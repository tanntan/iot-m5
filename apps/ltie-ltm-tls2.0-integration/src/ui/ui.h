// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif


void blink_Animation(lv_obj_t * TargetObject, int delay);
void ui_list(const char * title, const char *item);
void machineList(const char *subType, const char *mc, const char *station);
extern lv_obj_t * ui_home;
extern lv_obj_t * ui_header;
extern lv_obj_t * ui_brandPanel;
extern lv_obj_t * ui_settingBtn;
extern lv_obj_t * ui_brandLabel;
extern lv_obj_t * ui_indicatorPanel;
extern lv_obj_t * ui_indicator;
extern lv_obj_t * ui_wifi;
extern lv_obj_t * ui_ltiepanel;
extern lv_obj_t * ui_Bar2;
extern lv_obj_t * ui_lineoutput;
extern lv_obj_t * ui_countpanel;
extern lv_obj_t * ui_totalOutput;
extern lv_obj_t * ui_device;
extern lv_obj_t * ui_quantity;
extern lv_obj_t * ui_countpanel1;
extern lv_obj_t * ui_dayOutput;
extern lv_obj_t * ui_label;
extern lv_obj_t * ui_valueDayOut;
extern lv_obj_t * ui_dayOutput1;
extern lv_obj_t * ui_label4;
extern lv_obj_t * ui_valueDayOut1;
extern lv_obj_t * ui_btnPanel;
void ui_event_redbtn(lv_event_t * e);
extern lv_obj_t * ui_redbtn;
extern lv_obj_t * ui_greenBtn;
extern lv_obj_t * ui_lineDetails;
extern lv_obj_t * ui_listPanel;
extern lv_obj_t * ui_listTitle;
extern lv_obj_t * ui_descripttion;
void ui_event_listOfMachine(lv_event_t * e);
extern lv_obj_t * ui_listOfMachine;
extern lv_obj_t * ui_machineList;
void ui_event_machineListItem(lv_event_t * e);
extern lv_obj_t * ui_machineListItem;
extern lv_obj_t * ui_listTitle1;
extern lv_obj_t * ui_descripttion1;
extern lv_obj_t * ui_selectListTitle;
extern lv_obj_t * ui_confirmScreen;
extern lv_obj_t * ui_confirmText;
extern lv_obj_t * ui_machineList1;
extern lv_obj_t * ui_listLineDetails;
extern lv_obj_t * ui_label1;
extern lv_obj_t * ui_lineIdText;
extern lv_obj_t * ui_listLineDetails1;
extern lv_obj_t * ui_label2;
extern lv_obj_t * ui_lineIdText1;
extern lv_obj_t * ui_listLineDetails2;
extern lv_obj_t * ui_label3;
extern lv_obj_t * ui_lineIdText2;
extern lv_obj_t * ui_btnConfirmPanel;
void ui_event_noConfirmBtn(lv_event_t * e);
extern lv_obj_t * ui_noConfirmBtn;
extern lv_obj_t * ui_noBtnTxt;
void ui_event_yesConfigmBtn(lv_event_t * e);
extern lv_obj_t * ui_yesConfigmBtn;
extern lv_obj_t * ui_noBtnTxt1;
extern lv_obj_t * ui_settingScreen;

extern lv_obj_t * countLabel;


LV_IMG_DECLARE(ui_img_194527309);    // assets\wifi (3).png
LV_IMG_DECLARE(ui_img_1704081452);



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
