#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

static const unsigned char PROGMEM fox[]={
  B00000000, B00010000, B00000000, B00000000,
  B00000000, B00111000, B00000111, B00000000,
  B00000000, B01111100, B00001111, B10000000,
  B00000000, B11001100, B00011101, B11000000,
  B00000001, B10001100, B00011000, B11000000,
  B00000001, B10000110, B00110000, B11000000,
  B00000011, B00000111, B11100000, B11000000,
  B00000011, B11111111, B11110000, B11000000,
  B00000111, B11111111, B11111110, B11000000,
  B00000111, B11111111, B11111111, B11000000,
  B00000111, B11111111, B11111111, B11000000,
  B00001111, B11111111, B11111111, B11000000,
  B00001111, B11111111, B11111111, B11000000,
  B00001111, B10111111, B11011111, B11000000,
  B00011111, B11011111, B10111111, B11000000,
  B00011111, B11101111, B01111111, B11000000,
  B00011111, B11101110, B11111111, B11000000,
  B00011111, B11011110, B11111111, B11000000,
  B00011111, B00011110, B01111111, B11100000,
  B00011111, B11111111, B10011111, B11100000,
  B00010000, B00000011, B11111111, B11100000,
  B00011000, B00000000, B00000000, B01100000,
  B00001100, B00111111, B10000000, B11000000,
  B00000010, B00111111, B10000011, B00000000,
  B01111111, B00111111, B00011100, B00000000,
  B01111111, B10011110, B00011000, B00000000,
  B01111111, B10000000, B00011000, B00000000,
  B00111111, B10000000, B00111100, B00000000,
  B00111111, B10000000, B01111110, B00000000,
  B00011111, B10000000, B01111111, B00000000,
  B00011111, B10000000, B01111111, B00000000,
  B00001111, B10000000, B01111100, B00000000,
  B00000011, B10000000, B00000000, B00000000};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.clearDisplay();
  display.setCursor(12, 32);
  display.print("SUCC-O-METER V1.0");
  display.setCursor(32, 40);
  display.print("<3 Empress");
  display.display();
  delay(5000);

  // Clear the buffer.
  display.clearDisplay();
}


void loop() {
  float hygroValue = analogRead(A0);
  float lumenValue = analogRead(A1);
  float tempValue = analogRead(A2) * 5;
  int hygroPercentage = 0;
  int lumenPercentage = 0;
  int temperatureC = 0;
  float maxVal = 1023.0;
  uint8_t heart = 3;

  tempValue /= maxVal;
  temperatureC = round((tempValue - 0.5) * 100);
  
  hygroPercentage = round(100 - ((hygroValue / maxVal) * 100));
  lumenPercentage = round((lumenValue / maxVal) * 100);

  display.setCursor(94, 50);
  display.write(heart);
  display.drawBitmap(100, 32, fox, 32, 32, 1);
  display.drawLine(0, 21, 64, 21, 1);
  display.drawLine(0, 42, 64, 42, 1);
  display.drawLine(64, 0, 64, 63, 1);
  display.drawLine(0, 0, 64, 0, 1);
  display.drawLine(0, 0, 0, 64, 1);
  display.drawLine(0, 63, 64, 63, 1);
  display.drawLine(32, 0, 32, 63, 1);

  // print humidity
  display.setCursor(6,8);
  display.print("HUM: "); display.print(hygroPercentage); display.print("%");

  // print light intensity
  display.setCursor(6,28);
  display.print("LUM: "); display.print(lumenPercentage); display.print("%");

  // print temperature
  display.setCursor(6,50);
  display.print("TMP: "); display.print(temperatureC); display.print((char)247); display.print("C");
  
  display.display();
  display.clearDisplay();
}
