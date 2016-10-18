#include "Flash.h"


Flash::Flash (int offset) 
{
  _offset = offset;
}


//preparando a memória flash
//(usamos 97 posições)
void Flash::init () {
    EEPROM.begin(256);
    #ifdef NUBIX_DEBUG 
      Log::d(PSTR("Flash::init"));
    #endif
    if (readState () > 16) {
      #ifdef NUBIX_DEBUG 
        Log::d(PSTR("iniciando memoria flash"));
      #endif
      
      //estado invalido - vamos resetar tudo-- TUDO!!!
      EEPROM.write (_offset,0);
      EEPROM.write (_offset + 1,0); //tipo de segurança. no mock eh a WPA2 
      
      //gravando 32 espaçoes para o SSID
      for (int i=0; i< 32; i+=1) {
         EEPROM.write ((_offset + 2) + i,(byte)'\0');
      }
      //gravando 63 espaçoes para a senha do wifi
      for (int i=0; i< 63; i+=1) {
         EEPROM.write ( (_offset + 34 ) +i,(byte)'\0');
    }

    //gravando 64 espaçoes para o id do dispositivo, um total de 18,446,744,073,709,551,615 de possiveis dispositivos (18 quintilhões)
    /*for (int i=0; i< 64; i+=1) {
       EEPROM.write (2+i,(byte)'0');
    }*/
    
    EEPROM.commit ();
  }
  
}



void Flash::setSSID (char* ssid) {
  //gravando 32 espaçoes para o SSID
    for (int i=0; i< 32; i+=1) {
       EEPROM.write ((_offset + 2)+i,(byte)ssid[i]);
    }
    EEPROM.commit ();
}

char* Flash::getSSID (char* ssid) {
  //lendo 32 espaçoes para o SSID
    for (int i=0; i< 32; i+=1) {
       ssid[i] = (char) EEPROM.read ((_offset + 2)+i);
    }
    return ssid;
}

void Flash::setPassword (char* password) {
  //gravando 63 espaçoes para a senha do wifi
    for (int i=0; i< 63; i+=1) {
       EEPROM.write ((_offset + 34)+i,(byte)password[i]);
    }
    EEPROM.commit ();
}

char*  Flash::getPassword (char* password) {
  //lendo 63 espaçoes para a senha do wifi
    for (int i=0; i< 63; i+=1) {
       password[i] = (char) EEPROM.read ((_offset + 34)+i);
    }
    return password;
}


/**

Estados
0 - incial
1 - ssid e password pegos
2 - ja se conectou alguma vez (ssid e pass validos)
3 - conectado e pronto para executar rotina
16 - PANICC!!!! - corram para as colinas, erro irrecuperavel - resete e reze

*/
 byte Flash::readState () {
  return EEPROM.read (_offset);
}

/**

Estados
0 - incial
1 - ssid e password pegos
2 - ja se conectou alguma vez (ssid e pass validos)
3 - conectado e pronto para executar rotina
16 - PANICC!!!! - corram para as colinas, erro irrecuperavel - resete e reze

*/
 void Flash::saveState (byte state) {
  //Log::d (String ("saveState:"+state)); 
  EEPROM.write (_offset,state);
  EEPROM.commit ();
}
