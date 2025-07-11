// ***********************************************************************
//     -------------------------------------------------------------------
//                        แก้ขาที่ esp32s3-default-pins.hpp
//                        แก้ฟอนต์ที่ ESP32-VirtualMatrixPanel-I2S-DMA.h
//     -------------------------------------------------------------------
// ***********************************************************************
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include "Wire.h"

#include <Fonts/FreeSansBold12pt7b.h>

#define PIN_RGB 48
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_RGB, NEO_RGB + NEO_KHZ800);
#define DELAYVAL 500

#define PANEL_RES_X 64 // จำนวนพิกเซลในแนวนอนของแต่ละโมดูลแผง
#define PANEL_RES_Y 64 // จำนวนพิกเซลในแนวตั้งของแต่ละโมดูลแผง

#define NUM_ROWS 1                     // จำนวนแถวของแผงที่เชื่อมต่อกัน
#define NUM_COLS 1                     // จำนวนแผงแต่ละแถว
#define PANEL_CHAIN NUM_ROWS *NUM_COLS // จำนวนรวมของแผงที่เชื่อมต่อกัน
#define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_NONE

MatrixPanel_I2S_DMA *dma_display = nullptr;
VirtualMatrixPanel *matrix = nullptr; // เปลี่ยน virtualDisp เป็น matrix

uint16_t myBLACK = matrix->color565(0, 0, 0);
uint16_t myWHITE = matrix->color565(255, 255, 255);
uint16_t myRED = matrix->color565(255, 0, 0);
uint16_t myGREEN = matrix->color565(0, 255, 0);
uint16_t myBLUE = matrix->color565(0, 0, 255);
uint16_t myYELLOW = matrix->color565(255, 255, 0);
uint16_t myPINK = matrix->color565(255, 20, 147);
uint16_t mySKYBLUE = matrix->color565(0, 255, 255);
uint16_t myPurple = matrix->color565(127, 0, 255);
uint16_t myMAGENTA = matrix->color565(210, 2, 210);

void setup()
{
  delay(1000);
   Serial.begin(115200);
  while (!Serial) {
    delay(10); // รอ USB CDC พร้อม
  }
  delay(100); // เพิ่มความเสถียร
  Serial.println("🚀 ESP32-S3 Started!");


  HUB75_I2S_CFG mxconfig(
      PANEL_RES_X, // ความกว้างของโมดูล
      PANEL_RES_Y, // ความสูงของโมดูล
      PANEL_CHAIN  // ความยาวของเชน
  );

  dma_display = new MatrixPanel_I2S_DMA(mxconfig);

  dma_display->setBrightness8(128); // ระดับความสว่างตั้งแต่ 0-255, 0 - 0%, 255 - 100%

  if (not dma_display->begin())
    Serial.println("****** !KABOOM! I2S memory allocation failed ***********");

  // matrix = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, CHAIN_NONE);
  matrix = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X / NUM_COLS, PANEL_RES_Y, VIRTUAL_MATRIX_CHAIN_TYPE);
  
  matrix->fillScreen(myRED);
  Serial.println("RED");
  pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // เขียว
  pixels.show();
  delay(1000);
  
  matrix->fillScreen(myGREEN);
  Serial.println("GREEN");
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // แดง
  pixels.show();
  delay(1000);

  matrix->fillScreen(myBLUE);
  Serial.println("BLUE");
  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // น้ำเงิน
  pixels.show();
  delay(1000);

  matrix->fillScreen(myYELLOW);
  Serial.println("YELLO");
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // น้ำเงิน
  pixels.show();
  delay(1000);

    matrix->fillScreen(myBLACK);
}

void loop()
{

  //64x64
  matrix->fillScreen(myRED);
  matrix->color565(0, 0, 0);
  matrix->setFont(&FreeSansBold12pt7b);
  matrix->setTextSize(1);
  matrix->setCursor(6, 43);
  matrix->print("RED");
  delay(1000);

  matrix->fillScreen(myGREEN);
  matrix->color565(0, 0, 0);
  matrix->setFont(&FreeSansBold12pt7b);
  matrix->setTextSize(1);
  matrix->setCursor(6, 43);
  matrix->print("GREEN");
  delay(1000);

  matrix->fillScreen(myBLUE);
  matrix->color565(0, 0, 0);
  matrix->setFont(&FreeSansBold12pt7b);
  matrix->setTextSize(1);
  matrix->setCursor(6, 43);
  matrix->print("BLUE");
  delay(1000);

  matrix->fillScreen(myYELLOW);
  matrix->color565(0, 0, 0);
  matrix->setFont(&FreeSansBold12pt7b);
  matrix->setTextSize(1);
  matrix->setCursor(6, 43);
  matrix->print("YELLOW");
  delay(1000);

}