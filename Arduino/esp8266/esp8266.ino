#include <SocketIOClient.h>
#include <ESP8266WiFi.h>
 
SocketIOClient client;
const char* ssid = "GFD Office Network";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
const char* password = "gfd@1352468";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.

//const char* ssid = "Redmi"; 
//const char* password = "1234567899";  

char host[] = "138.197.46.187";  //Địa chỉ IP dịch vụ, hãy thay đổi nó theo địa chỉ IP Socket server của bạn.
int port = 3484;                  //Cổng dịch vụ socket server do chúng ta tạo!
 
//từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
// mà chúng ta cần quan tâm đó là
// RID: Tên hàm (tên sự kiện
// Rfull: Danh sách biến (được đóng gói lại là chuối JSON)
extern String RID;
extern String Rfull;



void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Ket noi mang wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
// kets noi wifi
  while(WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print('.');
  }

  Serial.println();
  Serial.println("da ket noi wifi");
  Serial.println(F("dia chi ip duoc su dung:"));
  Serial.println(WiFi.localIP());

  if(!client.connect(host,port)) {
    Serial.println(F("Ket no den socket server that bai!"));
    return;
  }
  else
  {
    Serial.println("Ket no den socket server ok!");
  }
// gui suwj kieejn connection den socket server
  if(client.connected()) {
    client.send("connection", "message", "Modul wifi đã kết nối.");
  }

}

void loop()
{
    delay(10000);
    client.send("atime", "message", " Time please?");
    
  if (client.monitor()) {
 
        //in ra serial cho Arduino
        mySerial.print(RID);
        mySerial.print('\r');
        mySerial.print(Rfull);
        mySerial.print('\r');
 
        //in ra serial monitor
        Serial.print(RID);
        Serial.print(' ');
        Serial.println(Rfull);
        
        //Kiểm tra xem còn dư bao nhiêu RAM, để debug
        uint32_t free = system_get_free_heap_size();
        Serial.println(free);
    }
    //Serial.println(client.connected());
 
    //Kết nối lại!
    if (!client.connected()) {
      client.reconnect(host, port);
    }

// Mất kết nối, thì kết nối lại
  if(!client.connected()) {
    client.reconnect(host, port);
    client.send("connection", "message", "Modul wifi đã kết nối.");
  }
}
