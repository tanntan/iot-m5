#include <M5Stack.h>
#include "UI.h"

using namespace LTLabs::UI;

Title::Title(const char* strTitle) {
  this->title = strTitle;
}

void Title::draw() {
  M5.Lcd.setTextSize(2);
  int16_t fontHeight = M5.Lcd.fontHeight();
  int16_t screenWidth = M5.Lcd.width();
  M5.Lcd.fillRect(0, 0, screenWidth, fontHeight + (PADDING * 2), BLUE);
  M5.Lcd.setTextColor(WHITE, BLUE);
  M5.Lcd.setTextDatum(TL_DATUM);
  M5.Lcd.drawString(title, 12, 6);
}

void Title::setTitle(const char* strTitle) {
  title = strTitle;
  draw();
}

const char* Title::getTitle() {
  return title;
}
