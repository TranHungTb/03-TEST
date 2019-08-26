char buffer[4]= {}; // Biến đệm lưu giá trị
void setup() {
        Serial.begin(9600);     // mở serial với baudrate 9600
}

void loop() {
if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    Serial.println("Command Sent: " + command);
    Serial.println();
//    Serial.println("Nhan duoc:" + command);
  }
        // nếu còn có thể đọc được 
//        if (Serial.available() >= 3) {
//                // đọc chữ liệu
//                Serial.readBytes(buffer,3);
//                //Xuất dữ liệu
//                Serial.print("Toi nhan duoc: ");
//                Serial.println(buffer);
//        }
} 
