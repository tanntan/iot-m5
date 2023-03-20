#include <Arduino.h>
#include <lvgl.h>

#ifndef LTLABS_H
#define LTLABS_H

#define RGB_PIN       32
#define RGB_LEN       29
#define BTN_RED       36
#define BTN_G         26
#define led_btn_1     13
#define led_btn_2     14

/*Change to your screen resolution*/
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );


class LTLABS {
    private:
        int delay;
    public: 
        void blink(int pin, int del);
        void ui();
        void hardwareButtonEvent();

        unsigned long currentMillis;
        unsigned long wifiCurrentMillis;

        int buttonStatePrevious = LOW;  
        int btnRedStatePrevious = LOW; 

        unsigned long minButtonLongPressDuration = 3000;    // Time we wait before we see the press as a long press
        unsigned long buttonLongPressMillis;                // Time in ms when we the button was pressed
        bool buttonStateLongPress = false;   
        bool btnRedStateLongPress = false;               // True if it is a long press

        const int intervalButton = 50;                      // Time between two readings of the button state
        unsigned long previousButtonMillis;                 // Timestamp of the latest reading
        unsigned long buttonPressDuration;

        bool greenBtnState = false;
        bool redBtnState = false;

        int count = 0;
        int interval = 10;

        struct ltmconfig
        {
            int station;
            const char *machineType;
            const char *machineCode;
        };
        struct GlobalConfig
        {
            int timeZone;
            const char *deviceName;
            const char *lineID;
            int lineSetupID;
            int xfactoryId;
            const char *companyId;
        };
        struct LTIE
        {
            int subTotal;
            int count;
            int totalOutput;
            int quantity;
            int dailyOpt;
            int targetOpt;
        };

        void LtieOutputCounter();
        
};

#endif

