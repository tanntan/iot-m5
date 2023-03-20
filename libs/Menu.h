#ifndef LTLABS_UI_MENU
#define LTLABS_UI_MENU

#include <M5Stack.h>
#include <vector>
#include "UI.h"

using namespace LTLabs::UI;
using namespace std;

namespace LTLabs::Menu {

  struct MenuItem {
    const char* value;
    const char* label;
  };


  typedef std::function<void(int8_t index, MenuItem selectedItem)> menuCallback;
  typedef std::function<void()> callback;

  const int8_t PADDING = 6;
  const int8_t SPACING = 20;
  const int SCREEN_WIDTH = M5.Lcd.width();
  const int SCREEN_HEIGHT = M5.Lcd.height();


  namespace {
    class MenuItemClass {
      private:
        MenuItem props;

      public:
        MenuItemClass(MenuItem pProps) {
          M5.Lcd.setTextSize(2);
          props = pProps;
        }

        void draw(uint8_t isSelected = 0) {
          int y = M5.Lcd.getCursorY() + PADDING;
          int16_t fontHeight = M5.Lcd.fontHeight();
          int height = fontHeight + (PADDING * 2);
          int width = M5.Lcd.width() - (SPACING * 2);

          M5.Lcd.fillRect(SPACING, y , width, height , BLACK); 
          if (isSelected) {
            M5.Lcd.fillRect(SPACING, y , width, height , BLUE); 
            M5.Lcd.setTextColor(WHITE, BLUE);
          }else{
            M5.Lcd.drawRect(SPACING, y , width, height , BLUE); 
            M5.Lcd.setTextColor(WHITE, BLACK);
          }
          M5.Lcd.setTextDatum(TL_DATUM);
          M5.Lcd.drawString(props.label, SPACING + (PADDING * 2), y + PADDING);
          M5.Lcd.setCursor(SPACING, y + height); 
        }
    };
  }

  class Menu {
    private:
      vector<MenuItem> items;
      int8_t activeIndex = 0;
      LeftButton* leftButton;
      CenterButton* centerButton;
      RightButton* rightButton;

      callback onLeftButtonPress = [&]() {
        if (activeIndex > 0) {
          activeIndex = activeIndex - 1;
          draw();
        }
      };

      callback onRightButtonPress = [&]() {
        int8_t maxIndex = items.size() - 1;
        if (activeIndex < maxIndex) {
          activeIndex = activeIndex + 1;
          draw();
        }
      };

      void drawButtons() {
        leftButton->draw();
        rightButton->draw();
        centerButton->draw();
      }


    public:
      Menu(vector<MenuItem> pItems, int8_t curIndex = 0) {
        items = pItems;
        activeIndex = (curIndex < 0 || curIndex >= items.size()) ? 0 : curIndex;
        centerButton = new CenterButton("Select");
        leftButton = new LeftButton("<");
        rightButton = new RightButton(">");
      }

      void draw() {
        drawButtons();
        M5.Lcd.setCursor(0, 30);
        int8_t maxIndex = items.size() - 1;
        int8_t start = (activeIndex - 2) < 0 ? 0 : activeIndex - 2;
        int8_t end = (start + 4) > maxIndex ? maxIndex : start + 4;
        start = (end - 4) < 0 ? 0 : (end - 4);
        for(int i = start; i <= end; i++) {
          MenuItemClass tmp(items.at(i));
          tmp.draw(i == activeIndex);
        }
      }

      void listen(menuCallback onSelect) {
        leftButton->onPress(onLeftButtonPress);
        rightButton->onPress(onRightButtonPress);
        callback onCenterButtonPress = [&]() {
          MenuItem selectedItem = items.at(activeIndex);
          onSelect(activeIndex, selectedItem);
        };
        centerButton->onPress(onCenterButtonPress);
      }
  };
}
#endif
