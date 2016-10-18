#include "Nubix.h"


//creates a random ssid with nubix prefix
String Nubix::getServerSSID () {
  String ssid = "nubix_";
  randomSeed(analogRead(A0));
  for (int i= 0; i< 5; i+=1) {
      int r = random (0,10);
      ssid+= r;
  }
  return ssid;
    
}

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}

//config esp to AP mode to receive connection and the configuration info
void Nubix::initConfigState () {
  WiFi.disconnect();
  delay(100);
  
  WiFi.mode(WIFI_AP);
  String serverSSID = getServerSSID();
  Log::d(serverSSID);
  WiFi.softAP(serverSSID.c_str());
  delay(10000);
  IPAddress myIP = WiFi.softAPIP();

  #ifdef NUBIX_DEBUG 
      Log::d(PSTR("Nubix::Server_IP "));
      Log::d(IpAddress2String(myIP));
      Log::d(PSTR("Starting server..."));
  #endif

  
  server.begin();
  delay(500);
}

//config esp to STA mode and try to connect to wifi with the storaged info
void Nubix::initConnectionState () {
  char ssid[32];
  char password[63];
  flash.getSSID (ssid);
  flash.getPassword (password);
  #ifdef NUBIX_DEBUG
    Log::d(String("SSID - Arduino"));
    Log::d( String(ssid));
    Log::d(String("Password - Arduino"));
    Log::d( String(password));
  #endif
  WiFi.disconnect();
  delay(100);
  WiFi.mode(WIFI_STA);  
  WiFi.begin(ssid, password);
  delay(500);
}

bool Nubix::receiveConfigInfo () {
    bool result = false;
    WiFiClient client = server.available();        // Check if a client has connected
    if (!client) {
      return result;
    }
    // Wait until the client sends some data
    while (!client.available()) {
      delay(1);
    }
    delay (10); 
    String ret = client.readStringUntil('\r');     // Read the first line of the request
    if (!ret.equals ("")) {
      //tem alguma coisa para analisar
      if (ret.startsWith ("NI:")) {
        //é nossa msg
        ret.replace ("NI:", "");
        ret.trim ();
        String ssid = ret.substring (0, ret.indexOf(","));
        String pass = ret.substring (ret.indexOf(",") + 1);
        char ssid_eeprom[32];
        memset(ssid_eeprom, '\0', sizeof (ssid_eeprom));
        char pass_eeprom[63];
        memset(pass_eeprom, '\0', sizeof (pass_eeprom));
        ssid.toCharArray (ssid_eeprom, sizeof (ssid_eeprom), 0);
        pass.toCharArray (pass_eeprom, sizeof (pass_eeprom), 0);
        flash.setSSID (ssid_eeprom);
        flash.setPassword (pass_eeprom);
        result = true;
        
      }
    }
    client.flush();
    client.stop();
    return result;                                 
}

//initialize nubix
void Nubix::setup () {
  
  flash.init ();
   Log::d(String ("Nubix::setup"));
  //flash.saveState (17);
  state = 0;
  status (state);
  initConfigState ();
  
  
}

void Nubix::loop () {
  byte memState = flash.readState ();
  byte state = getState ();
  if (state == Nubix::NUBIX_NOT_CONFIGURED) {
    if (flash.readState () == Nubix::NUBIX_NOT_CONFIGURED) {
      if (WiFi.getMode()!=WIFI_AP)
        initConfigState ();
    }
    if (memState == Nubix::NUBIX_NOT_CONFIGURED) {
      if (receiveConfigInfo () == true) {
        setState (Nubix::NUBIX_CONNECTING);
        //flash.saveState (Nubix::NUBIX_CONNECTING);
      }
    } else {
      setState (Nubix::NUBIX_CONNECTING);      
    }
  } else 
  if (state == Nubix::NUBIX_CONNECTING) {
    initConnectionState ();
    if (waitConnection (connTimeout)) {
      byte currentState = flash.readState ();
      if (currentState == Nubix::NUBIX_NOT_CONFIGURED) {
        flash.saveState (Nubix::NUBIX_VALID);
      }
      setState (Nubix::NUBIX_VALID);      
    } else {
      //não se conectou
      byte currentState = flash.readState ();
      if (currentState == Nubix::NUBIX_NOT_CONFIGURED) {
        //never connected... back to state 0 
        setState (Nubix::NUBIX_NOT_CONFIGURED);
        
      }      
    }    
  } else if (state == Nubix::NUBIX_VALID) {
    setState (Nubix::NUBIX_CONNECTED);
  } else if (state == Nubix::NUBIX_CONNECTED) {
    if (WiFi.status() != WL_CONNECTED) {
      setState (Nubix::NUBIX_CONNECTING);     
    } else {
      myLoop ();
    }
  }

  status (getState ());
  
}

 void Nubix::myLoop () {
  
 }

bool Nubix::waitConnection (long timeout) {
  long init = millis ();
  Log::d(String("WC"));  
  while (WiFi.status() != WL_CONNECTED && ((millis () - init) < timeout)) {
    delay (500);
    Log::d(String("."));
  }
  if (WiFi.status() == WL_CONNECTED)
    return true;
  else
    return false;

}

//change connection timeout
void Nubix::setConnectionTimeout (long connectionTimeout){
  connTimeout = connectionTimeout;
}

byte Nubix::getState () {
  return state;
}

void Nubix::status (byte nubix_state) {

}

void Nubix::changeState (byte _old, byte _new) {
  
}

void Nubix::setState (byte _state) {
  if (state != _state) {
    changeState (state,_state);    
  }
  state = _state;
}


