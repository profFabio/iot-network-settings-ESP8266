//simplest-sample
//
//this way, you don't need to implement a class extending the 
//Nubix class. It is very simple, but using the lib this way
//you cannot control the state changes (to give user some 
//sort of feedback)

#include <Flash.h>
#include <Log.h>
#include <Nubix.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

Nubix nubix;

//You can change the eeprom offset and the server port
//int eeprom_offset = 0;
//int server_port = 9402;
//Nubix nubix(eeprom_offset,server_port);

void setup() {
  Serial.begin (9600);
  nubix.setup ();
}

void loop() {
  nubix.loop ();
  if (nubix.getState() == Nubix::NUBIX_CONNECTED) {
    Serial.println ("do your stuff");
  }
}
