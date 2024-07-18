// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_screen1
void ui_screen1_screen_init(void);
lv_obj_t * ui_screen1;
lv_obj_t * ui_soccontainer;
lv_obj_t * ui_socbar;
lv_obj_t * ui_soclabel;
lv_obj_t * ui_batteryvoltagelabel;
lv_obj_t * ui_homebar4;
lv_obj_t * ui_bar1;
lv_obj_t * ui_label1;
lv_obj_t * ui_homebar2;
lv_obj_t * ui_bar3;
lv_obj_t * ui_label4;
lv_obj_t * ui_container3;
lv_obj_t * ui_button2;
lv_obj_t * ui_label3;
lv_obj_t * ui_container1;
lv_obj_t * ui_button1;
lv_obj_t * ui_label2;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_screen1);
}
