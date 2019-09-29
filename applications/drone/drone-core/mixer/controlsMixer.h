#ifndef CONTROLSMIXER_H
#define CONTROLSMIXER_H

#include <copterInputs.h>
#include <joystickInterface.h>



class ControlsMixer
{
public:
    class ChannelOperation
    {
        int defaultValue = 0;
        int min;
        int max;
        int outputNumber;
    };


    std::string name =  "Default";
    virtual bool mix(JoystickState &state, CopterInputs &outputs);

    int currentMode=0;  // switch stick-channel mapping

    ControlsMixer();
private:
     void usualMode(JoystickState &state, CopterInputs &outputs, bool xInputOn);
};

#endif // CONTROLSMIXER_H
