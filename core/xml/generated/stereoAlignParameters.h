#ifndef STEREO_ALIGN_PARAMETERS_H_
#define STEREO_ALIGN_PARAMETERS_H_
/**
 * \file stereoAlignParameters.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from stereoAlign.xml
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
 * \brief Stereo Align Parameters 
 * Stereo Align Parameters 
 **/
class StereoAlignParameters : public corecvs::BaseReflection<StereoAlignParameters>
{
public:
    enum FieldId {
        PRODUCE_CAMERAS_ID,
        PRODUCE_OBSERVATIONS_ID,
        ZDIRX_ID,
        ZDIRY_ID,
        ZDIRZ_ID,
        AUTOZ_ID,
        AUTOSHIFT_ID,
        PRESHIFT_ID,
        GUESSSHIFTTHRESHOLD_ID,
        STEREO_ALIGN_PARAMETERS_FIELD_ID_NUM
    };

    /** Section with variables */

    /** 
     * \brief Produce Cameras 
     * Produce Cameras 
     */
    bool mProduceCameras;

    /** 
     * \brief Produce Observations 
     * Produce Observations 
     */
    bool mProduceObservations;

    /** 
     * \brief zdirX 
     * zdirX 
     */
    double mZdirX;

    /** 
     * \brief zdirY 
     * zdirY 
     */
    double mZdirY;

    /** 
     * \brief zdirZ 
     * zdirZ 
     */
    double mZdirZ;

    /** 
     * \brief autoZ 
     * autoZ 
     */
    bool mAutoZ;

    /** 
     * \brief autoShift 
     * autoShift 
     */
    bool mAutoShift;

    /** 
     * \brief preShift 
     * preShift 
     */
    int mPreShift;

    /** 
     * \brief guessShiftThreshold 
     * guessShiftThreshold 
     */
    int mGuessShiftThreshold;

    /** Static fields init function, this is used for "dynamic" field initialization */ 
    static int staticInit(corecvs::Reflection *toFill);

    static int relinkCompositeFields();

    /** Section with getters */
    const void *getPtrById(int fieldId) const
    {
        return (const unsigned char *)(this) + fields()[fieldId]->offset;
    }
    bool produceCameras() const
    {
        return mProduceCameras;
    }

    bool produceObservations() const
    {
        return mProduceObservations;
    }

    double zdirX() const
    {
        return mZdirX;
    }

    double zdirY() const
    {
        return mZdirY;
    }

    double zdirZ() const
    {
        return mZdirZ;
    }

    bool autoZ() const
    {
        return mAutoZ;
    }

    bool autoShift() const
    {
        return mAutoShift;
    }

    int preShift() const
    {
        return mPreShift;
    }

    int guessShiftThreshold() const
    {
        return mGuessShiftThreshold;
    }

    /** Section with setters */
    void setProduceCameras(bool produceCameras)
    {
        mProduceCameras = produceCameras;
    }

    void setProduceObservations(bool produceObservations)
    {
        mProduceObservations = produceObservations;
    }

    void setZdirX(double zdirX)
    {
        mZdirX = zdirX;
    }

    void setZdirY(double zdirY)
    {
        mZdirY = zdirY;
    }

    void setZdirZ(double zdirZ)
    {
        mZdirZ = zdirZ;
    }

    void setAutoZ(bool autoZ)
    {
        mAutoZ = autoZ;
    }

    void setAutoShift(bool autoShift)
    {
        mAutoShift = autoShift;
    }

    void setPreShift(int preShift)
    {
        mPreShift = preShift;
    }

    void setGuessShiftThreshold(int guessShiftThreshold)
    {
        mGuessShiftThreshold = guessShiftThreshold;
    }

    /** Section with embedded classes */
    /* visitor pattern - http://en.wikipedia.org/wiki/Visitor_pattern */
template<class VisitorType>
    void accept(VisitorType &visitor)
    {
        visitor.visit(mProduceCameras,            static_cast<const corecvs::BoolField *>(fields()[PRODUCE_CAMERAS_ID]));
        visitor.visit(mProduceObservations,       static_cast<const corecvs::BoolField *>(fields()[PRODUCE_OBSERVATIONS_ID]));
        visitor.visit(mZdirX,                     static_cast<const corecvs::DoubleField *>(fields()[ZDIRX_ID]));
        visitor.visit(mZdirY,                     static_cast<const corecvs::DoubleField *>(fields()[ZDIRY_ID]));
        visitor.visit(mZdirZ,                     static_cast<const corecvs::DoubleField *>(fields()[ZDIRZ_ID]));
        visitor.visit(mAutoZ,                     static_cast<const corecvs::BoolField *>(fields()[AUTOZ_ID]));
        visitor.visit(mAutoShift,                 static_cast<const corecvs::BoolField *>(fields()[AUTOSHIFT_ID]));
        visitor.visit(mPreShift,                  static_cast<const corecvs::IntField *>(fields()[PRESHIFT_ID]));
        visitor.visit(mGuessShiftThreshold,       static_cast<const corecvs::IntField *>(fields()[GUESSSHIFTTHRESHOLD_ID]));
    }

    StereoAlignParameters()
    {
        corecvs::DefaultSetter setter;
        accept(setter);
    }

    StereoAlignParameters(
          bool produceCameras
        , bool produceObservations
        , double zdirX
        , double zdirY
        , double zdirZ
        , bool autoZ
        , bool autoShift
        , int preShift
        , int guessShiftThreshold
    )
    {
        mProduceCameras = produceCameras;
        mProduceObservations = produceObservations;
        mZdirX = zdirX;
        mZdirY = zdirY;
        mZdirZ = zdirZ;
        mAutoZ = autoZ;
        mAutoShift = autoShift;
        mPreShift = preShift;
        mGuessShiftThreshold = guessShiftThreshold;
    }

    /** Exact match comparator **/ 
    bool operator ==(const StereoAlignParameters &other) const 
    {
        if ( !(this->mProduceCameras == other.mProduceCameras)) return false;
        if ( !(this->mProduceObservations == other.mProduceObservations)) return false;
        if ( !(this->mZdirX == other.mZdirX)) return false;
        if ( !(this->mZdirY == other.mZdirY)) return false;
        if ( !(this->mZdirZ == other.mZdirZ)) return false;
        if ( !(this->mAutoZ == other.mAutoZ)) return false;
        if ( !(this->mAutoShift == other.mAutoShift)) return false;
        if ( !(this->mPreShift == other.mPreShift)) return false;
        if ( !(this->mGuessShiftThreshold == other.mGuessShiftThreshold)) return false;
        return true;
    }
    friend std::ostream& operator << (std::ostream &out, StereoAlignParameters &toSave)
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
#endif  //STEREO_ALIGN_PARAMETERS_H_
