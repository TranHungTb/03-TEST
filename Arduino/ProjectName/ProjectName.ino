
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;
int led7 = 8;
int led8 = 9;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  digitalWrite(2, HIGH);                
  digitalWrite(3, HIGH); 
  digitalWrite(4, HIGH);                  
  digitalWrite(5, HIGH); 
  digitalWrite(6, HIGH);                 
  digitalWrite(7, HIGH); 
  digitalWrite(8, HIGH);                
  digitalWrite(9, HIGH);     

}

// the loop function runs over and over again forever
void loop() {
  
  digitalWrite(2, LOW); 
  delay(500);                    
  digitalWrite(4, LOW); 
  delay(500);    
  digitalWrite(6, LOW); 
  delay(500);                    
  digitalWrite(8, LOW); 
  delay(500);   
  digitalWrite(3, LOW); 
  delay(500);                    
  digitalWrite(5, LOW); 
  delay(500);   
  digitalWrite(7, LOW); 
  delay(500);                    
  digitalWrite(9, LOW); 
  delay(500);   
  digitalWrite(2, HIGH);                   
  digitalWrite(3, HIGH);   
  digitalWrite(4, HIGH);                   
  digitalWrite(5, HIGH);   
  digitalWrite(6, HIGH);                   
  digitalWrite(7, HIGH);   
  digitalWrite(8, HIGH);                    
  digitalWrite(9, HIGH); 
  delay(500);      
 
}
