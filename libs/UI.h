#ifndef LTLABS_UI
#define LTLABS_UI

#include <M5Stack.h>
#include <vector>
#include <string>

using namespace std;


namespace LTLabs::UI {

  const int PADDING = 6;

  class Title {
    private:
      const char* title;

    public:
      Title(const char* strTitle);
      void draw();
      void setTitle(const char* strTitle);
      const char* getTitle();
  };

  struct LabelProps {
    int16_t x = M5.Lcd.getCursorX();
    int16_t y = M5.Lcd.getCursorY();
    int width = 0;
    int8_t padding = PADDING;
    int16_t radius = 3;
    int8_t textAlign = TL_DATUM;
  };

  class Label {
    private:
      const char* label;
      LabelProps props;

    public:
      Label(const char* label);
      Label(const char* strLabel, LabelProps pProps);
      void draw();
      void hide();
      void setLabel(const char* pLabel);
      void setX(int x);
  };

  class M5Button {
    private:
      Label* label;

    public:
      // std::function<void(void)> onPress;
      M5Button(const char* pLabel, int x = 10);
      void setX(int x);
      void setLabel(const char* pLabel);
      void draw(const char* pLabel = "");
      void hide();
  };

  class LeftButton: public M5Button {
    public:
      LeftButton(const char* label): M5Button(label) {
        int blockWidth = M5.Lcd.width() / 4;
        int x = blockWidth - 40 - 20;
        setX(x);
      }

      void onPress(std::function<void()> callback) {
        if (M5.BtnA.wasReleased()) {
          M5.Speaker.tone(700, 5);
          callback();
          M5.Speaker.update();
        }
      }
  };

  class CenterButton: public M5Button {
    public:
      CenterButton(const char* label): M5Button(label) {
        int center = M5.Lcd.width() / 2;
        int x = center - 40;
        setX(x);
      }

      void onPress(std::function<void()> callback) {
        if (M5.BtnB.wasReleased()) {
          M5.Speaker.tone(700, 5);
          callback();
          M5.Speaker.update();
        }
      }

  };

  class RightButton: public M5Button {
    public:
      RightButton(const char* label): M5Button(label) {
        int block = M5.Lcd.width() / 4;
        int x = (block * 3) - 20;
        setX(x);
      }

      void onPress(std::function<void()> callback) {
        if (M5.BtnC.wasReleased()) {
          M5.Speaker.tone(700, 5);
          callback();
          M5.Speaker.update();
        }
      }
  };

  struct ListItem {
    const char* label;
    String value;
  };

  class List {
    private:
      vector<ListItem> items;

      void drawItem(ListItem item) {
        int y = M5.Lcd.getCursorY() + 25;
        M5.Lcd.setCursor(20, y);
        M5.Lcd.print(item.label);
        M5.Lcd.setCursor(100, y);
        M5.Lcd.print(String(item.value));
      }

    public:
      List(vector<ListItem> pItems) {
        items = pItems;
      }

      void draw() {
        M5.Lcd.setCursor(0, 20);
        int8_t size = items.size(); 
        for(int8_t i = 0; i < size; i++) {
          ListItem item = items.at(i);
          drawItem(item);
        }
      }
  };
}

#endif
