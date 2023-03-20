#include <Arduino.h>
#include <lvgl.h>
#include "ltlabs.h"
#include <M5Tough.h>
#include "../ui/ui.h"
LTLABS::LTIE ltieOpt;
void LTLABS::blink(int pin, int del)
{
    digitalWrite(pin, LOW);
    vTaskDelay(del);
    digitalWrite(pin, HIGH);
    vTaskDelay(del);
}

M5Display tft;

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX = 0, touchY = 0;

    bool touched = tft.getTouch(&touchX, &touchY, 600);

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;
    }
}
void LTLABS::ui()
{
    tft.setBrightness(50);
    // init lvgl
    lv_init();
#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.setRotation( 1 ); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );
    ui_init();

}

void LTLABS::hardwareButtonEvent()
{
    // If the difference in time between the previous reading is larger than intervalButton
  if(currentMillis - previousButtonMillis > intervalButton) {
    
    int buttonState = digitalRead(BTN_G);
    int buttonRedState = digitalRead(BTN_RED);

    if(buttonRedState == HIGH && btnRedStatePrevious == LOW && !btnRedStateLongPress )
    {
        buttonLongPressMillis = currentMillis;
        btnRedStatePrevious = HIGH;
    }

    if (buttonState == HIGH && buttonStatePrevious == LOW && !buttonStateLongPress) {
      buttonLongPressMillis = currentMillis;
      buttonStatePrevious = HIGH;
    }

    // Calculate how long the button has been pressed
    buttonPressDuration = currentMillis - buttonLongPressMillis;

    if (buttonState == HIGH && !buttonStateLongPress && buttonPressDuration >= minButtonLongPressDuration) {
      buttonStateLongPress = true;
    }

    if (buttonRedState == HIGH && !btnRedStateLongPress && buttonPressDuration >= minButtonLongPressDuration) {
      btnRedStateLongPress = true;
    }

    if (buttonState == LOW && buttonStatePrevious == HIGH) {
      buttonStatePrevious = LOW;
      buttonStateLongPress = false;

      if (buttonPressDuration < minButtonLongPressDuration) {
        greenBtnState = true;
        count++;
        interval = 10;
      }
    }
    if (buttonRedState == LOW && btnRedStatePrevious == HIGH) {
      btnRedStatePrevious = LOW;
      btnRedStateLongPress = false;

      if (buttonPressDuration < minButtonLongPressDuration) {
        redBtnState = true;
        count--;
        if(count < 0) count = 0;
        interval = 10;
      }
    }
    // store the current timestamp in previousButtonMillis
    previousButtonMillis = currentMillis;

  }
}

void LTLABS::LtieOutputCounter()
{
    ltieOpt.subTotal = ltieOpt.totalOutput + count;

    Serial.print(ltieOpt.subTotal);
}

