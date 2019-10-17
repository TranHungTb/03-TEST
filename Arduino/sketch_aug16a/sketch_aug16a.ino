char a[18]="";
int i; String reportString = "0972154901";
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

  StringToChar(reportString);
  delay(100);
  delay(1000);  
  Serial.print("  ss : ");

    Serial.print(" a  : ");
  
      Serial.println( a); 
  
  while (true);
}
void StringToChar(String string){


   for (i = 0; i < string.length(); i++) { 
      // chữ số có ý nghĩa nhất của bài đọc nằm ở vị trí 15 trong báo cáoString:
//  char mostSignificantDigit = 
 
        a[i] = string.charAt(i);
       
        Serial.println( a[i]); 
       delay(10); 
    } 
    
  // bạn cũng có thể đặt ký tự của Chuỗi. Thay đổi: thành a = ký tự
//  Serial.print("\n\nreport  s : ");
//  Serial.println( s); 
//  string.setCharAt(10, '=');
//  Serial.println(string);



}
