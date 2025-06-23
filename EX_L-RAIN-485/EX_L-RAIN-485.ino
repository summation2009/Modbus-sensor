
/*
  example using ModbusMaster library
*/

#include "ModbusMaster.h"

// instantiate ModbusMaster object
ModbusMaster myModbus;                    // สร้าง Modbus อ๊อปเจค

#define SLAVE_ID 1                        // ประกาศตัวแปร SLAVE ID (ID ของตัวเซนเซอร์ที่ต้องการอ่าน)
#define SLAVE_BAUDRATE 9600               // ประกาศตัวแปร SLAVE BAUDRATE (อัตราความเร็วรับ-ส่งข้อมูล) *** ค่า Baud rate ต้องตรงกับตัวเซนเซอร์ที่เราจะอ่านค่า


void setup()
{
  // use Serial (port 0); initialize Modbus communication baud rate
  Serial.begin(115200);                            // Serial0 สำหรับดีบั๊ก เพื่อดูค่า

  Serial2.begin(SLAVE_BAUDRATE, SERIAL_8N1, 16, 17);     // เริ่มการเปิดพอร์ตสื่อสาร Serial2, ค่าความเร็วสื่อสารที่ 4800 (ตั้งค่าให้ตรงกับเซนเซอร์ที่จะอ่าน), Data bit 8: parity: NONE, Stopbit :1, ขา 16 เป็น RX, ขา 17 เป็น TX
  myModbus.begin(SLAVE_ID, Serial2);                     // Slave ID = 1 (ID ของตัวเซนเซอร์ที่ต้องการอ่านค่า), โดยใช้พอร์ต Serial2 เป็นพอร์ตสื่อสาร
}


void loop()
{
  uint8_t result;
  int rain_24h;
  int light;

  result = myModbus.readHoldingRegisters(0, 4);   // เริ่มอ่านค่าที่ตำแหน่งรีจิสเตอร์ 0, เป็นจำนวน 2 รีจิสเตอร์

  if (result == myModbus.ku8MBSuccess) {          // หากสำเร็จ เซนเซอร์ตอบกลับ และไม่มีผิดพลาด
    rain_24h = myModbus.getResponseBuffer(0);     // เอาค่า Buffer 0 ที่อ่านจาก Modbus มาไว้ในตัวแปร rain_24h
    light = myModbus.getResponseBuffer(3);     // เอาค่า Buffer 0 ที่อ่านจาก Modbus มาไว้ในตัวแปร light

    Serial.print (rain_24h);                 // นำค่าที่อ่านได้ พิมพ์ออกทาง Serial0
    Serial.print (" MM");
    Serial.print ("\t");
    Serial.print (light);              // นำค่าที่อ่านได้ พิมพ์ออกทาง Serial0
    Serial.println (" LUX");
  } else {
    //Serial.println ("error");
  }
  
  delay(1000);
  
}