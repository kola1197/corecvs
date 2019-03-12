#include "joystickInput.h"
#include "core/utils/global.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <unistd.h>
#include <QBitArray>
#include <bitset>
#include <linux/joystick.h>
#include <fcntl.h>
#include <thread>
#include "joystickInput.h"
#include "time.h"
#include <fstream>


using namespace std;


JoyStickInput::JoyStickInput(int &_yawValue, int &_rollValue, int &_pitchValue, int &_throttleValue,
                             int &_CH5Value, int &_CH6Value, int &_CH7Value,  int &_CH8Value )
    : yawValue(_yawValue) , rollValue(_rollValue), pitchValue(_pitchValue), throttleValue(_throttleValue),
      CH5Value(_CH5Value), CH6Value(_CH6Value), CH7Value(_CH7Value), CH8Value(_CH8Value)
{
    throttleValue=1239;
    // cout<<"AAAaaaAAA"<<endl;
}

void JoyStickInput::start()
{
    timerForThrottle();
    startJoyStickMode();
}

//JOYSTICKs PART

/**
 * Reads a joystick event from the joystick device.
 *
 * Returns 0 on success. Otherwise -1 is returned.
 */
int readEvent(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    /* Error, could not read full event. */
    return -1;
}

/**
 * Returns the number of axes on the controller or 0 if an error occurs.
 */
size_t getAxisCount(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}

/**
 * Returns the number of buttons on the controller or 0 if an error occurs.
 */


size_t getButtonCount(int fd)
{
    __u8 buttons;
    if (ioctl(fd, JSIOCGBUTTONS, &buttons) == -1)
        return 0;

    return buttons;
}

/**
 * Current state of an axis.
 */
struct AxisState {short x, y;};


/**
 * Keeps track of the current axis state.
 *
 * NOTE: This function assumes that axes are numbered starting from 0, and that
 * the X axis is an even number, and the Y axis is an odd number. However, this
 * is usually a safe assumption.
 *
 * Returns the axis that the event indicated.
 */

size_t getAxisState(struct js_event *event,  JoyStickInput::AxisState axes[3])
{
    size_t axis = event->number / 2;

    if (axis < 3)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value;
        else
            axes[axis].y = event->value;
    }

    return axis;
}



void JoyStickInput::startJoyStickMode()
{
    std::thread thr([this]()
    {
        const char *device;
        int js;
        struct js_event eventtt;
        device = "/dev/input/js0";
        js = open(device, O_RDONLY);
        if (js == -1)
        {
            perror("Could not open joystick");
            cout<<"Could not open joystick"<<endl;
        }
        else
        {
            countOfSticks=getAxisCount(js);
            cout<<"JS mode has started"<<endl;
            while (readEvent(js, &eventtt) == 0)
            {
                autopilotMode=false;
                switch (eventtt.type)
                {
                case JS_EVENT_BUTTON:
                    //cout<<"button event"<<endl;

                    switch (currentMode)
                    {
                    case 0:
                        usualButtons(eventtt);
                        break;
                    case 1:
                        inertialButtons(eventtt);
                        break;
                    case 2:
                        casualButtons(eventtt);
                        break;
                    case 3:
                        usualExperimentalButtons(eventtt);
                        break;
                    case 4:                                 //diff with 3 in timer thread
                        usualExperimentalButtons(eventtt);
                        break;
                    default: break;
                    }


                    break;
                case JS_EVENT_AXIS:
                    //cout<<"stick event"<<endl;

                    switch (currentMode)
                    {
                    case 0:
                        usualSticks(eventtt);
                        break;
                    case 1:
                        inertialSticks(eventtt);
                        break;
                    case 2:
                        casualSticks(eventtt);
                        break;
                    case 3:
                        usualExperimentalSticks(eventtt);
                        break;
                    case 4:
                        usualExperimentalSticks(eventtt);
                        break;

                    default: break;
                    }

                    break;
                default:
                    break;
                }
            }
        }
    });
    thr.detach();
}

void JoyStickInput::usualButtons(js_event event)
{
    unsigned char seven=7;
    unsigned char six=6;
    unsigned char five=5;
    unsigned char four=4;
    unsigned char three=3;
    unsigned char two=2;
    unsigned char one=1;
    unsigned char zero=0;
    switch (countOfSticks)
    {

    case 6:                            //Dinput
        if (event.number==seven)                     //arming    //rt
        {
            startArming(event.value);
        }
        if (event.number==five  && event.value )      //rb         //turn of copter(if smth goes wery wery wrong)
        {
            disconnectFromCopter();
        }
        if (event.number==one && event.value)         //a
        {
            if (!recording)
            {
                startRecord();
            }
            else
            {
                stopRecord();
            }
        }
        break;                          //Xinput
    case 8:

        if (event.number==five  && event.value )      //rb         //turn of copter(if smth goes wery wery wrong)
        {
            disconnectFromCopter();
        }
        if (event.number==zero && event.value)         //a
        {
            if (!recording)
            {
                startRecord();
            }
            else
            {
                stopRecord();
            }
        }
        break;
    }
}

void JoyStickInput::usualSticks(js_event event)
{
    const int thr_const=1;
    const int roll_const=10;
    const int pit_const=10;
    const int yaw_const=10;
    size_t axis;

    switch (countOfSticks)
    {

    case 6:                            //Dinput
        axis = getAxisState(&event, axes);
        if (axis < 3)
        {                                                //minimum axis is not 30000, but near
            if (axis==0)
            {
                yawValue = 1500+axes[axis].x/50/yaw_const;
                throttleValue = 1500-axes[axis].y/50/thr_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}
                if (throttleValue>2100){throttleValue=2099;}
                if (throttleValue<900) {throttleValue=901;}
            }
            if (axis==1)
            {
                pitchValue = 1500 - axes[axis].y/50/pit_const;
                rollValue = 1500 + axes[axis].x/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}
            }
        }
        break;
    case 8:                            //Xinput
        axis = getAxisState(&event, axes);
        if (axis < 3)
        {                                                //minimum axis is not 30000, but near
            if (axis==0)
            {
                yawValue = 1500+axes[axis].x/50/yaw_const;
                throttleValue = 1500-axes[axis].y/50/thr_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}
                if (throttleValue>2100){throttleValue=2099;}
                if (throttleValue<900) {throttleValue=901;}
            }
            if (axis==1)
            {
                rollValue = 1500 + axes[axis].y/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}
            }
            if (axis==2)
            {

                pitchValue = 1500 - axes[axis].x/50/pit_const;
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}
                if (axes[axis].y>10000)
                {
                    startArming(true);
                }
                else
                {
                    startArming(false);
                }
            }
        }
        break;


    }
}

void JoyStickInput::inertialButtons(js_event event)
{
    unsigned char seven=7;
    unsigned char six=6;
    unsigned char five=5;
    unsigned char four=4;
    unsigned char three=3;
    unsigned char two=2;
    unsigned char one=1;
    unsigned char zero=0;

    switch (countOfSticks)
    {

    case 6:                            //Dinput

        if (event.number==seven )                  //rt   //arming
        {
            startArming(event.value);
        }
        if (event.number==five  && event.value )    //rb                 //turns of copter(if smth goes very very wrong)
        {
            disconnectFromCopter();
        }
        if (event.number==six  && event.value )     //lt            //  all sticks to zero (if smth goes wrong)
        {
            throttleValue = 1100;
            rollValue = 1500;
            pitchValue = 1500;
            throttleValueFromJS = 1500;
            yawValue = 1500;
        }
        if (event.number==four && event.value )      //lb               //Throttle to mid
        {
            throttleValue=midThrottle;
            throttleValueFromJS=1500;
        }
        if (event.number==three && event.value )     //y                //Throttle to mid
        {
            midThrottle=throttleValue;
        }
        if (event.number==one && event.value)        //a            //arming
        {
            if (!recording)
            {
                startRecord();
            }
            else
            {
                stopRecord();
            }
        }
        break;
    case 8:                            //Xinput


        if (event.number==five  && event.value )    //rb                 //turns of copter(if smth goes very very wrong)
        {
            disconnectFromCopter();
        }

        if (event.number==four && event.value )      //lb               //Throttle to mid
        {
            throttleValue=midThrottle;
            throttleValueFromJS=1500;
        }
        if (event.number==three && event.value )     //y                //Throttle to mid
        {
            midThrottle=throttleValue;
        }
        if (event.number==zero && event.value)        //a            //arming
        {
            if (!recording)
            {
                startRecord();
            }
            else
            {
                stopRecord();
            }
        }
        break;
    }
}

void JoyStickInput::inertialSticks(js_event event)
{
    const int thr_const=1;
    const int roll_const=10;
    const int pit_const=10;
    const int yaw_const=10;

    size_t axis;

    switch (countOfSticks)
    {

    case 6:                            //Dinput
        axis = getAxisState(&event, axes);

        if (axis < 3)
        {                                                //minimum axis is -32767
            if (axis==0)
            {
                yawValue = 1500+axes[axis].x/50/yaw_const;
                throttleValueFromJS = 1500-axes[axis].y/50/thr_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}
                if (throttleValue>2100){throttleValue=2099;}
                if (throttleValue<900) {throttleValue=901;}

            }
            if (axis==1)
            {
                pitchValue = 1500 - axes[axis].y/50/pit_const;
                rollValue = 1500 + axes[axis].x/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}
            }
        }
        break;
    case 8:                            //Xinput
        axis = getAxisState(&event, axes);

        if (axis < 3)
        {                                                //minimum value on axis is -32767 (tested with logitech f710)
            if (axis==0)
            {
                yawValue = 1500+axes[axis].x/50/yaw_const;
                throttleValueFromJS = 1500-axes[axis].y/50/thr_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}
                if (throttleValue>2100){throttleValue=2099;}
                if (throttleValue<900) {throttleValue=901;}

            }
            if (axis==1)
            {
                rollValue = 1500 + axes[axis].y/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}
                if (axes[axis].x>-29000)
                {
                    throttleValue = 1100;
                    rollValue = 1500;
                    pitchValue = 1500;
                    throttleValueFromJS = 1500;
                    yawValue = 1500;
                }

            }
            if (axis==2)
            {

                pitchValue = 1500 - axes[axis].x/50/pit_const;
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}
                cout<<"axe lt"<<axes[axis].y<<endl;
                if (axes[axis].y>10000)
                {
                    startArming(true);
                }
                else
                {
                    startArming(false);
                }
            }
        }
        break;
    }
}

void JoyStickInput::casualButtons(js_event event)
{

    unsigned char seven=7;
    unsigned char six=6;
    unsigned char five=5;
    unsigned char four=4;
    unsigned char three=3;
    unsigned char two=2;
    unsigned char one=1;
    unsigned char zero=0;

    switch (countOfSticks)
    {
    case 6:
        if (event.number==five )                    //rb //arming
        {
            startArming(event.value);
        }
        if (event.number==four  && event.value )     //lb                //turn of copter(if smth goes wery wery wrong)
        {
            disconnectFromCopter();
        }
        if (event.number==seven  && event.value && !ltPressed)        //rt
        {
            rtPressed=true;
            throttleValue=1500;
        }
        if (event.number==seven  && !event.value && !ltPressed)         //rt
        {
            rtPressed=false;
            throttleValue=midThrottle;
        }
        if (event.number==six  && event.value && !rtPressed)            //lt
        {
            ltPressed=true;
            throttleValue=1250;
        }
        if (event.number==six  && !event.value && !rtPressed)           //lt
        {
            ltPressed=false;
            throttleValue=midThrottle;
        }
        if (event.number==one && event.value)                   //a  //arming
        {
            if (!recording)
            {
                startRecord();
            }
            else
            {
                stopRecord();
            }
        }
        break;
    case 8:
        if (event.number==five )                    //rb //arming
        {
            startArming(event.value);
        }
        if (event.number==four  && event.value )     //lb                //turn of copter(if smth goes wery wery wrong)
        {
            disconnectFromCopter();
        }

        if (event.number==zero && event.value)                   //a  //arming
        {
            if (!recording)
            {
                startRecord();
            }
            else
            {
                stopRecord();
            }
        }
        break;

    }
}

void JoyStickInput::casualSticks(js_event event)
{
    const int thr_const=1;
    const int roll_const=10;
    const int pit_const=10;
    const int yaw_const=10;

    size_t axis;
    switch (countOfSticks)
    {
    case 6:
        axis = getAxisState(&event, axes);
        if (axis < 3)
        {                                               //minimum axis is -32767
            if (axis==0)
            {
                pitchValue = 1500 - axes[axis].y/50/pit_const;
                rollValue = 1500 + axes[axis].x/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}

            }
            if (axis==1)
            {
                yawValue = 1500 + axes[axis].x/50/yaw_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}

            }
        }
        break;
    case 8:
        axis = getAxisState(&event, axes);
        if (axis < 3)
        {                                                //minimum axis is -32767
            if (axis==0)
            {

                rollValue = 1500 + axes[axis].x/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}


            }
            if (axis==1)
            {
                if (axes[axis].x>10000 && !rtPressed )                          //lt
                {
                    ltPressed=true;
                    throttleValue=1250;
                }
                if (axes[axis].x<10000 && !rtPressed )                          //lt
                {
                    ltPressed=false;
                    throttleValue=midThrottle;
                }
                yawValue = 1500 + axes[axis].y/50/roll_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}

            }
            if (axis==2)
            {

                pitchValue = 1500 - axes[axis].x/50/pit_const;
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}
                if (axes[axis].y>10000  && !ltPressed)                            //rt
                {
                    rtPressed=true;
                    throttleValue=1550;
                }
                if (axes[axis].y<10000  && !ltPressed)                            //rt
                {
                    rtPressed=false;
                    throttleValue=midThrottle;
                }
            }
        }
        break;


    }
}

void JoyStickInput::usualExperimentalSticks(js_event event)
{
    const int thr_const=1;
    const int roll_const=10;
    const int pit_const=10;
    const int yaw_const=10;

    size_t axis;
    switch (countOfSticks)
    {
    case 6:
        axis = getAxisState(&event, axes);
        if (axis < 3)
        {                                                //minimum axis is -32767
            if (axis==0)
            {
                pitchValue = 1500 - axes[axis].y/50/pit_const;
                rollValue = 1500 + axes[axis].x/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}

            }
            if (axis==1)
            {
                yawValue = 1500 + axes[axis].x/50/yaw_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}

            }
        }
        break;
    case 8:
        axis = getAxisState(&event, axes);
        if (axis < 3)
        {                                                //minimum axis is -32767
            if (axis==0)
            {

                rollValue = 1500 + axes[axis].x/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}

                pitchValue = 1500 - axes[axis].y/50/pit_const;
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}


            }
            if (axis==1)
            {
                lastLT=axes[axis].x;
                yawValue = 1500 + axes[axis].y/50/roll_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}

            }
            if (axis==2)
            {

                lastRT=axes[axis].y;
            }
        }
        break;
    }
}


void JoyStickInput::usualExperimentalButtons(js_event event)
{

    unsigned char seven=7;
    unsigned char six=6;
    unsigned char five=5;
    unsigned char four=4;
    unsigned char three=3;
    unsigned char two=2;
    unsigned char one=1;
    unsigned char zero=0;

    switch (countOfSticks)
    {
    case 6:                            //Dinput
        if (event.number==seven)                     //arming    //rt
        {
            startArming(event.value);
        }
        if (event.number==five  && event.value )      //rb         //turn of copter(if smth goes wery wery wrong)
        {
            disconnectFromCopter();
        }
        if (event.number==one && event.value)         //a
        {
            if (!recording)
            {
                startRecord();
            }
            else
            {
                stopRecord();
            }
        }
        break;
    case 8:
        if (event.number==five )                    //rb //arming
        {
            startArming(event.value);
        }
        if (event.number==four  && event.value )     //lb                //turn of copter(if smth goes wery wery wrong)
        {
            disconnectFromCopter();
        }

        if (event.number==zero && event.value)                   //a  //arming
        {
            if (!recording)
            {
                startRecord();
            }
            else
            {
                stopRecord();
            }
        }
        break;

    }
}

void JoyStickInput::fullRtSticks(js_event event)
{
    const int thr_const=1;
    const int roll_const=10;
    const int pit_const=10;
    const int yaw_const=10;

    size_t axis;
    switch (countOfSticks)
    {
    case 6:
        axis = getAxisState(&event, axes);
        if (axis < 3)
        {                                                //minimum axis is -32767
            if (axis==0)
            {
                pitchValue = 1500 - axes[axis].y/50/pit_const;
                rollValue = 1500 + axes[axis].x/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}

            }
            if (axis==1)
            {
                yawValue = 1500 + axes[axis].x/50/yaw_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}

            }
        }
        break;
    case 8:
        axis = getAxisState(&event, axes);
        if (axis < 3)
        {                                                //minimum axis is -32767
            if (axis==0)
            {

                rollValue = 1500 + axes[axis].x/50/roll_const;
                if (rollValue>2100){rollValue=2099;}
                if (rollValue<900){rollValue=901;}

                pitchValue = 1500 - axes[axis].y/50/pit_const;
                if (pitchValue>2100){pitchValue=2099;}
                if (pitchValue<900){pitchValue=901;}


            }
            if (axis==1)
            {
                lastLT=axes[axis].x;
                yawValue = 1500 + axes[axis].y/50/roll_const;
                if (yawValue>2100){yawValue=2099;}
                if (yawValue<900){yawValue=901;}

            }
            if (axis==2)
            {

                lastRT=axes[axis].y;
            }
        }
        break;
    }
}










void JoyStickInput::startArming(bool pressed)
{
    if (pressed)
    {
        printf("##################___arming___######################");
        throttleValue=930;
        lastLT=32767;
        lastRT=-32767;
        throttleValueFromJS=1500;
        CH5Value=1900;
        arming =true;
    }
    else
    {
        if (arming)
        {
            throttleValue=1100;
            throttleValueFromJS=1500;
            lastLT=-32767;
            lastRT=-32767;
            arming=false;
        }
    }
}

void JoyStickInput::disconnectFromCopter()
{
    CH5Value=900;
}

int JoyStickInput::sign(int val)
{
    int result=0;
    if (val >100){result=1;}
    if (val <-100){result=-1;}
    return result;
}


void JoyStickInput::startRecord()
{
    //recording=true;
    //recordData =  ControllRecord();

}

void JoyStickInput::stopRecord()
{
    //printf("##################___writing___######################");

    // recording=false;
    //recordData.Save();
}

void JoyStickInput::setUsualCurrentMode()
{
    currentMode=0;
}


void JoyStickInput::setInertiaCurrentMode()
{
    currentMode=1;
}

void JoyStickInput::setCasualCurrentMode()
{
    currentMode=2;
}

void JoyStickInput::setRTLTUsialMode()
{
    currentMode=3;
}

void JoyStickInput::setRTLTFullMode()
{
    currentMode=4;
}
void JoyStickInput::timerForThrottle()
{
    std::thread thr([this]()
    {
        while(true)
        {
            if (currentMode==1)
            {
                throttleValue+=sign(throttleValueFromJS-1500);
                if (throttleValue>1800){throttleValue=1799;}
                if (throttleValue<900){throttleValue=901;}
            }
            if (currentMode==3)
            {
                throttleValue=1300+(lastRT-lastLT)/188;
                if (throttleValue>1800){throttleValue=1799;}
                if (throttleValue<900){throttleValue=901;}
            }
            if (currentMode==4)
            {
                throttleValue=1300+(lastRT-lastLT)/85;
                if (throttleValue>2100){throttleValue=2099;}
                if (throttleValue<900){throttleValue=901;}
            }
            usleep(30000);
        }
    });
    thr.detach();
}
