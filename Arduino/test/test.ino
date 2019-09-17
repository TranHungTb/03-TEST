
#include <ESP8266WiFi.h>
 
void setup() {
  Serial.begin(9600);
  /*
   * WiFi.softAP(ssid, password, channel, hidden)
   * ssid     : Chuỗi lí tự chưa SSID mạng (tối đa 63 kí tự)
   * password : Chuỗi ký tự tùy chọn với mật khẩu. Đối với mạng WPA2-PSK, nó phải có ít nhất 8 ký tự. 
   *            Nếu không có mật khẩu, thì đây sẽ là mạng WiFi mở.
   * channel  : Tham số tùy chọn để thiết lập kênh Wi-Fi, từ 1 đến 13. Kênh mặc định = 1
   * hidden   : Tham số tùy chọn, thiết lập là true để ẩn SSID
   */
  //WiFi.softAP("MTE Acess Point");
  WiFi.softAP("MTE Acess Point","********",6,false);
  Serial.print("Soft-AP IP address = ");            // Địa chỉ IP của acess point
  Serial.println(WiFi.softAPIP());
  Serial.print("MAC address: ");                    // Địa chỉ MAC của esp
  Serial.println(WiFi.softAPmacAddress());
}
 
void loop() {
  Serial.print("Số thiết bị kết nối: ");
  Serial.println(WiFi.softAPgetStationNum());
  delay(2000);
}
