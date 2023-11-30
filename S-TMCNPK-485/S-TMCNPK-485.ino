#include <SoftwareSerial.h>
SoftwareSerial Serial2(3,4); // RX, TX 

#define PIN_RE_DE   7

#include "ModbusMaster.h"
ModbusMaster myModbus;                    

#define SLAVE_ID 1                        
#define SLAVE_BAUDRATE 9600              


void modbusPreTransmission()
{
  delay(500);
  digitalWrite(PIN_RE_DE, HIGH);
}

void modbusPostTransmission()
{
  digitalWrite(PIN_RE_DE, LOW);
  delay(500);
}

void setup()
{
  Serial.begin(9600);               

  Serial2.begin(SLAVE_BAUDRATE);    
  myModbus.begin(SLAVE_ID, Serial2);                   

  pinMode(PIN_RE_DE , OUTPUT);      
  digitalWrite(PIN_RE_DE , HIGH);    

  myModbus.preTransmission(modbusPreTransmission);
  myModbus.postTransmission(modbusPostTransmission);
}


void loop()
{
  uint8_t result;
  float Temperature, Humidity;
  uint16_t Conductivity, N, P, K;

  result = myModbus.readHoldingRegisters(0, 6);   // เริ่มอ่านค่าที่ตำแหน่งรีจิสเตอร์ 0, เป็นจำนวน 2 รีจิสเตอร์

  if (result == myModbus.ku8MBSuccess) {          // หากสำเร็จ เซนเซอร์ตอบกลับ และไม่มีผิดพลาด
    Humidity = myModbus.getResponseBuffer(0) / 10.0;     // เอาค่า Buffer 0 ที่อ่านจาก Modbus มาไว้ในตัวแปร Humidity และหารด้วย 10
    Temperature = myModbus.getResponseBuffer(1) / 10.0;  // เอาค่า Buffer 1 ที่อ่านจาก Modbus มาไว้ในตัวแปร Temperature และหารด้วย 10
    Conductivity = myModbus.getResponseBuffer(2);
    N = myModbus.getResponseBuffer(3);
    P = myModbus.getResponseBuffer(4);
    K = myModbus.getResponseBuffer(5);

    Serial.print ("Humidity = ");
    Serial.print (Humidity);                 // นำค่าที่อ่านได้ พิมพ์ออกทาง Serial0
    Serial.print (" %RH");
    Serial.print ("\t");
    Serial.print ("Temperature = ");
    Serial.print (Temperature);             
    Serial.println (" *C");
    Serial.print ("Conductivity = ");
    Serial.print (Conductivity);                 
    Serial.print (" EC");
    Serial.print ("\t");
    Serial.print ("Nitrogen = ");
    Serial.print (N);              
    Serial.println (" mg/kg");
    Serial.print ("Phosphorus = ");
    Serial.print (P);                
    Serial.print (" mg/kg");
    Serial.print ("\t");
    Serial.print ("Potassium = ");
    Serial.print (K);             
    Serial.println (" mg/kg");
    Serial.println("**********************************************");
  } else {
    Serial.println ("error");
  }
  
  delay(1000);
  
}
