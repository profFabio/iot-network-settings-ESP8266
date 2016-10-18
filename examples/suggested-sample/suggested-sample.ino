//suggested-sample
//
//this way, your main loop will be inside a class that extends the Nubix class
//you can handle state changes 

#include <Flash.h>
#include <Log.h>
#include <Nubix.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

#include "MyNubix.h"

MyNubix myNubix;

//You can change the eeprom offset and the server port
//int eeprom_offset = 0;
//int server_port = 9402;
//MyNubix myNubix(eeprom_offset,server_port);

void setup() {  
  myNubix.setup ();
}

void loop() {
  myNubix.loop ();  
}
