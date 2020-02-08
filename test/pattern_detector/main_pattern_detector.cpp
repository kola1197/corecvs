#include <iostream>

#include <core/reflection/commandLineSetter.h>
#include <core/reflection/jsonPrinter.h>
#include <core/reflection/usageVisitor.h>

#include <wrappers/jsonmodern/jsonModernReader.h>

#include <core/patterndetection/harrisPatternDetector.h>

#include "core/patterndetection/dummyPatternDetector.h"
#include "core/patterndetection/patternDetector.h"

#include "core/buffers/bufferFactory.h"
#include "core/fileformats/bmpLoader.h"
#include "core/buffers/rgb24/rgb24Buffer.h"

#ifdef WITH_LIBJPEG
#include "libjpegFileReader.h"
#endif
#ifdef WITH_LIBPNG
#include "libpngFileReader.h"
#endif
#ifdef WITH_OPENCV
#include "patternDetect/openCVSquareDetector.h"
#include "patternDetect/openCVCheckerBoardDetector.h"
#endif

#ifdef WITH_APRILTAG
#include "wrappers/apriltag_wrapper/apriltagDetector.h"
#endif

using namespace std;
using namespace corecvs;

int producerCaps(CommandLineSetter &s)
{
    std::string producerName = s.getString("producer");
    PatternDetector *producer = PatternDetectorFabric::getInstance()->fabricate(producerName);

    if (producer == NULL) {
        SYNC_PRINT(("Producer not found. Check --caps\n"));
        return 1;
    }

    SYNC_PRINT(("Printing parameters for <%s>\n", producerName.c_str()));

    std::map<std::string, DynamicObject> paramsMap = producer->getParameters();
    for(auto &it : paramsMap) {
        cout << it.first << endl;
        UsagePrinter printer;
        DynamicObjectWrapper wrapper(it.second.reflection, it.second.rawObject);
        printer.printUsage(&wrapper, it.first + ".");
        cout << endl;
    }
    SYNC_PRINT(("You can also use config files:\n"));
    SYNC_PRINT(("  --config=<filename> - this JSON file is loaded first, separate parameters are applied later\n"));
    SYNC_PRINT(("  --dumpConfig - saves the default file\n"));
    SYNC_PRINT(("\n"));
    return 0;
}


int detect(CommandLineSetter &s)
{
    Statistics stats;
    Statistics::startInterval(&stats);

    std::string producerName = s.getString("producer");
    PatternDetector *producer = PatternDetectorFabric::getInstance()->fabricate(producerName);
    if (producer == NULL) {
        SYNC_PRINT(("Producer not found. Check --caps\n"));
        return 2;
    }
    std::map<std::string, DynamicObject> paramsMap = producer->getParameters();
    std::string configFile = s.getString("config", "");

    /* Store default config if needed */
    if (s.hasOption("dumpConfig")) {
        if (configFile.empty()) {
            cout << "Config example begins below this line:" << endl;
            JSONPrinter printer;
            for(auto &it : paramsMap)
                printer.visit(it.second, it.first.c_str());
            cout << endl << "Config ended\n";
        } else {
            JSONPrinter printer(configFile);
            for(auto &it : paramsMap)
                printer.visit(it.second, it.first.c_str());
        }
    } else if (!configFile.empty()) {
        JSONModernReader reader(configFile);
        if (!reader.hasError()) {
            for(auto &it : paramsMap)
                reader.visit(it.second, it.first.c_str());
        }
    }

    /* Check for config parameters from command line */
    for(auto &it : paramsMap) {
        CommandLineSetter sCopy = s;
        sCopy.mPreserveValues = true;

        /*This block is unsafe*/
        DynamicObject copy = it.second.clone();
        sCopy.visit(it.second, it.first.c_str());
        if (!DynamicObject::compare(copy, it.second))
            cout << "Params Differ" << endl;
    }

    if (s.hasOption("showParams"))
        for(auto &it : paramsMap)
            cout << "Param set:\n" << it.first << endl << it.second << endl;

    /*Setting actual parameters*/
    for(auto &it : paramsMap)
        producer->setParameters(it.first, it.second);

    Statistics::endInterval(&stats, "Creating producer");

    Statistics::startInterval(&stats);
    std::string inputName = s.getString("input");
    RGB24Buffer *input = BufferFactory::getInstance()->loadRGB24Bitmap(inputName);
    if (input == NULL)
    {
        SYNC_PRINT(("Unable to load image <%s>\n", inputName.c_str()));
    }
    Statistics::endInterval(&stats, "Loading input data");

    Statistics::enterContext(&stats, "Processing ->");
    producer->setInputImage(input);
    producer->setStatistics(&stats);
    producer->operator ()();
    vector<PatternDetectorResult> result;
    producer->getOutput(result);
    Statistics::leaveContext(&stats);

    for(size_t i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }

    Statistics::startInterval(&stats);
    producer->dumpAllDebugs("detector-", ".png");

    delete_safe(input);
    delete_safe(producer);
    Statistics::endInterval(&stats, "Cleanup");

    BaseTimeStatisticsCollector collector;
    collector.addStatistics(stats);
    collector.printAdvanced();

    return 0;
}


void usage()
{
  SYNC_PRINT(("Call example:\n\n"));

  SYNC_PRINT(("./bin/pattern_detector --caps\n"));
  SYNC_PRINT(("          - show options with which app was compiled\n"));
  SYNC_PRINT(("./bin/pattern_detector --producercaps --producer=Dummy\n"));
  SYNC_PRINT(("          - show specific provider options\n"));
  SYNC_PRINT(("./bin/pattern_detector --detect --producer=Dummy --dumpConfig\n"));
  SYNC_PRINT(("          - dump current config to stdout\n"));
  SYNC_PRINT(("./bin/pattern_detector --detect --producer=Dummy --dumpConfig --config=out.json\n"));
  SYNC_PRINT(("          - dump current config to out.json\n"));
  SYNC_PRINT(("          \n"));
  SYNC_PRINT(("          \n"));
  SYNC_PRINT(("Dummy pattern provider:\n"));
  SYNC_PRINT(("./bin/pattern_detector --detect --producer=Dummy --point.position.x=10 --point.position.y=10 --input=circles.bmp\n"));
  SYNC_PRINT(("          - example that returns back pattern at given point\n"));
  SYNC_PRINT(("./bin/pattern_detector --detect --producer=Dummy --color.r=100 --color.g=100 --color.b=100 --input=circles.bmp\n"));
  SYNC_PRINT(("          - example that returns back pattern at point with closest color to given\n"));
  SYNC_PRINT(("          \n"));
  SYNC_PRINT(("          \n"));
  SYNC_PRINT(("Opencv Square pattern provider:\n"));
  SYNC_PRINT(("./bin/pattern_detector --detect --producer=OpenCVSquare --params.debug=on --input=photo_2019-09-29_23-11-36.jpg\n"));
  SYNC_PRINT(("          - example that returns detected squares\n"));
  SYNC_PRINT(("          \n"));
  SYNC_PRINT(("Opencv CheckerBoard pattern provider (only one checkerboard in frame):\n"));
  SYNC_PRINT(("wget https://rdmilligan.files.wordpress.com/2015/06/cameracalibrationandposeestimation_sample.jpg -o in.jpg"));
  SYNC_PRINT(("./bin/pattern_detector --detect --producer=OpenCVCheckerBoard  --input=in.jpg\n"));
  SYNC_PRINT(("          - example that returns detected squares\n"));
  SYNC_PRINT(("          \n"));
  SYNC_PRINT(("          \n"));  
  SYNC_PRINT(("Apriltag pattern provider:\n"));
  SYNC_PRINT(("./bin/pattern_detector --detect --producer=Apriltag --params.debug=on --input="".jpg\n")); //TODO add more params
  SYNC_PRINT(("          - example that returns detected squares\n"));
}

int main(int argc, char *argv[])
{
#ifdef WITH_LIBJPEG
    LibjpegFileReader::registerMyself();
    LibjpegFileSaver::registerMyself();
    SYNC_PRINT(("Libjpeg support on\n"));
#endif
#ifdef WITH_LIBPNG
    LibpngFileReader::registerMyself();
    LibpngFileSaver::registerMyself();
    SYNC_PRINT(("Libpng support on\n"));
#endif    
    PatternDetectorFabric::getInstance()->add(new PatternDetectorProducer<DummyPatternDetector>("Dummy"));
    PatternDetectorFabric::getInstance()->add(new PatternDetectorProducer<HarrisPatternDetector>("Harris"));

#ifdef WITH_OPENCV
    PatternDetectorFabric::getInstance()->add(new PatternDetectorProducer<OpenCVSquareDetector>("OpenCVSquare"));
    PatternDetectorFabric::getInstance()->add(new PatternDetectorProducer<OpenCVCheckerBoardDetector>("OpenCVCheckerBoard"));

#endif

#ifdef WITH_APRILTAG
    PatternDetectorFabric::getInstance()->add(new PatternDetectorProducer<ApriltagDetector>("Apriltag"));
#endif

    CommandLineSetter s(argc, argv);
    if (s.hasOption("caps")) {
        BufferFactory::printCaps();
        PatternDetectorFabric::getInstance()->print();
        return 0;
    }

    if (s.hasOption("producercaps")) {
        producerCaps(s);
        return 0;
    }

    if (s.hasOption("detect"))
    {
        detect(s);
        return 0;
    }

    usage();
    return 0;
}
