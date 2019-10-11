int incomingAudio;

void setup(){
  Serial.begin(2000000);
  for(int i=0; i<8; i++){
    pinMode(i,OUTPUT);
  }
}

void loop(){
//  incomingAudio = analogRead(A0);
//  Serial.println(incomingAudio);

  PORTD = 0;
  delay(1);
  PORTD = 127;
  delay(2);
  PORTD = 51;
  delay(1);
  PORTD = 255;
  delay(3);      
}
