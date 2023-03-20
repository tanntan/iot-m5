#include "UI.h"

using namespace LTLabs::UI;

Label::Label(const char* label) {
  LabelProps props;
  Label(label, props);
}

Label::Label(const char* strLabel, LabelProps pProps) {
  label = strLabel;
  props = pProps; 
}

void Label::draw() {
  int16_t textHeight = M5.Lcd.fontHeight();
  int width = props.width == 0
    ? M5.Lcd.textWidth(label) + (props.padding * 2)
    : props.width;
  M5.Lcd.fillRoundRect(props.x, props.y, width, (props.padding * 2) + textHeight, 5, BLUE);

  M5.Lcd.setTextDatum(props.textAlign);
  M5.Lcd.setTextColor(WHITE, BLUE);
  int16_t textX = props.textAlign == TC_DATUM
    ? props.x + (width / 2) 
    : props.x + props.padding;

  M5.Lcd.drawString(label, textX, props.y + props.padding);
}

void Label::hide() {
  int16_t textHeight = M5.Lcd.fontHeight();
  int width = props.width == 0
    ? M5.Lcd.textWidth(label) + (props.padding * 2)
    : props.width;
  M5.Lcd.fillRoundRect(props.x, props.y, width, (props.padding * 2) + textHeight, 5, BLACK);
}


void Label::setLabel(const char* pLabel) {
  label = pLabel;
}

void Label::setX(int x) {
  props.x = x;
}


