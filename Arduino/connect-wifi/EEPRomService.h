/*
 * EEPROM - Thư viện giao tiếp với bộ nhớ EEPROM của Arduino
 * Trên một số loại vi điều khiển đều có một bộ nhớ trong (giống như một ổ cứng nhỏ xíu) gọi là EEPROM, 
 * nó sẽ được lưu giữ với thời gian và không bị mất đi nếu vi điều khiển được reset, 
 * hay mất điện (nhưng khi upload code mới thì sẽ bị mất, 
 * tuy nhiên chúng ta vẫn có thể chỉnh để EEPROM không bị mất khi upload code mới, 
 * sẽ có bài viết về vấn đề này cho các bạn lập trình Arduino "cao tay"). Trên mạch Arduino, 
 * các vi điều khiển đều có một bộ nhớ EEPROM của riêng mình.
Để thao tác với EEPROM ta sẽ sử dụng thư viện EEPROM của ESP8266. 
Tuy nhiên thư viện này chỉ thao tác với từng ô nhớ. 
Nhưng những giá trị cần lưu vào là các String do vậy cần phải viết các hàm thực hiện được điều đó. 
Service này sẽ có 4 hàm cơ bản sau:

write Hàm ghi
read Hàm đọc
clear Hàm xóa dùng để xóa các ô nhớ về giá trị 0
commit Hàm commit để lưu những thay đổi vào EEPROM thật
 */

#ifndef EEPROM_SERVICE_H_
#define EEPROM_SERVICE_H_

#include <Arduino.h>
#include <EEPROM.h>
#include "AppDebug.h"

#define EEPROM_SIZE 250

class EEPRomHClass
{
public:
    EEPRomHClass();
    ~EEPRomHClass();
    void write(const String &data, int begin, int endMax);
    String read(int begin, int end);
    void clear(int start, int end);
    void commit();
};

extern EEPRomHClass EEPROMH;

#endif /* EEPROM_SERVICE_H_ */
