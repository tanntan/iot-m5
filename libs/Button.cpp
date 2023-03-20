#include "UI.h"

using namespace LTLabs::UI;

// std::function<void(void)> onPress;
M5Button::M5Button(const char* pLabel, int x) {
  int height = M5.Lcd.height();
  int16_t textHeight = M5.Lcd.fontHeight();
  int y = height - (textHeight + (PADDING * 2));
  LabelProps props;
  props.y = y;
  props.x = x;
  props.width = 80;
  props.textAlign = TC_DATUM;
  label = new Label(pLabel, props);
}

void M5Button::setX(int x) {
  label->setX(x);
}

void M5Button::setLabel(const char* pLabel) {
  label->setLabel(pLabel);
  label->draw();
}

void M5Button::draw(const char* pLabel) {
  if (pLabel == "") {
    label->draw();
  }else{
    label->setLabel(pLabel);
  }
}

void M5Button::hide() {
  label->hide();
}

