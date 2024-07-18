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

    printf("main()\n");
    CANMessage msg;

    can1.filter(291, 0xFFF, CANStandard, 0);

    // Lvgl init
    lv_init();
    tft_init();
    touchpad_init();

    // Create a thread to handle lvgl tasks
    thread.start(lv_ticker_thread);
    // thread.start(lv_task_handler_thread);
    // thread.start(send_thread);

    ui_init();


    while (1)
    {
#ifdef DEBUG_CAN
        if (can1.read(msg))
        printf("Message received: %d\n", msg.id);
#else
        can1.read(msg);

#endif

        ThisThread::sleep_for(1ms);
    }
}
