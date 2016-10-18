#ifndef __MYNUBIX_H_
#define __MYNUBIX_H_

#include <Nubix.h>

class MyNubix : public Nubix {

public:

  MyNubix () { }
  
  MyNubix (int eeprom_offset, int server_port) : Nubix (eeprom_offset,server_port) { }

  //your own setup
  void mySetup () {
    Serial.println ("your setup");
    Serial.begin (9600);
    pinMode (redLedPin,OUTPUT);
    pinMode (yellowLedPin,OUTPUT);
    pinMode (greenLedPin,OUTPUT);
    digitalWrite (redLedPin,LOW);
    digitalWrite (yellowLedPin,LOW);
    digitalWrite (greenLedPin,LOW);
    
  }

  //your own loop
  void myLoop () {
    Serial.println ("do your stuff here");
  }

  //called evertime a state changes (good to give some sort of feedback to the user)
  void changeState (byte _old, byte _new) {
    if (_new == NUBIX_CONNECTING || _new == NUBIX_VALID) {
      digitalWrite (redLedPin,LOW);
      digitalWrite (yellowLedPin,HIGH);
      digitalWrite (greenLedPin,LOW);
    }
    if (_new == NUBIX_CONNECTED) {
      digitalWrite (redLedPin,LOW);
      digitalWrite (yellowLedPin,LOW);
      digitalWrite (greenLedPin,HIGH);
    }
    
  }

  //receives the current status (called in the setup step and after each nubix loop)
  void status (byte nubix_state) {
    if (nubix_state == NUBIX_NOT_CONFIGURED) {
      digitalWrite (redLedPin,HIGH);
      digitalWrite (yellowLedPin,LOW);
      digitalWrite (greenLedPin,LOW);
    }
  }

  

private:

  byte redLedPin = 12;
  byte yellowLedPin = 14;
  byte greenLedPin = 4;

};

#endif
