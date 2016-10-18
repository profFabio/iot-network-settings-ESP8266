# iot-network-settings-ESP8266
Provide a way to receive the network settings (ssid and pass) wirelessly to the IoT device made with esp8266.
You can use it together with the cordova app, to config your device with your smartphone. Check it out here:

built for arduino-esp8266 sdk - https://github.com/esp8266/Arduino

## ChangeLog

* 0.1 - initial commit

## Motivation

When you are developing an IoT device with ESP8266, you need it to connect to a wifi network to send and receive data. To connect it to a wifi network, you need the wifi network credentials (ssid and pass). And you need a fancy and easy way to configure it, since you want that an avareage user could configure your device.

This library provides you an easy way to configure the device, receiving the wifi network credentials wirelessly. 

To send the credential wirelessly, you can use my smartphone solution (checkout here) or send it by your own application*. 

## Installation

1. Configure your arduino ide to compile and upload programs to ESP8266 (Arduino core for ESP8266 - details https://github.com/esp8266/Arduino)*
2. Install iot-network-settings-ESP8266 as Arduino Library 

## Limitation

* the network info (ssid and pass) recevied is not encrypted
* handle just WPA2, WPA and WEP networks. does not handle open networks, networks with certificates or with login pages.  

## Usage

See the samples. Nubix library will handle the config and connection step. Once connected in a wifi network, you gain control and can use the Wifi Layer to send and receive data. 

\* if you don't want to use my smartphone solution to send the network info, you can connect to the wifi network made by ESP8266 in the NUBIX_NOT_CONFIGURED state, open a TCP socket to the server ip (by default 192.168.4.1) using the library port (default port: 9402) and send an string with this pattern (change SSID and PASS by the values you want to send):

 ```NI:ssid,pass ```

## State

The library works in a state machine. The picture helps you to understand the states and how they changes

[[https://github.com/odelot/iot-network-settings-ESP8266/blob/master/img/states.png|alt=states]]
