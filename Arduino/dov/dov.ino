float voltage = 0.0;

float temp=0.0;

int analog_value;

void setup()

{

Serial.begin(9600);


Serial.print("Digital Voltmeter ");
pinMode(2, INPUT_PULLUP);
pinMode(13, OUTPUT);
pinMode(A0, INPUT);
delay(3000);
digitalWrite(13,0);
}

void loop()

{

analog_value = analogRead(A0);

voltage = (analog_value * 5.0) / 1024.0;

if (voltage < 0.1)
{

voltage = 0.0;

}

if(digitalRead(2)==0){digitalWrite(13,1);}
else{digitalWrite(13,0);}
Serial.print("DIEN AP LA: ");

Serial.println(voltage);

Serial.print(" V");

delay(10);

}
