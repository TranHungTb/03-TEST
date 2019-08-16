const int ledPin = 13;   
 
void setup() { 
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);        
} 
 
void loop() { 
  digitalWrite(ledPin, HIGH);
  Serial.write(0);
  delay(1000);    
  digitalWrite(ledPin, LOW);
  Serial.write(1);
  delay(1000);
} 
