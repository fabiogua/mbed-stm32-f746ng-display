#include "mbed.h"

#include "../lib/hal_stm_lvgl/touchpad/touchpad.h"
#include "../lib/hal_stm_lvgl/tft/tft.h"
#include "../lib/display/src/ui.h"
// #include "canService.cpp"

// Define can1 interface pins
#define LVGL_TICK 30 // Time tick value for lvgl in ms (1-10msa)

/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#if !DEVICE_CAN
#error[NOT_SUPPORTED] CAN not supported for this target
#endif

#define DEBUG_CAN 1

Ticker ticker;
Thread thread;

#define CAN_RD PB_8 // Adjust according to your hardware
#define CAN_TD PB_9

CAN can1(CAN_RD, CAN_TD, 100000);

void send_thread()
{

    CANMessage msg(80, "1", 1);
    while (true)
    {
#ifdef DEBUG
        printf("send()\n");
#endif

        if (can1.write(msg))
        {
#ifdef DEBUG
            printf("wloop()\n");
            printf("Message sent: %d\n", msg.id);
#endif
        }
        ThisThread::sleep_for(1s);
    }
}

void lv_ticker_thread()
{
    while (true)
    {
#ifdef DEBUG
        printf("lv_ticker_thread()\n");
#endif
        lv_task_handler();
        lv_tick_inc(LVGL_TICK);
        ThisThread::sleep_for(LVGL_TICK);
    }
}

int main()
{
    CANMessage msg;

    can1.filter(291, 0xFFF, CANStandard, 0);

    // Lvgl init
    lv_init();
    tft_init();
    touchpad_init();

    // Create a thread to handle lvgl tasks
    thread.start(lv_ticker_thread);

    ui_init();

    while (1)
    {
        if (can1.read(msg))
        {
#ifdef DEBUG
            printf("Message received: %d\n", msg.id);
#endif

        if (msg.id == 293)
            {
                uint16_t gasvalue = (uint16_t)msg.data[0] + ((uint16_t)msg.data[1] << 8);
                uint8_t gas_percentage = (uint8_t (gasvalue * 100 / 4095));

                lv_label_set_text_fmt(ui_label1, "%d%", gas_percentage);
                lv_bar_set_value(ui_bar1, (uint8_t)gas_percentage, LV_ANIM_ON);

                printf("Gas value: %d\n Gas percentage: %d\n", gasvalue , gas_percentage);
            }
            else
            {
            // byte 0: battery voltage & 0xFF
            // byte 1: battery voltage  >> 8
            // byte 2: battery current & 0xFF
            // byte 3: battery current >> 8
            // byte 4: battery temperature
            // byte 5: motor temperature
            // byte 6: power mode

            // battery voltage range is 0-500V in 0.1V-> 2 bytes
            // battery temperature range is -40-215C in 1C -> 1 byte
            // battery current range is -50000-100000A in 10A -> 2 bytes
            // motor temperature range is -40-215C in 1C -> 1 byte
            // power mode range is 0-255 -> 1 byte

            uint16_t battery_voltage = (uint32_t)msg.data[0] + ((uint32_t)msg.data[1] << 8);
            uint16_t battery_current = (uint32_t)msg.data[2] + ((uint32_t)msg.data[3] << 8);
            uint8_t battery_temperature = (uint32_t)msg.data[4];
            uint8_t motor_temperature = (uint32_t)msg.data[5];
            uint8_t powermode = (uint8_t)msg.data[6];
            switch (powermode)
            {
            case 0:
                powermode = 40;
                break;
            case 1:
                powermode = 60;
                break;
            case 2:
                powermode = 80;
                break;
            default:
                powermode = 0;
                break;
            }


            uint32_t power = battery_voltage * battery_current /1000;

            lv_label_set_text_fmt(ui_soclabel, "%d %c", battery_voltage / 50, '%');
            lv_bar_set_value(ui_socbar, (uint8_t)(battery_voltage / 50), LV_ANIM_ON);
            lv_label_set_text_fmt(ui_batteryvoltagelabel, "%dV", battery_voltage / 10);

            lv_label_set_text_fmt(ui_label4, "%d°C", battery_temperature);
            lv_bar_set_value(ui_bar3, (uint8_t)battery_temperature*100/255, LV_ANIM_ON);

            lv_label_set_text_fmt(ui_label1, "%d°C", motor_temperature);
            lv_bar_set_value(ui_bar1, (uint8_t)motor_temperature*100/255, LV_ANIM_ON);

            lv_label_set_text_fmt(ui_label3, "%d kW", powermode);
        }
        }

        ThisThread::sleep_for(1ms);
    }
}
