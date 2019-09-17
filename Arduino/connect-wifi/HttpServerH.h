/*
 * Service này sẽ tạo Web Server và cung cấp API phục vụ cho việc kết nối. 
 * Tất nhiên là dữ liệu trao đổi sẽ là chuỗi json để dễ xử lý. 
 * ESP8266 có thư viện ArduinoJson để thực hiện parse các chuỗi json. 
 * Chúng ta sẽ sử dụng thư viện này để parse dữ liệu nhận được từ máy tính.

Sẽ có 3 hàm thực hiện API chính:

handleStatus dùng để kiểm tra trạng thái của thiết bị
handleWifis dùng để quét các wifi gần kề để gửi trả lại phía máy tính
handleConnectTo dùng để nhận mật khẩu từ máy tính gửi đến và gọi hàm connect wifi.
 */

#ifndef HttpServerH_H_
#define HttpServerH_H_

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "AppConfig.h"
#include "EEPRomService.h"
#include "WifiService.h"
#include "AppDebug.h"

extern ESP8266WebServer* server;

extern void startConfigServer();
extern void handleOk();
extern void handleRoot();
extern void handleConnectTo();
extern void handleStatus();
extern void handleWifis();

#endif /* HttpServerH_H_ */
