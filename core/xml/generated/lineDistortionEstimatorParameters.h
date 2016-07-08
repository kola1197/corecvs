#ifndef LINE_DISTORTION_ESTIMATOR_PARAMETERS_H_
#define LINE_DISTORTION_ESTIMATOR_PARAMETERS_H_
/**
 * \file lineDistortionEstimatorParameters.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include "reflection.h"
#include "defaultSetter.h"
#include "printerVisitor.h"

/*
 *  Embed includes.
 */
/*
 *  Additional includes for Composite Types.
 */

using namespace corecvs;

/*
 *  Additional includes for Pointer Types.
 */

namespace corecvs {
}
/*
 *  Additional includes for enum section.
 */
#include "lineDistortionEstimatorCost.h"

/**
 * \brief Line Distortion Estimator Parameters 
 * Line Distortion Estimator Parameters 
 **/
class LineDistortionEstimatorParameters : public BaseReflection<LineDistortionEstimatorParameters>
{
public:
    enum FieldId {
        COST_ALGORITHM_ID,
        ITERATION_NUMBER_ID,
        POLINOM_DEGREE_ID,
        SIMPLE_JACOBIAN_ID,
        EVEN_POWERS_ONLY_ID,
        ESTIMATE_TANGENT_ID,
        ESTIMATE_CENTER_ID,
        LINE_DISTORTION_ESTIMATOR_PARAMETERS_FIELD_ID_NUM
    };

    /** Section with variables */

    /** 
     * \brief Cost Algorithm 
     * Cost Algorithm 
     */
    int mCostAlgorithm;

    /** 
     * \brief Iteration Number 
     * Iteration Number 
     */
    int mIterationNumber;

    /** 
     * \brief Polinom Degree 
     * Polinom Degree 
     */
    int mPolinomDegree;

    /** 
     * \brief Simple Jacobian 
     * Simple Jacobian 
     */
    bool mSimpleJacobian;

    /** 
     * \brief Even powers only 
     * Even powers only 
     */
    bool mEvenPowersOnly;

    /** 
     * \brief Estimate Tangent 
     * Estimate Tangent 
     */
    bool mEstimateTangent;

    /** 
     * \brief Estimate Center 
     * Estimate Center 
     */
    bool mEstimateCenter;

    /** Static fields init function, this is used for "dynamic" field initialization */ 
    static int staticInit();

    /** Section with getters */
    const void *getPtrById(int fieldId) const
    {
        return (const unsigned char *)(this) + fields()[fieldId]->offset;
    }
    LineDistortionEstimatorCost::LineDistortionEstimatorCost costAlgorithm() const
    {
        return static_cast<LineDistortionEstimatorCost::LineDistortionEstimatorCost>(mCostAlgorithm);
    }

    int iterationNumber() const
    {
        return mIterationNumber;
    }

    int polinomDegree() const
    {
        return mPolinomDegree;
    }

    bool simpleJacobian() const
    {
        return mSimpleJacobian;
    }

    bool evenPowersOnly() const
    {
        return mEvenPowersOnly;
    }

    bool estimateTangent() const
    {
        return mEstimateTangent;
    }

    bool estimateCenter() const
    {
        return mEstimateCenter;
    }

    /* Section with setters */
    void setCostAlgorithm(LineDistortionEstimatorCost::LineDistortionEstimatorCost costAlgorithm)
    {
        mCostAlgorithm = costAlgorithm;
    }

    void setIterationNumber(int iterationNumber)
    {
        mIterationNumber = iterationNumber;
    }

    void setPolinomDegree(int polinomDegree)
    {
        mPolinomDegree = polinomDegree;
    }

    void setSimpleJacobian(bool simpleJacobian)
    {
        mSimpleJacobian = simpleJacobian;
    }

    void setEvenPowersOnly(bool evenPowersOnly)
    {
        mEvenPowersOnly = evenPowersOnly;
    }

    void setEstimateTangent(bool estimateTangent)
    {
        mEstimateTangent = estimateTangent;
    }

    void setEstimateCenter(bool estimateCenter)
    {
        mEstimateCenter = estimateCenter;
    }

    /* Section with embedded classes */
    /* visitor pattern - http://en.wikipedia.org/wiki/Visitor_pattern */
template<class VisitorType>
    void accept(VisitorType &visitor)
    {
        visitor.visit((int &)mCostAlgorithm,      static_cast<const EnumField *>    (fields()[COST_ALGORITHM_ID]));
        visitor.visit(mIterationNumber,           static_cast<const IntField *>     (fields()[ITERATION_NUMBER_ID]));
        visitor.visit(mPolinomDegree,             static_cast<const IntField *>     (fields()[POLINOM_DEGREE_ID]));
        visitor.visit(mSimpleJacobian,            static_cast<const BoolField *>    (fields()[SIMPLE_JACOBIAN_ID]));
        visitor.visit(mEvenPowersOnly,            static_cast<const BoolField *>    (fields()[EVEN_POWERS_ONLY_ID]));
        visitor.visit(mEstimateTangent,           static_cast<const BoolField *>    (fields()[ESTIMATE_TANGENT_ID]));
        visitor.visit(mEstimateCenter,            static_cast<const BoolField *>    (fields()[ESTIMATE_CENTER_ID]));
    }

    LineDistortionEstimatorParameters()
    {
        DefaultSetter setter;
        accept(setter);
    }

    LineDistortionEstimatorParameters(
          LineDistortionEstimatorCost::LineDistortionEstimatorCost costAlgorithm
        , int iterationNumber
        , int polinomDegree
        , bool simpleJacobian
        , bool evenPowersOnly
        , bool estimateTangent
        , bool estimateCenter
    )
    {
        mCostAlgorithm = costAlgorithm;
        mIterationNumber = iterationNumber;
        mPolinomDegree = polinomDegree;
        mSimpleJacobian = simpleJacobian;
        mEvenPowersOnly = evenPowersOnly;
        mEstimateTangent = estimateTangent;
        mEstimateCenter = estimateCenter;
    }

    friend ostream& operator << (ostream &out, LineDistortionEstimatorParameters &toSave)
    {
        PrinterVisitor printer(out);
        toSave.accept<PrinterVisitor>(printer);
        return out;
    }

    void print ()
    {
        cout << *this;
    }
};
#endif  //LINE_DISTORTION_ESTIMATOR_PARAMETERS_H_