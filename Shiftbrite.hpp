#ifndef Shiftbrite_hpp
#define Shiftbrite_hpp

#include "Arduino.h"


class Shiftbrite
{
  public:
    Shiftbrite();
    Shiftbrite(int datapin, int latchpin, int enablepin, int clockpin);
    void setColor(int color);
    void setLevel(int level);
    void switchOff();
    void switchOn();
  private:
    void SB_SendPacket();
    int level;
    int color;
    int datapin;
    int latchpin;
    int enablepin;
    int clockpin;
    unsigned long SB_CommandPacket;
    int SB_CommandMode;
    int SB_BlueCommand;
    int SB_RedCommand;
    int SB_GreenCommand;
};
#endif
