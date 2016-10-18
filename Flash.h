#ifndef __FLASH_H_
#define __FLASH_H_

#include <EEPROM.h>
#include "Log.h"

class Flash {
  
public:
  Flash (int offset);
  
  void init ();
  void setSSID (char* ssid);
  char* getSSID (char* ssid);
  void setPassword (char* password);
  char*  getPassword (char* password);
  byte readState ();
  void saveState (byte state);

private :
  int _offset;
  
};

#endif
