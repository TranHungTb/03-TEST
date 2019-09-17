/*
 * 
  Wifi service sẽ có 2 hàm 3 hàm để thực hiện việc: kết nối wifi, lưu trữ wifi, phát wifi. Cụ thể như sau:

Kết nối wifi: có 2 hàm kết nối wifi. Một là lấy dữ liệu từ bộ nhớ EEPROM rồi kết nối, 
một hàm sẽ cho phép truyền ssid và pass từ bên ngoài vào để kết nối. 
Khi truyền từ bên ngoài vào nếu wifi kết nối thành công thì ssid và pass sẽ được lưu lại để sử dụng cho lần sau. 

 */

#ifndef WIFI_SERVICE_H_
#define WIFI_SERVICE_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "EEPRomService.h"
#include "AppDebug.h"
#include "HttpServerH.h"

#define WIFI_AP_SSID "BE-CA"
#define WIFI_AP_PASSWORD "12345678"

#define CONNECT_OK (1)
#define CONNECT_TIMEOUT (-1)
#define CONNECT_SUSPENDED (-2)

#define EEPROM_WIFI_SSID_START 0
#define EEPROM_WIFI_SSID_END 19

#define EEPROM_WIFI_PASS_START 20
#define EEPROM_WIFI_PASS_END 39

class WifiServiceClass
{
public:
    WifiServiceClass();
    ~WifiServiceClass();
    void setupAP();
    int connect(const String &ssid, const String &pass, boolean isNew = false);
    int connect();
    void storeWifi(const String &ssid, const String &pass);
};

extern WifiServiceClass WifiService;

#endif /* WIFI_SERVICE_H_ */
