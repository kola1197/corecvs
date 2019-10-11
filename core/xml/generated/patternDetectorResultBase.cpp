/**
 * \file patternDetectorResultBase.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from parameters.xml
 */

#include <vector>
#include <stddef.h>
#include "patternDetectorResultBase.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
#if 0
template<>
Reflection BaseReflection<PatternDetectorResultBase>::reflection = Reflection();
template<>
int BaseReflection<PatternDetectorResultBase>::dummy = PatternDetectorResultBase::staticInit();
#endif
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int PatternDetectorResultBase::staticInit(corecvs::Reflection *toFill)
{
    if (toFill == NULL || toFill->objectSize != 0) {
        SYNC_PRINT(("staticInit(): Contract Violation in <PatternDetectorResultBase>\n"));
         return -1;
    }

    toFill->name = ReflectionNaming(
        "pattern Detector Result Base",
        "pattern Detector Result Base",
        ""
    );

     toFill->objectSize = sizeof(PatternDetectorResultBase);
     

    CompositeField* field0 = new CompositeField
        (
          PatternDetectorResultBase::POSITION_ID,
          offsetof(PatternDetectorResultBase, mPosition),
          "position",
          "Vector2dParameters",
          "position",
          "Resulting pattern position",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Vector 2d Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field0->reflection = it->second;
        } else {
             printf("Reflection PatternDetectorResultBase to the subclass Vector 2d Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field0);
    /*  */ 
    CompositeField* field1 = new CompositeField
        (
          PatternDetectorResultBase::ORTX_ID,
          offsetof(PatternDetectorResultBase, mOrtX),
          "ortX",
          "Vector2dParameters",
          "ortX",
          "One of resulting pattern directions in image corrdinate",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Vector 2d Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field1->reflection = it->second;
        } else {
             printf("Reflection PatternDetectorResultBase to the subclass Vector 2d Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field1);
    /*  */ 
    CompositeField* field2 = new CompositeField
        (
          PatternDetectorResultBase::ORTY_ID,
          offsetof(PatternDetectorResultBase, mOrtY),
          "ortY",
          "Vector2dParameters",
          "ortY",
          "Second resulting pattern direction in image corrdinate ",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Vector 2d Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field2->reflection = it->second;
        } else {
             printf("Reflection PatternDetectorResultBase to the subclass Vector 2d Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field2);
    /*  */ 
    CompositeField* field3 = new CompositeField
        (
          PatternDetectorResultBase::UNITYPOINT_ID,
          offsetof(PatternDetectorResultBase, mUnityPoint),
          "unityPoint",
          "Vector2dParameters",
          "unityPoint",
          "Point that corresponds to (1,1 point on the pattern)",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Vector 2d Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field3->reflection = it->second;
        } else {
             printf("Reflection PatternDetectorResultBase to the subclass Vector 2d Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field3);
    /*  */ 
    IntField* field4 = new IntField
        (
          PatternDetectorResultBase::ID_ID,
          offsetof(PatternDetectorResultBase, mId),
          0,
          "id",
          "id",
          "pattern id "
        );
    toFill->fields.push_back(field4);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("pattern Detector Result Base")]= toFill;
   return 0;
}
int PatternDetectorResultBase::relinkCompositeFields()
{
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Vector 2d Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[0]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection PatternDetectorResultBase to the subclass Vector 2d Parameters can't be linked\n");
        }
    }
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Vector 2d Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[1]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection PatternDetectorResultBase to the subclass Vector 2d Parameters can't be linked\n");
        }
    }
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Vector 2d Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[2]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection PatternDetectorResultBase to the subclass Vector 2d Parameters can't be linked\n");
        }
    }
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Vector 2d Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[3]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection PatternDetectorResultBase to the subclass Vector 2d Parameters can't be linked\n");
        }
    }
   return 0;
}

SUPPRESS_OFFSET_WARNING_END

