#include "Shiftbrite.hpp"
#include "Arduino.h"


Shiftbrite::Shiftbrite(){}
Shiftbrite::Shiftbrite(int datapin, int latchpin, int enablepin, int clockpin){
    this->datapin=datapin;
    this->latchpin=latchpin;
    this->enablepin=enablepin;
    this->clockpin=clockpin;
    pinMode(datapin, OUTPUT);
    pinMode(latchpin, OUTPUT);
    pinMode(enablepin, OUTPUT);
    pinMode(clockpin, OUTPUT);
    digitalWrite(latchpin, LOW);
    digitalWrite(enablepin, LOW); 
    this->color=0x0000;
    this->level=2;
}
void Shiftbrite::setColor(int color){
    int blue=color&0x0000FF;
    int green=(color&0x00FF00)>>8;
    int red=(color&0xFF0000)>>16;
    
    this->SB_CommandMode = B00; // Write to PWM control registers
    this->SB_RedCommand = red*level; // Minimum red
    this->SB_GreenCommand = green*level; // Maximum green
    this->SB_BlueCommand = blue*level; // Minimum blue
    this->SB_SendPacket();
    Serial.print("canales de color:");
    Serial.print("Rojo:");Serial.println(red); 
    Serial.print("Verde:");Serial.println(green); 
    Serial.print("Azul:");Serial.println(blue); 
}
void Shiftbrite::setLevel(int level){
    if (level < 0) level=0;
    else if (level > 4) level=4;
}
void Shiftbrite::switchOff(){

}
void Shiftbrite::switchOn(){

}

void Shiftbrite::SB_SendPacket() {
   this->SB_CommandPacket = this->SB_CommandMode & B11;
   this->SB_CommandPacket = (this->SB_CommandPacket << 10)  | (this->SB_BlueCommand & 1023);
   this->SB_CommandPacket = (this->SB_CommandPacket << 10)  | (this->SB_RedCommand & 1023);
   SB_CommandPacket = (this->SB_CommandPacket << 10)  | (this->SB_GreenCommand & 1023);

   shiftOut(this->datapin, this->clockpin, MSBFIRST, this->SB_CommandPacket >> 24);
   shiftOut(this->datapin, this->clockpin, MSBFIRST, this->SB_CommandPacket >> 16);
   shiftOut(this->datapin, this->clockpin, MSBFIRST, this->SB_CommandPacket >> 8);
   shiftOut(this->datapin, this->clockpin, MSBFIRST, this->SB_CommandPacket);

   delay(1); // adjustment may be necessary depending on chain length
   digitalWrite(this->latchpin,HIGH); // latch data into registers
   delay(1); // adjustment may be necessary depending on chain length
   digitalWrite(this->latchpin,LOW);
}
