int sensorValue = 0;
float out_average = 0;
const int pin = 34;
float value;
long sum = 0;
int i = 0;
/*******************************BG**********************************/
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
/*******************************BT**********************************/
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS 1000
PulseOximeter pox;
uint32_t tsLastReport = 0;
/*******************************HR**********************************/
#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT
#include <BlynkSimpleEsp32_BT.h>
#define PIN_1 V5
#define PIN_1 V4
#define PIN_1 V3
char auth[] = "MY4T3RAdKOQWDf92tZ15jRsN2pLCrjwI";
/*******************************BL**********************************/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 27
#define OLED_CS 5
#define OLED_RESET 0
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
B00000001, B11000000,
B00000001, B11000000,
B00000011, B11100000,
B11110011, B11100000,
B11111110, B11111000,
B01111110, B11111111,
B00110011, B10011111,
B00011111, B11111100,
B00001101, B01110000,
B00011011, B10100000,
B00111111, B11100000,
B00111111, B11110000,
B01111100, B11110000,
B01110000, B01110000,
B00000000, B00110000
};
/*******************************OL**********************************/
void setup()
{
Serial.begin(115200);
Serial.println("Waiting for connections...");
Blynk.setDeviceName("Blynk");
Blynk.begin(auth);
/*******************************BL**********************************/
Serial.println("Adafruit MLX90614 test");
mlx.begin();
/*******************************BT**********************************/
Serial.print("Initializing pulse oximeter..");
if (!pox.begin())
{
Serial.println("FAILED");
//for (;;);
}
else
{
Serial.println("SUCCESS");
}
/*******************************HR**********************************/
if (!display.begin(SSD1306_SWITCHCAPVCC)) {
Serial.println(F("SSD1306 allocation failed"));
for (;;);
}
display.display();
delay(2000);
display.clearDisplay();
display.drawPixel(10, 10, SSD1306_WHITE);
display.display();
delay(2000);
/*******************************OL**********************************/
}
void loop()
{
for (i = 0; i < 100; i++)
{
sensorValue = analogRead(pin);
sum = sum + sensorValue;
delay(1);
}
out_average = sum / 100;
Serial.print("ADC Value:");
Serial.println(sensorValue);
Serial.print("Sum:");
Serial.println(sum);
Serial.print("Average:");
Serial.println(out_average);
delay(5000);
/*******************************BG**********************************/
Serial.print("Ambient = ");
Serial.print(mlx.readAmbientTempC());
Serial.print("*C\tObject = ");
Serial.print(mlx.readObjectTempC());
Serial.println("*C");
Serial.print("Ambient = ");
Serial.print(mlx.readAmbientTempF());
Serial.print("*F\tObject = ");
Serial.print(mlx.readObjectTempF());
Serial.println("*F");
Serial.println();
delay(500);
sum = 0;
/*******************************BT**********************************/
pox.update();
Serial.print("Heart rate:");
Serial.print(pox.getHeartRate());
Serial.print("bpm / SpO2:");
Serial.print(pox.getSpO2());
Serial.println("%");
//tsLastReport = millis();
/*******************************HR**********************************/
Blynk.run();
BLYNK_READ(PIN_1)
{
int sensorData1 = mlx.readObjectTempC();
Blynk.virtualWrite(PIN_1, sensorData1);
}
BLYNK_READ(PIN_2)
{
int sensorData2 = out_average;
Blynk.virtualWrite(PIN_2, sensorData2);
}
BLYNK_READ(PIN_3)
{
int sensorData3 = pox.getHeartRate();
Blynk.virtualWrite(PIN_3, sensorData3);
}
/*******************************BT**********************************/
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.print(a);
display.println("*C");
display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.print(b);
display.println("mg/dl"); display.setTextSize(2);
display.setTextColor(SSD1306_WHITE);
display.print(c);
display.println("bpm");
display.display();
delay(2000);
/*******************************OL**********************************/
}
