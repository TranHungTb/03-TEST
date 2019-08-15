
#include <SoftwareSerial.h> 
#define GSMSerial Serial // phần cứng nối tiếp bây giờ sẽ được gọi là GSMSerial, để tránh nhầm lẫn 
SoftwareSerial SMSerial (2,3); // Sử dụng Phần mềm nối tiếp làm UART thứ hai - 
char incoming_char = 0; // Sẽ giữ ký tự đến từ Cổng nối tiếp phần mềm. 
void setup () 
{ 
  
// Khởi tạo các cổng nối tiếp để liên lạc. 
SMSerial.begin (9600); 
GSMSerial.begin (9600); 
SMSerial.println ("Bắt đầu truyền thông SM5100B ..."); 
} 
void loop () 
{ 
if(GSMSerial.available()>0) //Nếu một ký tự đến từ mô-đun di động ... 
{
SMSerial.write(GSMSerial.read()); //ghi nó ra màn hình nối tiếp để chúng ta có thể nhìn thấy nó 
}
if(SMSerial.available() >0) //Nếu bạn nhập một cái gì đó vào màn hình nối tiếp 
{
incoming_char=SMSerial.read(); // Nhận ký tự đến từ thiết bị đầu cuối 
GSMSerial.print(incoming_char); // Gửi ký tự đến mô-đun di động. 
}
}
