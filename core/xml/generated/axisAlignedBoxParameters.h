#ifndef AXIS_ALIGNED_BOX_PARAMETERS_H_
#define AXIS_ALIGNED_BOX_PARAMETERS_H_
/**
 * \file axisAlignedBoxParameters.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from parameters.xml
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

/**
 * \brief Axis Aligned Box Parameters 
 * Axis Aligned Box Parameters 
 **/
class AxisAlignedBoxParameters : public corecvs::BaseReflection<AxisAlignedBoxParameters>
{
public:
    enum FieldId {
        X_ID,
        Y_ID,
        Z_ID,
        WIDTH_ID,
        HEIGHT_ID,
        DEPTH_ID,
        AXIS_ALIGNED_BOX_PARAMETERS_FIELD_ID_NUM
    };

    /** Section with variables */

    /** 
     * \brief X 
     * X 
     */
    double mX;

    /** 
     * \brief Y 
     * Y 
     */
    double mY;

    /** 
     * \brief Z 
     * Z 
     */
    double mZ;

    /** 
     * \brief width 
     * width 
     */
    double mWidth;

    /** 
     * \brief height 
     * height 
     */
    double mHeight;

    /** 
     * \brief depth 
     * depth 
     */
    double mDepth;

    /** Static fields init function, this is used for "dynamic" field initialization */ 
    static int staticInit(corecvs::Reflection *toFill);

    static int relinkCompositeFields();

    /** Section with getters */
    const void *getPtrById(int fieldId) const
    {
        return (const unsigned char *)(this) + fields()[fieldId]->offset;
    }
    double x() const
    {
        return mX;
    }

    double y() const
    {
        return mY;
    }

    double z() const
    {
        return mZ;
    }

    double width() const
    {
        return mWidth;
    }

    double height() const
    {
        return mHeight;
    }

    double depth() const
    {
        return mDepth;
    }

    /** Section with setters */
    void setX(double x)
    {
        mX = x;
    }

    void setY(double y)
    {
        mY = y;
    }

    void setZ(double z)
    {
        mZ = z;
    }

    void setWidth(double width)
    {
        mWidth = width;
    }

    void setHeight(double height)
    {
        mHeight = height;
    }

    void setDepth(double depth)
    {
        mDepth = depth;
    }

    /** Section with embedded classes */
    /* visitor pattern - http://en.wikipedia.org/wiki/Visitor_pattern */
template<class VisitorType>
    void accept(VisitorType &visitor)
    {
        visitor.visit(mX,                         static_cast<const corecvs::DoubleField *>(fields()[X_ID]));
        visitor.visit(mY,                         static_cast<const corecvs::DoubleField *>(fields()[Y_ID]));
        visitor.visit(mZ,                         static_cast<const corecvs::DoubleField *>(fields()[Z_ID]));
        visitor.visit(mWidth,                     static_cast<const corecvs::DoubleField *>(fields()[WIDTH_ID]));
        visitor.visit(mHeight,                    static_cast<const corecvs::DoubleField *>(fields()[HEIGHT_ID]));
        visitor.visit(mDepth,                     static_cast<const corecvs::DoubleField *>(fields()[DEPTH_ID]));
    }

    AxisAlignedBoxParameters()
    {
        corecvs::DefaultSetter setter;
        accept(setter);
    }

    AxisAlignedBoxParameters(
          double x
        , double y
        , double z
        , double width
        , double height
        , double depth
    )
    {
        mX = x;
        mY = y;
        mZ = z;
        mWidth = width;
        mHeight = height;
        mDepth = depth;
    }

    /** Exact match comparator **/ 
    bool operator ==(const AxisAlignedBoxParameters &other) const 
    {
        if ( !(this->mX == other.mX)) return false;
        if ( !(this->mY == other.mY)) return false;
        if ( !(this->mZ == other.mZ)) return false;
        if ( !(this->mWidth == other.mWidth)) return false;
        if ( !(this->mHeight == other.mHeight)) return false;
        if ( !(this->mDepth == other.mDepth)) return false;
        return true;
    }
    friend std::ostream& operator << (std::ostream &out, AxisAlignedBoxParameters &toSave)
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
#endif  //AXIS_ALIGNED_BOX_PARAMETERS_H_
