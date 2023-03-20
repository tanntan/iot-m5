
#include <Arduino.h>
#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void blink_Animation(lv_obj_t * TargetObject, int delay);
void ui_list(const char * title, const char *item);
void machineList(const char *subType, const char *mc, const char *station);
lv_obj_t * ui_home;
lv_obj_t * ui_header;
lv_obj_t * ui_brandPanel;
lv_obj_t * ui_settingBtn;
lv_obj_t * ui_brandLabel;
lv_obj_t * ui_indicatorPanel;
lv_obj_t * ui_indicator;
lv_obj_t * ui_wifi;
lv_obj_t * ui_ltiepanel;
lv_obj_t * ui_Bar2;
lv_obj_t * ui_lineoutput;
lv_obj_t * ui_countpanel;
lv_obj_t * ui_totalOutput;
lv_obj_t * ui_device;
lv_obj_t * ui_quantity;
lv_obj_t * ui_countpanel1;
lv_obj_t * ui_dayOutput;
lv_obj_t * ui_label;
lv_obj_t * ui_valueDayOut;
lv_obj_t * ui_dayOutput1;
lv_obj_t * ui_label4;
lv_obj_t * ui_valueDayOut1;
lv_obj_t * ui_btnPanel;
void ui_event_redbtn(lv_event_t * e);
lv_obj_t * ui_redbtn;
lv_obj_t * ui_greenBtn;
lv_obj_t * ui_lineDetails;
lv_obj_t * ui_listPanel;
lv_obj_t * ui_listTitle;
lv_obj_t * ui_descripttion;
void ui_event_listOfMachine(lv_event_t * e);
lv_obj_t * ui_listOfMachine;
lv_obj_t * ui_machineList;
void ui_event_machineListItem(lv_event_t * e);
lv_obj_t * ui_machineListItem;
lv_obj_t * ui_listTitle1;
lv_obj_t * ui_descripttion1;
lv_obj_t * ui_selectListTitle;
lv_obj_t * ui_confirmScreen;
lv_obj_t * ui_confirmText;
lv_obj_t * ui_machineList1;
lv_obj_t * ui_listLineDetails;
lv_obj_t * ui_label1;
lv_obj_t * ui_lineIdText;
lv_obj_t * ui_listLineDetails1;
lv_obj_t * ui_label2;
lv_obj_t * ui_lineIdText1;
lv_obj_t * ui_listLineDetails2;
lv_obj_t * ui_label3;
lv_obj_t * ui_lineIdText2;
lv_obj_t * ui_btnConfirmPanel;
void ui_event_noConfirmBtn(lv_event_t * e);
lv_obj_t * ui_noConfirmBtn;
lv_obj_t * ui_noBtnTxt;
void ui_event_yesConfigmBtn(lv_event_t * e);
lv_obj_t * ui_yesConfigmBtn;
lv_obj_t * ui_noBtnTxt1;
lv_obj_t * ui_settingScreen;
lv_obj_t * btnSetting;
lv_obj_t * countLabel;
///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void blink_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 255, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_opacity);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_listOfMachine(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_scr_load(ui_home);
    }
}
void event_no_btn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED)
    {
        lv_scr_load(ui_home);
    }
}
void ui_event_machineListItem(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    
    if(event_code == LV_EVENT_CLICKED) {
        lv_obj_t * mcCode = lv_obj_get_child(target, 1);
        lv_obj_t * station = lv_obj_get_child(target, 2);

        const char * mcTxt = lv_label_get_text(mcCode);
        const char * staText = lv_label_get_text(station);
        
        lv_scr_load(ui_confirmScreen);
        lv_label_set_text(ui_lineIdText1, staText);
        lv_label_set_text(ui_lineIdText2, mcTxt);
    }
}
void ui_event_noConfirmBtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_LONG_PRESSED) {
        _ui_opacity_set(ui_indicator, 100);
    }
}


void settingBtnEvent(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
       lv_scr_load(ui_settingScreen);
    }
}

///////////////////// SCREENS ////////////////////
void ui_list(const char * title, const char *item)
{
    ui_listPanel = lv_obj_create(ui_lineDetails);
    lv_obj_set_width(ui_listPanel, 289);
    lv_obj_set_height(ui_listPanel, 64);
    lv_obj_set_align(ui_listPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_listPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_listPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_listPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_listPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_listPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_listPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_listPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_listPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_listTitle = lv_label_create(ui_listPanel);
    lv_obj_set_width(ui_listTitle, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_listTitle, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_listTitle, LV_ALIGN_CENTER);
    lv_label_set_text(ui_listTitle, title);
    lv_obj_set_style_text_color(ui_listTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_listTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_descripttion = lv_label_create(ui_listPanel);
    lv_obj_set_width(ui_descripttion, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_descripttion, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_descripttion, LV_ALIGN_CENTER);
    lv_label_set_text(ui_descripttion, item);
    lv_obj_set_style_text_color(ui_descripttion, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_descripttion, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_descripttion, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
}


void ui_home_screen_init(void)
{
    ui_home = lv_obj_create(NULL);
    lv_obj_set_flex_flow(ui_home, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_home, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_bg_color(ui_home, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_home, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_home, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_home, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_home, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_home, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_home, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_header = lv_obj_create(ui_home);
    lv_obj_set_width(ui_header, lv_pct(100));
    lv_obj_set_height(ui_header, lv_pct(18));
    lv_obj_set_align(ui_header, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_header, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_header, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_header, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_header, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_header, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_header, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_header, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_header, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_brandPanel = lv_obj_create(ui_header);
    lv_obj_set_width(ui_brandPanel, lv_pct(50));
    lv_obj_set_height(ui_brandPanel, lv_pct(200));
    lv_obj_set_align(ui_brandPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_brandPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_brandPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_brandPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_brandPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_brandPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_brandPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_brandPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_brandPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_brandPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_brandPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_brandPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_brandPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_brandPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_brandPanel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingBtn = lv_btn_create(ui_brandPanel);
    lv_obj_set_width(ui_settingBtn, 36);
    lv_obj_set_height(ui_settingBtn, 33);
    lv_obj_set_align(ui_settingBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_settingBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_settingBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_settingBtn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_settingBtn, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_settingBtn, &ui_img_1704081452, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_settingBtn, lv_color_hex(0x4040FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_settingBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_settingBtn, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_settingBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_settingBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_settingBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(ui_settingBtn, settingBtnEvent, LV_EVENT_ALL, NULL);

    ui_brandLabel = lv_label_create(ui_brandPanel);
    lv_obj_set_width(ui_brandLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_brandLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_brandLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_brandLabel, "XO-11");
    lv_obj_set_style_text_color(ui_brandLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_brandLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_indicatorPanel = lv_obj_create(ui_header);
    lv_obj_set_width(ui_indicatorPanel, 151);
    lv_obj_set_height(ui_indicatorPanel, lv_pct(243));
    lv_obj_set_align(ui_indicatorPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_indicatorPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_indicatorPanel, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_indicatorPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_indicatorPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_indicatorPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_indicatorPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_indicatorPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_indicatorPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_indicatorPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_indicator = lv_obj_create(ui_indicatorPanel);
    lv_obj_set_width(ui_indicator, 24);
    lv_obj_set_height(ui_indicator, 24);
    lv_obj_set_align(ui_indicator, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_indicator, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_indicator, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_indicator, lv_color_hex(0x00000010), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_indicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_indicator, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_indicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_indicator, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi = lv_img_create(ui_indicatorPanel);
    lv_img_set_src(ui_wifi, &ui_img_194527309);
    lv_obj_set_width(ui_wifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_wifi, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_wifi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_wifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_wifi, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ltiepanel = lv_obj_create(ui_home);
    lv_obj_set_width(ui_ltiepanel, lv_pct(100));
    lv_obj_set_height(ui_ltiepanel, lv_pct(44));
    lv_obj_set_align(ui_ltiepanel, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_ltiepanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_ltiepanel, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_ltiepanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ltiepanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ltiepanel, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ltiepanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ltiepanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ltiepanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ltiepanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ltiepanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ltiepanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ltiepanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_ltiepanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_ltiepanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Bar2 = lv_bar_create(ui_ltiepanel);
    lv_bar_set_range(ui_Bar2, 0, 10);
    lv_bar_set_value(ui_Bar2, 0, LV_ANIM_OFF);
    lv_obj_set_height(ui_Bar2, 5);
    lv_obj_set_width(ui_Bar2, lv_pct(100));
    lv_obj_set_align(ui_Bar2, LV_ALIGN_CENTER);

    ui_lineoutput = lv_label_create(ui_ltiepanel);
    lv_obj_set_width(ui_lineoutput, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lineoutput, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lineoutput, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lineoutput, "Total line output");
    lv_obj_set_style_text_color(ui_lineoutput, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lineoutput, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lineoutput, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_countpanel = lv_obj_create(ui_ltiepanel);
    lv_obj_set_height(ui_countpanel, 24);
    lv_obj_set_width(ui_countpanel, lv_pct(100));
    lv_obj_set_x(ui_countpanel, 0);
    lv_obj_set_y(ui_countpanel, -2);
    lv_obj_set_align(ui_countpanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_countpanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_countpanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_countpanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_countpanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_countpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_countpanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_countpanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_countpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_countpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_countpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_countpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_countpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_countpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_countpanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_totalOutput = lv_label_create(ui_countpanel);
    lv_obj_set_width(ui_totalOutput, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_totalOutput, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_totalOutput, LV_ALIGN_CENTER);
    lv_label_set_text(ui_totalOutput, "0");
    lv_obj_set_style_text_color(ui_totalOutput, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_totalOutput, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_totalOutput, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_device = lv_label_create(ui_countpanel);
    lv_obj_set_width(ui_device, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_device, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_device, LV_ALIGN_CENTER);
    lv_label_set_text(ui_device, "/");
    lv_obj_set_style_text_color(ui_device, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_device, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_device, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_quantity = lv_label_create(ui_countpanel);
    lv_obj_set_width(ui_quantity, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_quantity, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_quantity, LV_ALIGN_CENTER);
    lv_label_set_text(ui_quantity, "0");
    lv_obj_set_style_text_color(ui_quantity, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_quantity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_quantity, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_countpanel1 = lv_obj_create(ui_ltiepanel);
    lv_obj_set_height(ui_countpanel1, 22);
    lv_obj_set_width(ui_countpanel1, lv_pct(94));
    lv_obj_set_x(ui_countpanel1, 0);
    lv_obj_set_y(ui_countpanel1, -2);
    lv_obj_set_align(ui_countpanel1, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_countpanel1, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_countpanel1, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END);
    lv_obj_clear_flag(ui_countpanel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_countpanel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_countpanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_countpanel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_countpanel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_countpanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_countpanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_countpanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_countpanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_countpanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_countpanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_countpanel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dayOutput = lv_obj_create(ui_countpanel1);
    lv_obj_set_width(ui_dayOutput, 149);
    lv_obj_set_height(ui_dayOutput, 24);
    lv_obj_set_align(ui_dayOutput, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_dayOutput, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_dayOutput, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dayOutput, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_dayOutput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_dayOutput, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dayOutput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_dayOutput, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_dayOutput, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_dayOutput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_dayOutput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_dayOutput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_dayOutput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_dayOutput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_dayOutput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_dayOutput, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label = lv_label_create(ui_dayOutput);
    lv_obj_set_width(ui_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label, "Day output:");
    lv_obj_set_style_text_color(ui_label, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_valueDayOut = lv_label_create(ui_dayOutput);
    lv_obj_set_width(ui_valueDayOut, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_valueDayOut, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_valueDayOut, LV_ALIGN_CENTER);
    lv_label_set_text(ui_valueDayOut, "00");
    lv_obj_set_style_text_color(ui_valueDayOut, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_valueDayOut, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_valueDayOut, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dayOutput1 = lv_obj_create(ui_countpanel1);
    lv_obj_set_width(ui_dayOutput1, 135);
    lv_obj_set_height(ui_dayOutput1, 27);
    lv_obj_set_align(ui_dayOutput1, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_dayOutput1, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_dayOutput1, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_dayOutput1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_dayOutput1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_dayOutput1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dayOutput1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_dayOutput1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_dayOutput1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_dayOutput1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_dayOutput1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_dayOutput1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_dayOutput1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_dayOutput1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_dayOutput1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_dayOutput1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label4 = lv_label_create(ui_dayOutput1);
    lv_obj_set_width(ui_label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label4, "Target output:");
    lv_obj_set_style_text_color(ui_label4, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label4, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_valueDayOut1 = lv_label_create(ui_dayOutput1);
    lv_obj_set_width(ui_valueDayOut1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_valueDayOut1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_valueDayOut1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_valueDayOut1, "00");
    lv_obj_set_style_text_color(ui_valueDayOut1, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_valueDayOut1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_valueDayOut1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_btnPanel = lv_obj_create(ui_home);
    lv_obj_set_width(ui_btnPanel, lv_pct(100));
    lv_obj_set_height(ui_btnPanel, lv_pct(36));
    lv_obj_set_align(ui_btnPanel, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_btnPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_btnPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_scroll_dir(ui_btnPanel, LV_DIR_VER);
    lv_obj_set_style_bg_color(ui_btnPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnPanel, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_btnPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_btnPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_btnPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_redbtn = lv_btn_create(ui_btnPanel);
    lv_obj_set_width(ui_redbtn, 120);
    lv_obj_set_height(ui_redbtn, 50);
    lv_obj_set_align(ui_redbtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_redbtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_redbtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_redbtn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_redbtn, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_redbtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_redbtn, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_redbtn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_redbtn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_redbtn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_redbtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_redbtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * minusLabel = lv_label_create(ui_redbtn);
    lv_obj_set_width(minusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(minusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(minusLabel, LV_ALIGN_CENTER);
    lv_label_set_text(minusLabel, "-");
    lv_obj_set_style_text_color(minusLabel, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(minusLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(minusLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_greenBtn = lv_btn_create(ui_btnPanel);
    lv_obj_set_width(ui_greenBtn, 120);
    lv_obj_set_height(ui_greenBtn, 50);
    lv_obj_set_align(ui_greenBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_greenBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_greenBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_greenBtn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_greenBtn, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_greenBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_greenBtn, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_greenBtn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_greenBtn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_greenBtn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_greenBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_greenBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    countLabel = lv_label_create(ui_greenBtn);
    lv_obj_set_width(countLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(countLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(countLabel, LV_ALIGN_CENTER);
    lv_label_set_text(countLabel, "+");
    lv_obj_set_style_text_color(countLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(countLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(countLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    

}
void listItem(const char *item)
{
    ui_descripttion1 = lv_label_create(ui_machineListItem);
    lv_obj_set_width(ui_descripttion1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_descripttion1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_descripttion1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_descripttion1, item);
    lv_obj_set_style_text_color(ui_descripttion1, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_descripttion1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_descripttion1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
}
void machineList(const char *subType, const char *mc, const char *station)
{
    // json String and deserialize

    ui_machineListItem = lv_obj_create(ui_machineList);
    lv_obj_set_width(ui_machineListItem, 289);
    lv_obj_set_height(ui_machineListItem, 64);
    lv_obj_set_align(ui_machineListItem, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_machineListItem, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_machineListItem, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_machineListItem, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_machineListItem, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_machineListItem, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_machineListItem, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_machineListItem, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_machineListItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_listTitle1 = lv_label_create(ui_machineListItem);
    lv_obj_set_width(ui_listTitle1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_listTitle1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_listTitle1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_listTitle1, subType);
    lv_obj_set_style_text_color(ui_listTitle1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_listTitle1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    listItem(mc);
    listItem(station);
    
    lv_obj_add_event_cb(ui_machineListItem, ui_event_machineListItem, LV_EVENT_ALL, NULL);
}
void ui_listOfMachine_screen_init(void)
{
    ui_listOfMachine = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_listOfMachine, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_listOfMachine, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_listOfMachine, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_machineList = lv_obj_create(ui_listOfMachine);
    lv_obj_set_width(ui_machineList, lv_pct(100));
    lv_obj_set_height(ui_machineList, lv_pct(70));
    lv_obj_set_align(ui_machineList, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_machineList, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_machineList, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_scroll_dir(ui_machineList, LV_DIR_VER);
    lv_obj_set_style_bg_color(ui_machineList, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_machineList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_machineList, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_machineList, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_machineList, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_selectListTitle = lv_label_create(ui_listOfMachine);
    lv_obj_set_width(ui_selectListTitle, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_selectListTitle, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_selectListTitle, 20);
    lv_obj_set_y(ui_selectListTitle, 20);
    lv_label_set_text(ui_selectListTitle, "Please select a \nmachine: ");
    lv_obj_set_style_text_color(ui_selectListTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_selectListTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_selectListTitle, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_add_event_cb(ui_listOfMachine, ui_event_listOfMachine, LV_EVENT_ALL, NULL);
    
}
void ui_confirmScreen_screen_init(void)
{
    ui_confirmScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_confirmScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_confirmScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_confirmScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_confirmText = lv_label_create(ui_confirmScreen);
    lv_obj_set_width(ui_confirmText, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_confirmText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_confirmText, 20);
    lv_obj_set_y(ui_confirmText, 10);
    lv_label_set_text(ui_confirmText, "Confirm report a machine\nbreak down?");
    lv_obj_set_style_text_color(ui_confirmText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_confirmText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_confirmText, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_machineList1 = lv_obj_create(ui_confirmScreen);
    lv_obj_set_width(ui_machineList1, lv_pct(100));
    lv_obj_set_height(ui_machineList1, lv_pct(60));
    lv_obj_set_align(ui_machineList1, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_machineList1, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_machineList1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_scroll_dir(ui_machineList1, LV_DIR_VER);
    lv_obj_set_style_bg_color(ui_machineList1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_machineList1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_machineList1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_machineList1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_machineList1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_listLineDetails = lv_obj_create(ui_machineList1);
    lv_obj_set_width(ui_listLineDetails, 289);
    lv_obj_set_height(ui_listLineDetails, 35);
    lv_obj_set_align(ui_listLineDetails, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_listLineDetails, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_listLineDetails, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
    lv_obj_clear_flag(ui_listLineDetails, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_listLineDetails, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_listLineDetails, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_listLineDetails, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_listLineDetails, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_listLineDetails, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label1 = lv_label_create(ui_listLineDetails);
    lv_obj_set_width(ui_label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label1, "Line:");
    lv_obj_set_style_text_color(ui_label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lineIdText = lv_label_create(ui_listLineDetails);
    lv_obj_set_width(ui_lineIdText, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lineIdText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lineIdText, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lineIdText, "XO-01");
    lv_obj_set_style_text_color(ui_lineIdText, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lineIdText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lineIdText, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_listLineDetails1 = lv_obj_create(ui_machineList1);
    lv_obj_set_width(ui_listLineDetails1, 289);
    lv_obj_set_height(ui_listLineDetails1, 35);
    lv_obj_set_align(ui_listLineDetails1, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_listLineDetails1, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_listLineDetails1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
    lv_obj_clear_flag(ui_listLineDetails1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_listLineDetails1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_listLineDetails1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_listLineDetails1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_listLineDetails1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_listLineDetails1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label2 = lv_label_create(ui_listLineDetails1);
    lv_obj_set_width(ui_label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label2, "Station:");
    lv_obj_set_style_text_color(ui_label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lineIdText1 = lv_label_create(ui_listLineDetails1);
    lv_obj_set_width(ui_lineIdText1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lineIdText1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lineIdText1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lineIdText1, "04");
    lv_obj_set_style_text_color(ui_lineIdText1, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lineIdText1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lineIdText1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_listLineDetails2 = lv_obj_create(ui_machineList1);
    lv_obj_set_width(ui_listLineDetails2, 289);
    lv_obj_set_height(ui_listLineDetails2, 35);
    lv_obj_set_align(ui_listLineDetails2, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_listLineDetails2, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_listLineDetails2, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
    lv_obj_clear_flag(ui_listLineDetails2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_listLineDetails2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_listLineDetails2, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_listLineDetails2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_listLineDetails2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_listLineDetails2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label3 = lv_label_create(ui_listLineDetails2);
    lv_obj_set_width(ui_label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label3, "M/C");
    lv_obj_set_style_text_color(ui_label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lineIdText2 = lv_label_create(ui_listLineDetails2);
    lv_obj_set_width(ui_lineIdText2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lineIdText2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lineIdText2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lineIdText2, "LTMC009");
    lv_obj_set_style_text_color(ui_lineIdText2, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lineIdText2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lineIdText2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btnConfirmPanel = lv_obj_create(ui_confirmScreen);
    lv_obj_set_width(ui_btnConfirmPanel, lv_pct(90));
    lv_obj_set_height(ui_btnConfirmPanel, lv_pct(20));
    lv_obj_set_align(ui_btnConfirmPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_btnConfirmPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_btnConfirmPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_btnConfirmPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_btnConfirmPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_btnConfirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_btnConfirmPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_btnConfirmPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_btnConfirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_btnConfirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_btnConfirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_btnConfirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_btnConfirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_btnConfirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_btnConfirmPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_noConfirmBtn = lv_btn_create(ui_btnConfirmPanel);
    lv_obj_set_width(ui_noConfirmBtn, 120);
    lv_obj_set_height(ui_noConfirmBtn, 43);
    lv_obj_set_align(ui_noConfirmBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_noConfirmBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_noConfirmBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_noConfirmBtn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_noConfirmBtn, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_noConfirmBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_noConfirmBtn, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_noConfirmBtn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_noConfirmBtn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_noConfirmBtn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_noConfirmBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_noConfirmBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_noBtnTxt = lv_label_create(ui_noConfirmBtn);
    lv_obj_set_width(ui_noBtnTxt, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_noBtnTxt, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_noBtnTxt, LV_ALIGN_CENTER);
    lv_label_set_text(ui_noBtnTxt, "NO");

    ui_yesConfigmBtn = lv_btn_create(ui_btnConfirmPanel);
    lv_obj_set_width(ui_yesConfigmBtn, 120);
    lv_obj_set_height(ui_yesConfigmBtn, 43);
    lv_obj_set_align(ui_yesConfigmBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_yesConfigmBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_yesConfigmBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_yesConfigmBtn, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_yesConfigmBtn, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_yesConfigmBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_yesConfigmBtn, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_yesConfigmBtn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_yesConfigmBtn, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_yesConfigmBtn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_yesConfigmBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_yesConfigmBtn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_noBtnTxt1 = lv_label_create(ui_yesConfigmBtn);
    lv_obj_set_width(ui_noBtnTxt1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_noBtnTxt1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_noBtnTxt1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_noBtnTxt1, "YES");
    lv_obj_set_style_text_color(ui_noBtnTxt1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_noBtnTxt1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_noConfirmBtn, ui_event_noConfirmBtn, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_noConfirmBtn, event_no_btn, LV_EVENT_ALL, NULL);

}
void ui_settingScreen_screen_init(void)
{
    ui_settingScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_settingScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_settingScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lineDetails = lv_obj_create(ui_settingScreen);
    lv_obj_set_width(ui_lineDetails, lv_pct(100));
    lv_obj_set_height(ui_lineDetails, lv_pct(100));
    lv_obj_set_align(ui_lineDetails, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_lineDetails, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_lineDetails, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_scroll_dir(ui_lineDetails, LV_DIR_VER);
    lv_obj_set_style_bg_color(ui_lineDetails, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_lineDetails, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_lineDetails, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_lineDetails, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_lineDetails, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_add_event_cb(ui_settingScreen, ui_event_listOfMachine, LV_EVENT_ALL, NULL);
}
void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_home_screen_init();
    ui_listOfMachine_screen_init();
    ui_confirmScreen_screen_init();
    ui_settingScreen_screen_init();
    
    lv_disp_load_scr(ui_home);
}
