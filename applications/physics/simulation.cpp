#include "simulation.h"
#include "list"
#include "simObject.h"
#include "simSphere.h"
#include <ctime>
#include "core/utils/log.h"
#include <chrono>

using namespace std;

Simulation::Simulation()
{
    defaultStart();
}

Simulation::Simulation(string arg)
{
    if (arg=="drone")
    {

    }
    else
    {
        defaultStart();
    }
}


void Simulation::droneStart()
{
    mainObjects.emplace_back();
    PhysMainObject *mainObject = &mainObjects.back();
    mainObject->countPhysics = true;
    double radius = 2.0;
    double mass = 1.0;
    Affine3DQ pos1 = Affine3DQ(Vector3dd(-1, -1, -1));
    Affine3DQ pos2 = Affine3DQ(Vector3dd(1, -1, -1));
    Affine3DQ pos3 = Affine3DQ(Vector3dd(-1, 1, -1));
    Affine3DQ pos4 = Affine3DQ(Vector3dd(1, 1, -1));
    PhysSphere sphere1 = PhysSphere(&pos1, &radius, &mass);
    PhysSphere sphere2 = PhysSphere(&pos2, &radius, &mass);
    PhysSphere sphere3 = PhysSphere(&pos3, &radius, &mass);
    PhysSphere sphere4 = PhysSphere(&pos4, &radius, &mass);
    mainObject->addObject(&sphere1);
    mainObject->addObject(&sphere2);
    mainObject->addObject(&sphere3);
    mainObject->addObject(&sphere4);
    mainObject->addForce(Vector3dd(0,-9.8,0));


    cout << "Simulation::Simulation():" << mainObjects[0].objects.size() << " before thread" <<endl;
}

void Simulation::defaultStart()
{
    /* Adds new MainObject to the vector */
    mainObjects.emplace_back();
    PhysMainObject *mainObject = &mainObjects.back();
    mainObject->countPhysics = true;
    double radius = 2.0;
    double mass = 1.0;
    Affine3DQ pos1 = Affine3DQ(Vector3dd(-1, -1, -1));
    PhysSphere sphere1 = PhysSphere(&pos1, &radius, &mass);
    mainObject->addObject(&sphere1);
    mainObject->addForce(Vector3dd(0,-9.8,0));
    cout << "Simulation::Simulation():" << mainObjects[0].objects.size() << " before thread" <<endl;
}

void Simulation::start()
{

    /* Use PreciseTime instead of chrono, it could make code a bit more compact */


    startTime = std::chrono::high_resolution_clock::now();
    oldTime = std::chrono::high_resolution_clock::now();

    std::thread thr([this]()
    {
        cout<<mainObjects.size()<<" after thread"<<endl;
        cout<<"kek"<<endl;
        while (true)
        {
            newTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(newTime-oldTime);
            std::chrono::duration<double> currentTime = std::chrono::duration_cast<std::chrono::duration<double>>(newTime-startTime);

            // cout<<time_span.count()<<endl;
            for (int i=0; i<mainObjects.size(); i++)
            {
                mainObjects[i].tick(time_span.count());
                //mainObjects[i].spheres(std::to_string(currentTime.count()));
            }
            //L_INFO<<mainObjects[0].force<< " coords of sph in thrd";
            frameCounter++;

            /*if (frameCounter%1000==0)

            {
                cout<<"counter - "<<frameCounter<<endl;

            }*/

            oldTime=newTime;
            usleep(3000);
        }
    });
    thr.detach();
}
