# iot-network-settings-ESP8266

Biblioteca construida para o ESP8266 com o SDK arduino (https://github.com/esp8266/Arduino) e fornece uma forma prática de configurar seu dispositivo IoT baseado no ESP8266 com os dados de acesso ao roteador wireless.

Uma das formas propostas de configuração é através do aplicativo android disponivel na Play Store (clique na imagem): 
<a href='https://play.google.com/store/apps/details?id=br.com.nubix.cordova.wifisettings&utm_source=global_co&utm_medium=prtnr&utm_content=Mar2515&utm_campaign=PartBadge&pcampaignid=MKT-Other-global-all-co-prtnr-py-PartBadge-Mar2515-1'><img alt='Disponível no Google Play' src='https://play.google.com/intl/en_us/badges/images/generic/pt-br_badge_web_generic.png' width="200px"/></a>

## ChangeLog

* 0.1 - Commit Inicial

## Motivação

Quando você está desenvolvendo um dispositivo IoT sem fio, com o ESP8266 por exemplo, é necessário que ele seja configurado com as informações necessarias (SSID da rede e senha, por exemplo) para acessar a rede wifi que contem internet.

Sugiro através dessa biblioteca uma forma simplificada de configuração, através do smartphone. É simples:

1. puxe a biblioteca ESP8266

2. puxe o aplicativo Android* 
<a href='https://play.google.com/store/apps/details?id=br.com.nubix.cordova.wifisettings&utm_source=global_co&utm_medium=prtnr&utm_content=Mar2515&utm_campaign=PartBadge&pcampaignid=MKT-Other-global-all-co-prtnr-py-PartBadge-Mar2515-1'><img alt='Disponível no Google Play' src='https://play.google.com/intl/en_us/badges/images/generic/pt-br_badge_web_generic.png' width="200px"/></a>

3. se preocupe somente com a programação fim do seu dispositivo

\* Você pode customizar o aplicativo Android e criar o seu. O codigo fonte está disponivel em:  https://github.com/profFabio/iot-network-settings-cordova

## Instalação

1. Configure a IDE do Arduino para compilar e fazer uploads de programas para o ESP8266  (Arduino sdk para ESP8266 - detalhes em https://github.com/esp8266/Arduino)
2. Instale a biblioteca iot-network-settings-ESP8266 como uma bilbioteca Arduino 

## Limitações

* Os dados da rede wifi são recebidos sem criptografia 
* Lida somente com acesso a redes wifi WPA2, WPA e WEP. Não lida com redes abertas, nem as que usam certificados ou paginas de login.  

## Maquina de estados

Veja a imagem para entender melhor como a biblioteca funciona.

![estados](https://github.com/odelot/iot-network-settings-ESP8266/blob/master/img/states.png)

## EEPROM

A biblioteca grava 97 bytes na memória eeprom. Você pode configurar um offset para gravar a partir de uma posição que não esteja em uso pela sua aplicação. Por padrão, o endereço inicial é o 0.

| Posição (some o offset)   | Descrição                                                            |
|---------------------------|----------------------------------------------------------------------|
|0                          |estado (da maquina de estado)                                         |
|1                          |tipo de segurança da conexão wifi (não utilizado por enquanto)        |
|2-33                       |SSID (recebido via wifi - no max. 32 posições)                        |
|34-96                      |password do wifi (recebido via wifi - no max 63 posições)             |

## Uso

### Uso mais simples

Veja o exemplo simplest-sample:

```
#include <Flash.h>
#include <Log.h>
#include <Nubix.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

Nubix nubix;

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
```

Use o aplicativo Android para enviar as configurações da rede wifi que o dispositivo deve se conectar.

Assim que a biblioteca conseguir as credenciais e se conectar, você pode executar seu código (na parte "do your stuff")

Veja o video mostrando esse procedimento:

### Uso sugerido

Veja o exemplo suggested-sample.

Nele, você verá que existe como controlar as mudanças de estado da maquina de estado da biblioteca.

### Customização

* Enviar configuração sem usar o aplicativo android

Você não necessariamente precisa utilizar o aplicativo android para enviar as configurações. Você pode se conectar ao dispositivo quando ele estiver no estado NUBIX_NOT_CONFIGURED, abrir um Socket TCP no ip do servidor (por padrão 192.168.4.1) usando a porta definida na biblioteca (porta padrão: 9402) e enviar uma string com o seguinte padrão (mude SSID e PASS pelos valores que você deseja enviar):
```
NI:ssid,pass
```
* Criar meu próprio aplicativo android para enviar configuração

O código fonte do aplicativo android, feito em cordova, está disponivel em: https://github.com/profFabio/iot-network-settings-cordova
Você pode customiza-lo ou absorvê-lo em sua aplicação
