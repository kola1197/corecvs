/**
 * \file main_test_commandline.cpp
 * \brief This is the main file for the test commandline 
 *
 * \date aug. 21, 2015
 * \author alexander
 *
 * \ingroup autotest  
 **/

#include <iostream>
#include <generated/testBlock.h>
#include <core/reflection/dynamicObject.h>
#include <core/reflection/usageVisitor.h>
#include "gtest/gtest.h"

#include "core/utils/global.h"

#include "core/reflection/commandLineSetter.h"
#include "core/reflection/commandLineGetter.h"
#include "core/math/vector/vector3d.h"

using namespace corecvs;

using std::istream;
using std::ostream;
using std::cout;
using std::endl;

TEST(CommandLine, testAdditionalFunction)
{
    const char *argv[] = {"--bool=true", "--bool1=false","--int=42", "--double=3.14", "--string=test1", "--value with spaces=999"};
    int argc = CORE_COUNT_OF(argv);

    CommandLineSetter setter(argc, argv);
    bool   boolVal  = setter.getBool("bool");
    bool   boolVal1 = setter.getBool("bool1");

    int    intVal  = setter.getInt("int");
    double dblVal  = setter.getDouble("double");
    string strVal  = setter.getString("string", "");
    int    intSpVal= setter.getInt("value with spaces");

    cout << "Bool :"   << (boolVal  ? "true" : "false") << endl;
    cout << "Bool1:"   << (boolVal1 ? "true" : "false") << endl;

    cout << "Int:"    << intVal << endl;
    cout << "Double:" << dblVal << endl;
    cout << "String:" << strVal << endl;

    CORE_ASSERT_TRUE(boolVal   == true ,    "Bool parsing problem");
    CORE_ASSERT_TRUE(boolVal1  == false,    "Bool false parsing problem");

    CORE_ASSERT_TRUE(intVal   == 42,      "Int parsing problem");
    CORE_ASSERT_TRUE(dblVal   == 3.14,    "Double parsing problem");
    CORE_ASSERT_TRUE(strVal   == "test1", "String parsing problem");
    CORE_ASSERT_TRUE(intSpVal == 999,     "Int with spaces parsing problem");



}


TEST(CommandLine, testVisitor)
{
    const char *argv[] = {"--x=2.4", "--y=42", "--z=3.14"};
    int argc = CORE_COUNT_OF(argv);

    CommandLineSetter setter(argc, argv);
    Vector3dd in (1.0,2.0,3.0);
    cout << "Before Loading :"  << in << std::endl;

    in.accept<CommandLineSetter>(setter);
    cout << "After Loading :"  << in << std::endl;

    CommandLineGetter getter;
    in.accept<CommandLineGetter>(getter);
    cout << getter.str() << std::endl;


    CORE_ASSERT_TRUE(in.x() ==  2.4, "Error in visitor x");
    CORE_ASSERT_TRUE(in.y() ==   42, "Error in visitor y");
    CORE_ASSERT_TRUE(in.z() == 3.14, "Error in visitor z");
}

TEST(CommandLine, testVisitorKeep)
{
    const char *argv[] = {"--x=2.4", "--y=42"};
    int argc = CORE_COUNT_OF(argv);

    CommandLineSetter setter(argc, argv);
    Vector3dd in;
    in = Vector3dd(1.0,2.0,3.0);
    cout << "Before Loading :"  << in << std::endl;

    in.accept<CommandLineSetter>(setter);
    cout << "After Loading :"  << in << std::endl;

    CommandLineGetter getter;
    in.accept<CommandLineGetter>(getter);
    cout << getter.str() << std::endl;

    CORE_ASSERT_TRUE(in.x() ==  2.4, "Error in visitor x");
    CORE_ASSERT_TRUE(in.y() ==   42, "Error in visitor y");
    CORE_ASSERT_TRUE(in.z() ==    0, "Error in visitor z");


    in = Vector3dd(1.0,2.0,3.0);
    CommandLineSetter setterKeep(argc, argv);
    setterKeep.mPreserveValues = true;
    in.accept<CommandLineSetter>(setterKeep);
    CORE_ASSERT_TRUE(in.x() ==  2.4, "Error in visitor x");
    CORE_ASSERT_TRUE(in.y() ==   42, "Error in visitor y");
    CORE_ASSERT_TRUE(in.z() ==  3.0, "Error in visitor z");
}

TEST(CommandLine, testVisitorComplexObject0)
{
     TestBlock block;
     {
         CommandLineGetter getter;
         cout << "Visitor call" << std::endl;
         getter.visit<TestBlock>(block, block.getReflection());
         cout << getter.str() << std::endl;
     }

     {
         CommandLineGetter getter;
         cout << "Visitor call1" << std::endl;
         getter.visit<TestBlock>(block, "prefix.");
         cout << getter.str() << std::endl;
     }

     {
        CommandLineGetter getter;
        cout << "Accept call" << std::endl;
        block.accept<CommandLineGetter>(getter);
     }

}

TEST(CommandLine, testVisitorComplexObject)
{    
    TestBlock block;
    UsagePrinter printer;
    printer.printUsage(block.getReflection(), "prefix.");
    cout << " ============================================" << std::endl;

    cout << block << std::endl;

    cout << " ============================================" << std::endl;

    const char *argv[] = {
        "--prefix.params.String field=change with space",
        "--prefix.params.Int Field0=5",
        "--prefix.params.Double field0=6.5",
        "--prefix.params.Enum Field0=1",
        "--prefix.params.Subclass Field.Int Field0=4"};
    int argc = CORE_COUNT_OF(argv);

    CommandLineSetter setter(argc, argv);
    DynamicObjectWrapper obj(&block);
    setter.mPreserveValues = true;
    setter.visit(obj, "prefix");
    cout << block << std::endl;
    CORE_ASSERT_TRUE(block.params().stringField()  == "change with space", "Wrong string parsing");
    CORE_ASSERT_TRUE(block.params().intField0()    == 5, "Wrong int parsing");
    CORE_ASSERT_TRUE(block.params().doubleField0() == 6.5, "Wrong double parsing");
    CORE_ASSERT_TRUE(block.params().enumField0()   == TestEnum::ITEM2, "Wrong enum parsing");
    CORE_ASSERT_TRUE(block.params().subclassField().intField0() == 4, "Wrong int in structure parsing");
}


TEST(CommandLine, testSubstring)
{
    const char *argv[] = {"./bin/test_cloud_match", "--icplist", "test", "test"};
    int argc = CORE_COUNT_OF(argv);

    CommandLineSetter setter(argc, argv);

    cout << setter.hasOption("icp") << "  " << setter.hasOption("icplist") << std::endl;

    CORE_ASSERT_TRUE(setter.hasOption("icp")     == false, "False positive");
    CORE_ASSERT_TRUE(setter.hasOption("icplist") == true, "False negative");

}

