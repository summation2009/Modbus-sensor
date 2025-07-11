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

// #include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

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

#define SW_MODE 35
#define SW_SET 39
#define SW_ADJ 36

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
  while (!Serial)
  {
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

  matrix->fillScreen(myBLACK);
  Serial.println("BLACK");
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // น้ำเงิน
  pixels.show();
  delay(1000);

  // 64x64
  matrix->fillScreen(myRED);
  matrix->color565(0, 0, 0);
  matrix->setFont(&FreeSansBold9pt7b);
  matrix->setTextColor(myWHITE);
  matrix->setTextSize(1);
  matrix->setCursor(1, 40);
  matrix->print("HELLO");

}

void loop()
{

  // // 64x64
  // matrix->fillScreen(myRED);
  // matrix->color565(0, 0, 0);
  // matrix->setFont(&FreeSansBold12pt7b);
  // matrix->setTextColor(myWHITE);
  // matrix->setTextSize(1);
  // matrix->setCursor(6, 43);
  // matrix->print("RED");
  // delay(1000);

  int M = 0;
  int S = 0;
  int A = 0;

  if (digitalRead(SW_MODE) == LOW)
  {
    while (digitalRead(SW_MODE) == LOW)
    {
      Serial.print("M");
      M++;
      pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // น้ำเงิน
      pixels.show();
      delay(250);
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // ปิดไฟ
      pixels.show();
      delay(250);
      if (M == 7)
      { // LED Blink 5 times
        M = 0;

        matrix->fillScreen(myRED);
        matrix->color565(0, 0, 0);
        matrix->setFont(&FreeSansBold9pt7b);
        matrix->setTextColor(myWHITE);
        matrix->setTextSize(1);
        matrix->setCursor(5, 38);
        matrix->print("MODE");
        Serial.println("MODE");

        while (!digitalRead(SW_MODE))
        {
          pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // น้ำเงิน
          pixels.show();
        }
        pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // ปิดไฟ
        pixels.show();
      }
    }
  }


  if (digitalRead(SW_SET) == LOW)
  {
    while (digitalRead(SW_SET) == LOW)
    {
      Serial.print("S");
      S++;
      pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // น้ำเงิน
      pixels.show();
      delay(250);
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // ปิดไฟ
      pixels.show();
      delay(250);
      if (S == 7)
      { // LED Blink 5 times
        S = 0;

        matrix->fillScreen(myRED);
        matrix->color565(0, 0, 0);
        matrix->setFont(&FreeSansBold12pt7b);
        matrix->setTextColor(myWHITE);
        matrix->setTextSize(1);
        matrix->setCursor(9, 43);
        matrix->print("SET");
        Serial.println("SET");

        while (!digitalRead(SW_SET))
        {
          pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // น้ำเงิน
          pixels.show();
        }
        pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // ปิดไฟ
        pixels.show();
      }
    }
  }

    if (digitalRead(SW_ADJ) == LOW)
  {
    while (digitalRead(SW_ADJ) == LOW)
    {
      Serial.print("A");
      A++;
      pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // น้ำเงิน
      pixels.show();
      delay(250);
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // ปิดไฟ
      pixels.show();
      delay(250);
      if (A == 7)
      { // LED Blink 5 times
        A = 0;

        matrix->fillScreen(myRED);
        matrix->color565(0, 0, 0);
        matrix->setFont(&FreeSansBold12pt7b);
        matrix->setTextColor(myWHITE);
        matrix->setTextSize(1);
        matrix->setCursor(9, 43);
        matrix->print("ADJ");
        Serial.println("ADJ");

        while (!digitalRead(SW_ADJ))
        {
          pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // น้ำเงิน
          pixels.show();
        }
        pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // ปิดไฟ
        pixels.show();
      }
    }
  }
}