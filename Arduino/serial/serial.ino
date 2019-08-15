void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  Serial.println();
}
void loop(){ 
 int mic = analogRead(A0);
 Serial.print("mic: "); 
 Serial.println(mic); 
}
