#include "physMainObject.h"


PhysMainObject::PhysMainObject()
{
    posCenter = Vector3dd(0.0, 0.0, 0.0);
    systemMass = 0;
    force = Vector3dd::Zero();
    //moment = Vector3dd::Zero();

    L_INFO << "default PhysMainObject():created";
}

void PhysMainObject::addForce(const corecvs::Vector3dd &_force)
{
    /* objects dont need to know about whole system forces
    for (size_t i = 0; i < objects.size(); ++i)
    {
        objects[i]->addForce(_force);
    }
    */
    force += _force;
}

void PhysMainObject::tick(double deltaT)
{
    //L_INFO <<"PhysMainObject::tick should not be called";
}



void PhysMainObject::calcCenterOfMass()
{
    for (size_t i = 0; i < objects.size(); ++i)
    {
        massCenter += objects[i]->mass * objects[i]->getPosVector();
        systemMass += objects[i]->mass;
    }
    massCenter = massCenter / systemMass;
}

const Vector3dd PhysMainObject::getCenterOfMass()
{
    calcCenterOfMass();
    return massCenter;
}

void PhysMainObject::setForce(const Vector3dd &_force)
{
    force = _force;
}

const corecvs::Vector3dd PhysMainObject::getForce()
{
    return force;
}

void PhysMainObject::setMomentum(const Vector3dd &_m)
{
    momentum = _m;
}

const Vector3dd PhysMainObject::getMomentum()
{
    return momentum;
}

void PhysMainObject::setSystemMass(const double m)
{
    systemMass = m;
}

double PhysMainObject::getSystemMass() const
{
    return systemMass;
}


void PhysMainObject::calcForce()
{
    Vector3dd f = Vector3dd::Zero();
    Affine3DQ transform;
    //L_INFO << "transform: " << transform;
    Vector3dd forceToTransform;
    Vector3dd forceAfterTransform;
    for(size_t i = 0; i < objects.size(); ++i)
    {
        objects[i]->calcForce();
        transform = Affine3DQ(orientation, getPosCenter());// * objects[i]->getPosAffine();
        forceToTransform = objects[i]->getForce();
        forceAfterTransform = transform.rotor * forceToTransform;
        f += forceAfterTransform;
        //L_INFO << "added force: " << forceAfterTransform << "; forceToTransform: " << forceToTransform;
    }
    //L_INFO << "final force to add to PhysMainObject: " << f;
    addForce(f);
}

void PhysMainObject::calcMoment()
{
    Affine3DQ transform;
    Vector3dd m = Vector3dd::Zero();
    transform = Affine3DQ(orientation, getPosCenter());
    for(size_t i = 0; i < objects.size(); ++i)
    {
        objects[i]->calcMoment();

        m += transform.rotor * objects[i]->getMoment();
    }
    setMomentum(m);
}

void PhysMainObject::setPosCenter(const Vector3dd &_pos)
{
    posCenter = _pos;
}

const Vector3dd PhysMainObject::getPosCenter()
{
    return posCenter;
}

void PhysMainObject::startTick()
{
    force = Vector3dd::Zero();
    momentum = Vector3dd::Zero();
    for (size_t i = 0; i < objects.size(); i++)
    {
        objects[i]->startTick();
        //objects[i]->calcForce();
    }
}

void PhysMainObject::addObject(PhysObject *object)
{
    objects.push_back(object);
    calcCenterOfMass();
}

/*
void PhysMainObject::addSphere(Vector3dd coords, double radius)
{
    objects.push_back(new PhysSphere(coords,radius));
    setCenterOfMass();
}

void PhysMainObject::addSphere(Vector3dd coords, double radius,corecvs::RGBColor color)
{
    objects.push_back(new SimSphere(coords,radius,color));
    setCenterOfMass();
}
*/
PhysMainObject::~PhysMainObject()
{
    for (PhysObject *obj : objects)
    {
        delete_safe(obj);
    }
    objects.clear();
}
