void setup()   {   
    Serial.begin(9600);
    pinMode(A3,INPUT_PULLUP); 
    pinMode(A2,INPUT_PULLUP); 
    pinMode(A1,INPUT_PULLUP);       
    pinMode(A0,INPUT_PULLUP); 
}
int x=60;//hoành độ khảo sát
byte button;
void loop(){
    if (button==3) {
        x--;// sang trái
    } else if(button==1) {
        x++;//sang phải
    }
    Serial.println(x);
}
