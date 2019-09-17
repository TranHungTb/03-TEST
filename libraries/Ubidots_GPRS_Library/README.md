# Ubidots Arduino GPRS Library 

**This library requires Arduino v1.6.0 or higher**

This is a library for the Arduino GPRS sim 900 

These modules use TTL Serial to communicate, 2 pins are required to interface
Be careful with jumpers, these will be like the photo:

<div style="text-align:center"><img src ="http://www.seeedstudio.com/wiki/images/thumb/5/50/GPRS_communicate_with_arduino_with_software_serial.jpg/400px-GPRS_communicate_with_arduino_with_software_serial.jpg" /></div>

## Components

* Arduino UNO
* Arduino GPRS shield sim 900
* Ubidots_GPRS library

## Pin Connection

To download. click the DOWNLOADS button in the top right corner, rename the uncompressed folder Ubidots_GPRS Check that the Ubidots_GPRS folder contains Ubidots_GPRS.cpp and Ubidots_GPRS.h

Place the Ubidots_GPRS library folder your *arduinosketchfolder*/libraries/ folder. 
You may need to create the libraries subfolder if its your first library. Restart the IDE.

## Steps to do a simple text with Arduino GPRS and Ubidots

1. Download the Ubidots_GPRS library [here](https://github.com/ubidots/ubidots-arduino-gprs/archive/1.0.0.zip)
2. Go to Arduino IDE, click on Sketch -> Include Library -> Add .zip Library
3. Select .zip file of Ubidots_GPRS, and just add it
4. Now go to File -> Examples -> Ubidots GPRS library and select get_value or save_value examples
5. Change your token, your id and run it!  

**Note: If you don't know how to add a new library to Arduino IDE press [here](https://www.arduino.cc/en/Guide/Libraries) and you can see the steps in Arduino page.**
