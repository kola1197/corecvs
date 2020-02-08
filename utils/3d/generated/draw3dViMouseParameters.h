#ifndef DRAW_3D_VIMOUSE_PARAMETERS_H_
#define DRAW_3D_VIMOUSE_PARAMETERS_H_
/**
 * \file draw3dViMouseParameters.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from draw3dutils.xml
 */

#include "core/reflection/reflection.h"
#include "core/reflection/defaultSetter.h"
#include "core/reflection/printerVisitor.h"

/*
 *  Embed includes.
 */
/*
 *  Additional includes for Composite Types.
 */

// using namespace corecvs;

/*
 *  Additional includes for Pointer Types.
 */

// namespace corecvs {
// }
/*
 *  Additional includes for enum section.
 */
#include "viMouse3dStereoStyle.h"
#include "viMouse3dFlowStyle.h"

/**
 * \brief draw 3d ViMouse Parameters 
 * draw 3d ViMouse Parameters 
 **/
class Draw3dViMouseParameters : public corecvs::BaseReflection<Draw3dViMouseParameters>
{
public:
    enum FieldId {
        REDDIST_ID,
        BLUEDIST_ID,
        FLOWZOOM_ID,
        POINT_COLOR_TYPE_ID,
        FLOW_COLOR_TYPE_ID,
        DRAW_3D_VIMOUSE_PARAMETERS_FIELD_ID_NUM
    };

    /** Section with variables */

    /** 
     * \brief redDist 
     * redDist 
     */
    double mRedDist;

    /** 
     * \brief blueDist 
     * blueDist 
     */
    double mBlueDist;

    /** 
     * \brief flowZoom 
     * flowZoom 
     */
    double mFlowZoom;

    /** 
     * \brief Point Color Type 
     * Point Color Type 
     */
    int mPointColorType;

    /** 
     * \brief Flow Color Type 
     * Flow Color Type 
     */
    int mFlowColorType;

    /** Static fields init function, this is used for "dynamic" field initialization */ 
    static int staticInit(corecvs::Reflection *toFill);

    static int relinkCompositeFields();

    /** Section with getters */
    const void *getPtrById(int fieldId) const
    {
        return (const unsigned char *)(this) + fields()[fieldId]->offset;
    }
    double redDist() const
    {
        return mRedDist;
    }

    double blueDist() const
    {
        return mBlueDist;
    }

    double flowZoom() const
    {
        return mFlowZoom;
    }

    ViMouse3dStereoStyle::ViMouse3dStereoStyle pointColorType() const
    {
        return static_cast<ViMouse3dStereoStyle::ViMouse3dStereoStyle>(mPointColorType);
    }

    ViMouse3dFlowStyle::ViMouse3dFlowStyle flowColorType() const
    {
        return static_cast<ViMouse3dFlowStyle::ViMouse3dFlowStyle>(mFlowColorType);
    }

    /** Section with setters */
    void setRedDist(double redDist)
    {
        mRedDist = redDist;
    }

    void setBlueDist(double blueDist)
    {
        mBlueDist = blueDist;
    }

    void setFlowZoom(double flowZoom)
    {
        mFlowZoom = flowZoom;
    }

    void setPointColorType(ViMouse3dStereoStyle::ViMouse3dStereoStyle pointColorType)
    {
        mPointColorType = pointColorType;
    }

    void setFlowColorType(ViMouse3dFlowStyle::ViMouse3dFlowStyle flowColorType)
    {
        mFlowColorType = flowColorType;
    }

    /** Section with embedded classes */
    /* visitor pattern - http://en.wikipedia.org/wiki/Visitor_pattern */
template<class VisitorType>
    void accept(VisitorType &visitor)
    {
        visitor.visit(mRedDist,                   static_cast<const corecvs::DoubleField *>(fields()[REDDIST_ID]));
        visitor.visit(mBlueDist,                  static_cast<const corecvs::DoubleField *>(fields()[BLUEDIST_ID]));
        visitor.visit(mFlowZoom,                  static_cast<const corecvs::DoubleField *>(fields()[FLOWZOOM_ID]));
        visitor.visit((int &)mPointColorType,     static_cast<const corecvs::EnumField *>(fields()[POINT_COLOR_TYPE_ID]));
        visitor.visit((int &)mFlowColorType,      static_cast<const corecvs::EnumField *>(fields()[FLOW_COLOR_TYPE_ID]));
    }

    Draw3dViMouseParameters()
    {
        corecvs::DefaultSetter setter;
        accept(setter);
    }

    Draw3dViMouseParameters(
          double redDist
        , double blueDist
        , double flowZoom
        , ViMouse3dStereoStyle::ViMouse3dStereoStyle pointColorType
        , ViMouse3dFlowStyle::ViMouse3dFlowStyle flowColorType
    )
    {
        mRedDist = redDist;
        mBlueDist = blueDist;
        mFlowZoom = flowZoom;
        mPointColorType = pointColorType;
        mFlowColorType = flowColorType;
    }

    /** Exact match comparator **/ 
    bool operator ==(const Draw3dViMouseParameters &other) const 
    {
        if ( !(this->mRedDist == other.mRedDist)) return false;
        if ( !(this->mBlueDist == other.mBlueDist)) return false;
        if ( !(this->mFlowZoom == other.mFlowZoom)) return false;
        if ( !(this->mPointColorType == other.mPointColorType)) return false;
        if ( !(this->mFlowColorType == other.mFlowColorType)) return false;
        return true;
    }
    friend std::ostream& operator << (std::ostream &out, Draw3dViMouseParameters &toSave)
    {
        corecvs::PrinterVisitor printer(out);
        toSave.accept<corecvs::PrinterVisitor>(printer);
        return out;
    }

    void print ()
    {
        std::cout << *this;
    }
};
#endif  //DRAW_3D_VIMOUSE_PARAMETERS_H_
