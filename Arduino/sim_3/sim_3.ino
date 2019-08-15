#include <SoftwareSerial.h>
SoftwareSerial sim808(11, 10); //Arduino(RX), Arduino(TX)
//Arduino(RX) to SIM808(TX)
//Arduino(TX) to SIM808(RX)

char phone_no[] = "0929034450";// replace with your phone no.
String data[5];
#define DEBUG true
String state,timegps,latitude,longitude;

void setup() {
  
sim808.begin(9600);
Serial.begin(9600);
delay(50);

getGPSLocation();

}

void loop() {

if (Serial.available()>0)
   sim808.write(Serial.read());
   if (sim808.available()>0)
   Serial.write(sim808.read());

}

void getGPSLocation()
{
//sim808.print("AT+CSMP=17,167,0,0");  // set this parameter if empty SMS received
delay(100);
sim808.print("AT+CMGF=1r");//configure SIM to TEXT mode
delay(400);
sendData("AT+CGNSPWR=1",1000,DEBUG);//Turn on GPS(GNSS - Global Navigation Satellite System)
delay(50);
sendData("AT+CGNSSEQ=RMC",1000,DEBUG);

delay(150);

//--------------------- send SMS containing google map location---------
sendTabData("AT+CGNSINF",1000,DEBUG);//Get GPS info(location
if (state !=0) {
Serial.println("State  :"+state);
Serial.println("Time  :"+timegps);
Serial.println("Latitude  :"+latitude);
Serial.println("Longitude  :"+longitude);


sim808.print("AT+CMGS=");
sim808.print(phone_no);
sim808.println("");

delay(300);

sim808.print("http://maps.google.com/maps?q=loc:");
sim808.print(latitude);
sim808.print(",");
sim808.print (longitude);
delay(200);
sim808.println((char)26); // End AT command with a ^Z, ASCII code 26
delay(200);
sim808.println();
delay(20000);
sim808.flush();
Serial.println("GPS Location sent! Check your mobile phone…");
} else {
Serial.println("GPS Initializing…");
}
//----------------------
}


void sendTabData(String command , const int timeout , boolean debug){

sim808.println(command);
long int time = millis();
int i = 0;

while((time+timeout) > millis()){
while(sim808.available()){
char c = sim808.read();
if (c != ',') {
data[i] +=c;
delay(100);
} else {
i++;
}
if (i == 5) {
delay(100);
goto exitL;
}
}
}exitL:
if (debug) {
state = data[1];
timegps = data[2];
latitude = data[3];
longitude =data[4];
}
}
String sendData (String command , const int timeout ,boolean debug){
String response = "";
sim808.println(command);
long int time = millis();
int i = 0;

while ( (time+timeout ) > millis()){
while (sim808.available()){
char c = sim808.read();
response +=c;
}
}
if (debug) {
Serial.print(response);
}
return response;
}
