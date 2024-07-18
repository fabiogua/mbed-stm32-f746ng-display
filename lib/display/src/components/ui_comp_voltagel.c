// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"


// COMPONENT voltageL

lv_obj_t * ui_voltageL_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_voltageL;
    cui_voltageL = lv_label_create(comp_parent);
    lv_obj_set_width(cui_voltageL, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_voltageL, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_voltageL, -23);
    lv_obj_set_y(cui_voltageL, -27);
    lv_obj_set_align(cui_voltageL, LV_ALIGN_CENTER);
    lv_label_set_text(cui_voltageL, "0.0V");
    lv_obj_set_style_text_font(cui_voltageL, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_VOLTAGEL_NUM);
    children[UI_COMP_VOLTAGEL_VOLTAGEL] = cui_voltageL;
    lv_obj_add_event_cb(cui_voltageL, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_voltageL, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_voltageL_create_hook(cui_voltageL);
    return cui_voltageL;
}

