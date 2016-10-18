#ifndef __LOG__H_
#define __LOG__H_

#include <ESP8266WiFi.h>

#define NUBIX_DEBUG
#define NUBIX_ERROR
#define NUBIX_INFO

class Log {
  
  public:
    static void d (const char p[]) {
      #ifdef NUBIX_DEBUG
        byte c;
        Serial.print("d:");
        Serial.print (millis());
        Serial.print ("\t:");
        while (0 != (c = pgm_read_byte(p++))) {
      Serial.write(c);
        }
        Serial.print ("\n");
      #endif
    }
    
    static void d (String s) {
      #ifdef NUBIX_DEBUG
        byte c;
        Serial.print("d:");
        Serial.print (millis());
        Serial.print ("\t:");
        Serial.print (s);
        Serial.print ("\n");
      #endif
    }
    
    static void i (const char p[]) {
      #ifdef NUBIX_INFO
        byte c;
        Serial.print("i:");
        Serial.print (millis());
        Serial.print ("\t:");
        while (0 != (c = pgm_read_byte(p++))) {
      Serial.write(c);
        }
        Serial.print ("\n");
      #endif
    }
    
   static void e (const char p[]) {
      #ifdef NUBIX_ERROR
        byte c;
        Serial.print("e:");
        Serial.print (millis());
        Serial.print ("\t:");
        while (0 != (c = pgm_read_byte(p++))) {
      Serial.write(c);
        }
        Serial.print ("\n");
      #endif
    } 
    
    static void e (String s) {
      #ifdef NUBIX_ERROR
        byte c;
        Serial.print("e:");
        Serial.print (millis());
        Serial.print ("\t:");
        Serial.print (s);
        Serial.print ("\n");
      #endif
    }
    
    static void e (String*s) {
      #ifdef NUBIX_ERROR
        byte c;
        Serial.print("e:");
        Serial.print (millis());
        Serial.print ("\t:");
        Serial.print (s->c_str ());
        Serial.print ("\n");
      #endif
    }
  
};

#endif
