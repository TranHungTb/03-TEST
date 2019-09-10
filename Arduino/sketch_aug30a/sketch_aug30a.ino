#include <uspeech.h>
signal voice(A0);
char option = 0;
uint32_t power(uint32_t base, uint32_t exp);
 
void setup()
{
#if 0
    int minVolume;  /*!< Mức âm thanh tối thiểu mà bạn cho là nó sẵn sàng có thể thu được âm */
    int fconstant;  /*!< cài ngưỡng cho âm /f/ */
    int econstant;  /*!< cài ngưỡng cho âm /ee/, /i/,  */
    int aconstant;  /*!< cài ngưỡng cho âm /a/ /o/ /r/ /l/,  */
    int vconstant;  /*!< cài ngưỡng cho âm /z/ /v/ /w/,  */
    int shconstant; /*!< cài ngưỡng cho âm /sh/ /ch/,  /s/ */
    bool f_enabled; /*!<thiết lập này để ở false nếu bạn không muốn xác định âm /f/s */
    int amplificationFactor; /*!<Amplification factor: điều chỉnh khi cần*/
#endif
    analogReference(EXTERNAL);
 
    voice.f_enabled = true;
    voice.fconstant = 400;
    voice.econstant = 2; //3; //1 2;
    voice.aconstant = 4; //5; //2 4;
    voice.vconstant = 6; //7; //3 6;
    voice.shconstant = 8; //4;
    voice.amplificationFactor = 10;
    voice.micPowerThreshold = 80;
    voice.scale = 8;
    Serial.begin(9600);
 
#if 0
    while (1) {
        uint16_t sig = analogRead(A0);
  Serial.println(sig);
  delay(100);
    }
#endif
 
    Serial.println(F("Calibrating"));
    voice.calibrate();
    Serial.print(F("Calibrated at "));
    Serial.println(voice.calib);
    Serial.println(F("Ready"));
}
 
uint16_t lastMicPower=0;
char lastPhoneme = ' ';;
uint16_t lastCoeff=0;
uint16_t lastPower=0;
uint32_t lastChange = 0;
uint32_t startUsec = 0;
 
uint8_t col=0;
 
char buf[80];
 
struct history_s {
    int micPower;
    int coeff;
    char phoneme;
    char f_phoneme;
    uint32_t usecs;
} history[80];
 
uint32_t power(uint32_t base, uint32_t ex) 
{
    if (ex == 0)
  return 1;
    else if (ex % 2)
  return base * power(base, ex - 1);
    else {
  int temp = power(base, ex / 2);
  return temp * temp;
    }
}
 
void pad(uint32_t value, uint8_t places)
{
    uint32_t padValue = power(10, places);
 
    while (value < padValue) {
        Serial.print(' ');
  padValue /= 10;
    }
    Serial.print(value);
}
 
void loop()
{
    char phoneme = voice.getPhoneme();
    if (option==0) {
  Serial.println(F("uSpeech debug tool--------"));
  Serial.println(F(" nhan 'f' neu ban muon hieu chinh/kiem tra thong so f"));
  Serial.println(F(" nhan 'p' neu ban muon hieu chinh/kiem tra  getPhoneme"));
  Serial.println(F(" nhan 'v' neu ban muon hieu chinh/kiem tra  volume of your microphone"));
  Serial.println(F(" nhan 'c' neu ban muon hieu chinh/kiem tra  coeff"));
  option = 1;
    }
    if (Serial.available() > 0) {
  option = Serial.read();
    }
    switch (option) {
    case 'f': {
  uint16_t micPower = voice.micPower;
  if (micPower != lastMicPower) {
      Serial.print(F("micPower: "));
      Serial.println(micPower);
      lastMicPower = micPower;
  }
  }
  break;
    case 'p': {
  if (phoneme != lastPhoneme || phoneme != ' ') {
      if (col == 0) {
    startUsec = micros();
      }
      lastPhoneme = phoneme;
      buf[col] = phoneme;
      history[col].phoneme = phoneme;
      history[col].f_phoneme = voice.phoneme;
      history[col].coeff = voice.testCoeff;
      history[col].micPower = voice.micPower;
      history[col].usecs = micros() - startUsec;
      startUsec = micros();
      if (++col >= sizeof(buf)-1) {
          buf[col] = 0;
    Serial.println(F("phonemes"));
    for (uint8_t ind=0; ind<col; ind++) {
        Serial.print(F("    "));
        pad(history[ind].usecs,5);
        Serial.print(F(": '"));
        Serial.print(history[ind].phoneme);
        Serial.print('\'');
        Serial.print(F(" ("));
        Serial.print(history[ind].coeff);
        Serial.print(',');
        Serial.print(history[ind].micPower);
        Serial.println(')');
    }
    Serial.print(F("phoneme sequence: \""));
    Serial.print(buf);
    Serial.println('"');
          col = 0;
      }
      lastChange = millis();
  }
  if (col && ((millis() - lastChange) > 50)) {
      buf[col] = 0;
      Serial.println(F("phonemes"));
      for (uint8_t ind=0; ind<col; ind++) {
    Serial.print(F("    "));
    pad(history[ind].usecs,5);
    //Serial.print(history[ind].usecs);
    Serial.print(F(": '"));
    Serial.print(history[ind].phoneme);
    Serial.print('\'');
    Serial.print(F(" ("));
    Serial.print(history[ind].coeff);
    Serial.print(',');
    Serial.print(history[ind].micPower);
    Serial.print(')');
    if (history[ind].phoneme == 'f') {
        Serial.print(" '");
        Serial.print(history[ind].f_phoneme);
        Serial.println('\'');
    } else {
        Serial.println();
    }
      }
      col = 0;
      Serial.print(F("phoneme sequence: \""));
      Serial.print(buf);
      Serial.println('"');
      Serial.println(F("-----------------------------"));
  }
  }
  break;
    case 'v': {
  uint16_t power = voice.power();
  if (power != lastPower) {
      Serial.print(F("power:"));
      Serial.println(power);
      lastPower = power;
  }
  }
  break;
    case 'c': {
  uint16_t coeff = voice.testCoeff;
  if (coeff != lastCoeff) {
      Serial.print(F("coeff: "));
      Serial.println(coeff);
      lastCoeff = coeff;
  }
  }
  break;
    case 1:
  break;
    default:
  option = 0;
  if (col) {
      Serial.println();
      col = 0;
  }
  break;
    }
 
}
