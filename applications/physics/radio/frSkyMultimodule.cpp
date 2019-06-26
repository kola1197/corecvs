#include <bitset>
#include <memory.h>
#include <vector>

#include "frSkyMultimodule.h"

using namespace std;

void FrSkyMultimodule::pack(int16_t channels[], uint8_t message[])
{
    int yawValue       = channels[CHANNEL_YAW];
    int rollValue      = channels[CHANNEL_ROLL];
    int pitchValue     = channels[CHANNEL_PITCH];
    int throttleValue  = channels[CHANNEL_THROTTLE];
    int CH5Value       = channels[CHANNEL_4];
    int CH6Value       = channels[CHANNEL_5];
    int CH7Value       = channels[CHANNEL_6];
    int CH8Value       = channels[CHANNEL_7];

    const int difference = MAGIC_DIFFERENCE;

    std::vector<uint8_t>  flyCommandFromUs = {0x55, 0x0F, 0x19, 0x00, 0x00,
                                              0x04, 0x20, 0x00, 0x00, 0x0F,
                                              0x10, 0x00, 0x02, 0x10, 0x80,
                                              0x00, 0x04, 0x20, 0x00, 0x01,
                                              0x08, 0x40, 0x00, 0x02, 0x10, 0x80};

    int k = throttleValue - difference;                    //858- min value
    k = k * 8 / 10;
    unsigned short sh1 = k;
    bitset<32> bitsRoll {sh1};

    bitset<8> firstByte {0};
    bitset<8> secondByte {0};
    bitset<8> thirdByte {0};
    bitset<8> fourthByte {0};
    bitset<8> fifthByte {0};
    bitset<8> sixthByte {0};
    bitset<8> seventhByte {0};
    bitset<8> eigthByte {0};
    bitset<8> ninethByte{0};
    bitset<8> tenthByte{0};
    bitset<8> eleventhByte{0};
    bitset<8> twelfthByte{0};


    for (int i=0;i<7;i++)
    {
        firstByte[i+1]=bitsRoll[i];
    }
    secondByte[0]=bitsRoll[7];
    secondByte[1]=bitsRoll[8];
    secondByte[2]=bitsRoll[9];

    k=rollValue-difference;
    k=k*8/10;
    sh1=k;
    bitset<32> bitspitch{sh1};
    for (int i=0;i<4;i++)
    {
        secondByte[i+4]=bitspitch[i];
    }
    for (int i=0;i<7;i++)
    {
        thirdByte[i]=bitspitch[i+4];
    }


    k=pitchValue-difference;
    k=k*8/10;
    sh1=k;
    bitset<32> bitsthrottle{sh1};

    thirdByte[7]=bitsthrottle[0];
    for (int i=0;i<8;i++)
    {
        fourthByte[i]=bitsthrottle[i+1];
    }
    fifthByte[0]=bitsthrottle[9];

    k=yawValue-difference;
    k=k*8/10;
    sh1=k;
    bitset<32> bitsyaw{sh1};

    for (int i=0;i<6;i++)
    {
        fifthByte[i+2]=bitsyaw[i];
    }
    for (int i=0;i<5;i++)
    {
        sixthByte[i]=bitsyaw[i+6];
    }

    k=CH5Value-difference;
    k=k*8/10;
    sh1=k;
    bitset<32> bitsCH5{sh1};

    for (int i=0;i<7;i++)
    {
        seventhByte[i]=bitsCH5[i+3];
    }
    for (int i=0;i<3;i++)
    {
        sixthByte[i+5]=bitsCH5[i];
    }

    k=CH6Value-difference;
    k=k*8/10;
    sh1=k;
    bitset<32> bitsCH6{sh1};

    for (int i=0;i<8;i++)
    {
        eigthByte[i]=bitsCH6[i];
    }
    for (int i=0;i<3;i++)
    {
        ninethByte[i]=bitsCH6[i+8];
    }

    k=CH7Value-difference;
    k=k*8/10;
    sh1=k;
    bitset<32> bitsCH7{sh1};

    for (int i=0;i<6;i++)
    {
        ninethByte[i+3]=bitsCH7[i];
    }
    for (int i=0;i<7;i++)
    {
        tenthByte[i]=bitsCH7[i+5];
    }

    k=CH8Value-difference;
    k=k*8/10;
    sh1=k;
    bitset<32> bitsCH8{sh1};

    for (int i=0;i<8;i++)
    {
        eleventhByte[i]=bitsCH8[i+2];
    }
    tenthByte[7]=bitsCH8[1];
    tenthByte[6]=bitsCH8[0];
    twelfthByte[0]=bitsCH8[10];

    uint8_t fb=firstByte.to_ulong();
    flyCommandFromUs[4]=fb;

    fb=secondByte.to_ulong();
    flyCommandFromUs[5]=fb;

    fb=thirdByte.to_ulong();
    flyCommandFromUs[6]=fb;

    fb=fourthByte.to_ulong();
    flyCommandFromUs[7]=fb;

    fb=fifthByte.to_ulong();
    flyCommandFromUs[8]=fb;

    fb=sixthByte.to_ulong();
    flyCommandFromUs[9]=fb;

    fb=seventhByte.to_ulong();
    flyCommandFromUs[10]=fb;

    fb=eigthByte.to_ulong();
    flyCommandFromUs[11]=fb;

    fb=ninethByte.to_ulong();
    flyCommandFromUs[12]=fb;

    fb=tenthByte.to_ulong();
    flyCommandFromUs[13]=fb;


    fb=eleventhByte.to_ulong();
    flyCommandFromUs[14]=fb;


    fb=twelfthByte.to_ulong();
    flyCommandFromUs[15]=fb;

    memcpy(message, flyCommandFromUs.data(), sizeof(uint8_t) * MESSAGE_SIZE);


}

/**

    Ti - are CH0 (throttle) bits
    Ri - are CH1 (Roll)     bits
    Pi - are CH2 (Pitch)    bits
    Yi - are CH3 (Yaw)      bits

    A, B, C, D - are CH4, CH5, CH6, CH7

       HEADER:
       | 31         [0x00]        24 | 23       [0x19]         16  |  15        [0x0F]        8  | 7         [0x55]        0  |
       |  0  0  0  0     0  0  0  0  |  0  0  0  1     1  0  0  1  |  0  0  0  0     1  1  1  1  | 0  1  0  1     0  1  0  1  |


       DATA:
       | 63                       56 | 55                       48 |  47                      40 | 39                      32 |
       |  P8 P7 P6 P5    P4 P3 P2 P1 |  P0 0  R9 R8    R7 R6 R5 R4 |  R3 R2 R1 R0    0  T9 T8 T7 | T6 T5 T4 T3    T2 T1 T0 0  |

       | 95                       88 | 87                       80 |  79                      72 | 71                      64 |
       |  B7 B6 B5  B4   B3 B2 B1 B0 |  0  A9 A8 A7    A6 A5 A4 A3 |  A2 A1 A0 00    Y9 Y8 Y7 Y6 | Y5 Y4 Y3 Y2    Y1 Y0 0  P9 |

       | 127        [0x00]       120 | 119                     112 |  111                    104 | 103                     96 |
       |  0  0  0  0     0  0  0  0  | D9 D8  D7 D6    D5 D4 D3 D2 |  D1 D0 0  C9    C8 C7 C6 C5 | C4 C3 C2 C1    C0  0 B9 B8 |

       FOOTER:
       | 159        [0x01]       152 | 151       [0x00]        144 |  143       [0x20]       136 | 135      [0x04]        128 |
       |  0  0  0  0     0  0  0  1  | 0  0  0   0     0  0  0  0  |  0  0  1  0     0  0  0  0  | 0  0  0  0     0  1  0  0  |

       | 191        [0x02]       184 | 183       [0x00]        176 |  175        [0x40]      168 | 167      [0x08]        160 |
       |  0  0  0  0     0  0  1  0  | 0  0  0   0     0  0  0  0  |  0  1  0  0     0  0  0  0  | 0  0  0  0     1  0  0  0  |

                                                                   |  207       [0x80]       200 | 199      [0x10]        192 |
                                                                   |  1  0  0  0     0  0  0  0  | 0  0  0  1     0  0  0  0  |


        0x55| 0x0F| 0x19| 0x00|
        0x00| 0x04| 0x20| 0x00|
        0x00| 0x0F| 0x10| 0x00|
        0x02| 0x10| 0x80| 0x00|
        0x04| 0x20| 0x00| 0x01|
        0x08| 0x40| 0x00| 0x02|
        0x10| 0x80


        More reference code for this message format can be found in OpenTX -
        https://github.com/opentx/opentx/blob/17b4aa24668bc4b223dd0613a48d2cc050e39358/radio/src/pulses/multi_arm.cpp

 **/

void FrSkyMultimodule::pack1(int16_t channels[], uint8_t message[])
{
    memset(message, 0, MESSAGE_SIZE * sizeof(uint8_t));

    uint32_t *mptr32 = (uint32_t *)&message[0];

    mptr32[0] = 0x00190F55U;
    mptr32[1] = ((channels[0] & MASK) <<  1) |
                ((channels[1] & MASK) << 12) |
                ((channels[2] & MASK) << 23) ;

    mptr32[2] = ((channels[2] & MASK) >>  9) |
                ((channels[3] & MASK) <<  2) |
                ((channels[4] & MASK) << 13) |
                ((channels[5] & MASK) << 24) ;

    mptr32[3] = ((channels[5] & MASK) >>  8) |
                ((channels[6] & MASK) <<  3) |
                ((channels[7] & MASK) << 14);

    mptr32[4] = 0x01002004U;
    mptr32[5] = 0x02004008U;

    message[24] = 0x10;
    message[25] = 0x80;

}
