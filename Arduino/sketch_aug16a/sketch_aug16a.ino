#include <EEPROMex.h>

char b[10]="";
int i; 
String reportString = "0972154901";
int addressCharArray=0; 
char input[10] = "";              // đầu vào hàm ghi eeprom
char output[10] = ""; 
String myphone;
void setup() {
  // Mở giao tiếp nối tiếp và đợi cổng mở:
  Serial.begin(9600);
  Serial.println("\n\nString charAt() and setCharAt():");

}

void loop() {
  // tạo Chuỗi để báo cáo đọc cảm biến:
  
  Serial.println(reportString);
   Serial.print("\n\nreport: ");
Serial.println(reportString.length());

  StringToChar(reportString,b);
  delay(100);
  delay(1000);  
  Serial.print("  ss : ");

    Serial.print(" a  : ");
  
      Serial.println( b);
      for (i = 0; i < 10; i++) { 
      input[i] = b[i];
      }
      delay(10);
       EEPROM.writeBlock<char>(addressCharArray, input, 10);
    delay(10);
    EEPROM.readBlock<char>(addressCharArray, output, 10);
    delay(10); // delay 5ms để trước khi lưu giá trị tiếp theo
    Serial.print("adress: ");
    Serial.println(addressCharArray);
    Serial.print("input: ");
    Serial.println(input);
    Serial.print("output: ");
    Serial.println(output);
    for (i = 0; i < 10; i++) { 
      myphone =myphone + output[i];
      }
//    myphone = output;
    Serial.println("myphone: ");
    Serial.print(myphone);
    Serial.println("");
//  
  while (true);
}

void StringToChar(String string, char a[10]){
//char a[18];
int i=0;

string.toCharArray(a, 11);
//   for (i = 0; i < string.length(); i++) { 
//      // chữ số có ý nghĩa nhất của bài đọc nằm ở vị trí 15 trong báo cáoString:
//    //  char mostSignificantDigit = 
// 
//        a[i] = string.charAt(i);
//       
//        Serial.println( a[i]); 
       delay(10); 
//    } 
    
// bạn cũng có thể đặt ký tự của Chuỗi. Thay đổi: thành a = ký tự
//  Serial.print("\n\nreport  s : ");
//  Serial.println( s); 
//  string.setCharAt(10, '=');
//  Serial.println(string);



}
