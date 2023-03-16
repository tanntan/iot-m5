#include <Arduino.h>
#include <M5Stack.h>

void setup() {
  Serial.begin(115200);
  M5.begin();

  M5.Lcd.fillScreen(0xeeeeee);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("Helloworld");
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}