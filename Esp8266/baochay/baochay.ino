
/*
  Chương trình nhỏ này cho thấy việc thực hiện một máy chủ rất nhỏ
  HTTP, để tương tác với mô-đun ESP thông qua WiFi.

  Ta sẽ kết nối module với wifi hiện có rồi từ dó ta sẽ truy cập vào modul qua wifi kết nối. bàng địa chỉ id của nó trong mạng
 
 * Để có thể chuyển đổi đầu ra D1 của nodeMCU, cần phải có
 * để gọi địa chỉ IP của mô-đun theo sau là / gpio / 1 để kích hoạt hoặc
 * / gpio / 0 để tắt
 *
 * Ví dụ: http: // <IP> / gpio / 0
 *
 * Thông tin về trạng thái của mô-đun được gửi trên
 * dòng nối tiếp (115200 bauds)
 *
 * Đèn LED nhấp nháy chậm biểu thị đang kết nối
   vào mạng Wifi của bạn
 * Nhấp nháy nhanh cho biết kết nối được thiết lập (
 * dừng nhấp nháy liên tục)
 *
 * Trang web trả về cho người dùng rất đơn giản,nó sử dụng CSS 

 */
#include <ESP8266WiFi.h>
#include <Servo.h>
       
 

const char* ssid = "GFD Office Network";
const char* password = "gfd@1352468";

//const String ssid = "Redmi";
//const String password = "1234567899";


Servo myservo;   
WiFiServer server(80);


int servoPin = D1; 

void setup() {
//  WiFiManager wifiManager;
//  wifiManager.autoConnect("AutoConnectAP","12345678");
  
  
// Cài đặt chức năng điều khiển servo cho chân servoPin
  myservo.attach(servoPin);
  myservo.write(0);
  
  int Led0 = LOW;
// set tốc độ cổng nt serial
  Serial.begin(115200);
  Serial.println();
  delay(10);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);
  
  Serial.println();
  Serial.println();
  Serial.println("**************************************");
  Serial.println("* Kiểm tra wifi");
  Serial.println("* Kiểm soát led");
  Serial.println("* URL ( http://<IP>/D0/[0|1]");
  Serial.println("**----------------------------------**");
  Serial.println("**************************************");
  Serial.println();

// Khởi tạo kết nối với mạng Wifi
  Serial.print("[i] Kết nối tới mạng wifi: ");
  Serial.println(ssid);

// kết nối wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

// Chờ kết nối hoạt đông
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
// wifi connect led nháy nhanh
    if(Led0 == LOW) { Led0 = HIGH; } else { Led0 = LOW; }
    digitalWrite(D0, Led0);
  }

  Serial.println("");
  Serial.println("[+] WiFi connect");

// 
  server.begin();
  Serial.println("[+] Server hoạt động");
  
// led cảnh báo
  for(int i=0; i<10; i++) {
  digitalWrite(D0, LOW);
  delay(125);
  digitalWrite(D0, HIGH);
  delay(125);
  }
  
  Serial.print("Địa chỉ ip được sử dụng:");
  Serial.println(WiFi.localIP());
}

 void loop() {

// kiểm tra xem máy khách có được kết nối module
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
// Đợi tín hiệu phản hồi
  Serial.println("[i] Đợi tín hiệu");
  while(!client.available()){
    delay(1);
  }

// Đọc dòng đầu tiên chúng ta nhận từ wep với readStringUntil('\r') lấy tới ký tự \r
  String req = client.readStringUntil('\r');
  Serial.print("req:");
  Serial.println(req);
// Xóa phần còn lại khi nhận được( nhiều tốn bộ nhớ ko cần)
  client.flush();
 
// Phân tích yêu cầu nhận được
  int val;
  if (req.indexOf("/D1/1") != -1) {
    val = 1;
    // vô hiệu hóa D0( chân led D0 có sẵn nối dương nên ta kích 1 thì led tắt)
    myservo.write(val*2*18-18);
  }
  
  else if (req.indexOf("/D1/2") != -1) {
    val = 2;
    // Bật D0
    myservo.write(val*2*18-18);
  }
  else if (req.indexOf("/D1/3") != -1) {
    val = 3;
    // Bật D0
    myservo.write(val*2*18-18);
  }
  else if (req.indexOf("/D1/4") != -1) {
    val = 4;
    // Bật D0
    myservo.write(val*2*18-18);
  }
  else if (req.indexOf("/D1/5") != -1) {
    val = 5;
    // Bật D0
    myservo.write(val*2*18-18);
  }
  else {
    Serial.println("[-] Yêu cầu không hợp lệ");
  }
  client.flush();

  // Trả lời t  
String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  // Chủ đề có sẵn
  s+= "<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"http://infoaleze.chez.com/IoT/IoT.css\" media=\"all\"/><meta charset='UTF-8'></head><body>";
  // văn bản :"Cấp 3":"Cấp 4":"Cấp 5"
  s+="<h1>Cấp dự báo cháy rừng: ";
  s += (val==1)?"Cấp 1":(val==2)?"Cấp 2":(val==3)?"Cấp 3":(val==4)?"Cấp 4":"Cấp 5";
  
  s += "</h1></html>\n";
  // thêm nút chuyển đổi
  s += "<a href=\"../D1/1\" class=\"bouton\"> Cấp 1 </a><a href=\"../D1/2\" class=\"bouton\"> Cấp 2 </a><a href=\"../D1/3\" class=\"bouton\"> Cấp 3 </a><a href=\"../D1/4\" class=\"bouton\"> Cấp 4 </a><a href=\"../D1/5\" class=\"bouton\"> Cấp 5 </a></body></html>";

  // Gửi lại phản hồi
  client.print(s);
  delay(1);
  Serial.println(s);
  Serial.println("[i] Ngắt kết nối");

  // khi ta ròi khỏi hàm thì kết nối sẽ tự hủy  
  
 }
