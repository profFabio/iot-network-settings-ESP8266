#ifndef __NUBIX_H_
#define __NUBIX_H_

#include "Flash.h"

#define DEFAULT_FLASH_OFFSET 0
#define DEFAULT_SERVER_PORT 9402
#define DEFAULT_CONNECTION_TIMEOUT 30000 //30 seconds

class Nubix {

public:
  Nubix () : flash (DEFAULT_FLASH_OFFSET), server (DEFAULT_SERVER_PORT), connTimeout (DEFAULT_CONNECTION_TIMEOUT) {};
  Nubix (int eeprom_offset, int server_port) : flash(eeprom_offset), server (server_port), connTimeout (DEFAULT_CONNECTION_TIMEOUT) {};

  const static byte NUBIX_NOT_CONFIGURED = 0;
  const static byte NUBIX_CONNECTING = 1;
  const static byte NUBIX_VALID = 2;
  const static byte NUBIX_CONNECTED = 3;
 
  void setup ();
  void loop ();
  byte getState ();
  virtual void status (byte nubix_state);
  virtual void changeState (byte _old, byte _new);

  void setConnectionTimeout (long connectionTimeout);
    

protected:
  virtual void myLoop ();
  void setState (byte state);
  String getServerSSID ();
  void initConfigState ();
  bool receiveConfigInfo ();
  void initConnectionState ();
  bool waitConnection (long timeout);
  
  Flash flash;
  byte state;
  long connTimeout;

  WiFiClient client[2];
  WiFiServer server;

};

#endif
