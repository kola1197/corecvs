/**
 * \file binarizeParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from bufferFilters.xml
 */

#include <vector>
#include <stddef.h>
#include "binarizeParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
#if 0
template<>
Reflection BaseReflection<BinarizeParameters>::reflection = Reflection();
template<>
int BaseReflection<BinarizeParameters>::dummy = BinarizeParameters::staticInit();
#endif
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int BinarizeParameters::staticInit(corecvs::Reflection *toFill)
{
    if (toFill == NULL || toFill->objectSize != 0) {
        SYNC_PRINT(("staticInit(): Contract Violation in <BinarizeParameters>\n"));
         return -1;
    }

    toFill->name = ReflectionNaming(
        "Binarize Parameters",
        "Binarize Parameters",
        ""
    );

     toFill->objectSize = sizeof(BinarizeParameters);
     

    IntField* field0 = new IntField
        (
          BinarizeParameters::THRESHOLD_ID,
          offsetof(BinarizeParameters, mThreshold),
          2000,
          "Threshold",
          "Threshold",
          "Threshold",
          true,
         0,
         4096,
         1
        );
    toFill->fields.push_back(field0);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Binarize Parameters")]= toFill;
   return 0;
}
int BinarizeParameters::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


