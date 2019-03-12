#include "mainObject.h"

MainObject::MainObject()
{
}

void MainObject::addForce(const corecvs::Vector3dd &_force)
{
    force += _force;
}

void MainObject::tick(double deltaT)
{
    Vector3dd deltaPos = posCenter;
    for (size_t i = 0; i < objects.size(); ++i)
    {
        systemMass += objects[i]->mass;
    }
    //posCenter += deltaT * (velocity + deltaT * (force + oldForce) / systemMass / 4.0 );
    //velocity += ((force + oldForce) * deltaT) / (2 * systemMass);
    //oldForce = force;

    velocity = Vector3dd(1, 1, 1);
    posCenter += velocity * deltaT;
    deltaPos = posCenter - deltaPos;


    for (size_t i = 0; i < objects.size(); ++i)
    {
        //objects[i]->coords += deltaPos;             //If uncomment ui thread will crash after pressing start virtual mode ????????????????

        objects[i]->setCoords(objects[i]->coords+deltaPos);  //Also ui thread crash

        //objects[i]->setCoords(posCenter);             //Normalno
    }

    /* This seems to be not needed
    for (int i = 0; i < spheres.size(); ++i)
    {
        spheres[i].coords=objects[i]->coords;
    }
    */
}

void MainObject::setCenterOfMass()
{
    for (size_t i = 0; i < objects.size(); ++i)
    {
        massCenter += objects[i]->mass * objects[i]->coords;
        systemMass += objects[i]->mass;
    }
    massCenter = massCenter / systemMass;
}

void MainObject::addObject(SimObject *object)
{
    objects.push_back(object);
    setCenterOfMass();
}


void MainObject::addSphere(Vector3dd coords, double radius)
{
    objects.push_back(new SimSphere(coords,radius));
    setCenterOfMass();
}

MainObject::~MainObject()
{
    for (SimObject *obj : objects)
    {
        delete_safe(obj);
    }
    objects.clear();
}
