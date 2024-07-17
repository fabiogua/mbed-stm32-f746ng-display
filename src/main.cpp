#include "mbed.h"

#include "../lib/hal_stm_lvgl/touchpad/touchpad.h"
#include "../lib/hal_stm_lvgl/tft/tft.h"
#include "../lib/display/src/ui.h"

// Define CAN interface pins
#define CAN_RD PB_8  // Adjust according to your hardware
#define CAN_TD PB_9
#define LVGL_TICK 10     // Time tick value for lvgl in ms (1-10msa)
#define TICKER_TIME 0.01 // modified to miliseconds

/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN not supported for this target
#endif


Ticker ticker;
DigitalOut led1(LED1);
/** The constructor takes in RX, and TX pin respectively.
  * These pins, for this example, are defined in mbed_app.json
  */
CAN can1(CAN_RD, CAN_TD);
char counter = 0;
    static void lv_ticker_func()
    {
        lv_tick_inc(LVGL_TICK);
    }


void send()
{
    printf("send()\n");
    if (can1.write(CANMessage(80, &counter, 1))) {
        printf("wloop()\n");
        counter++;
        printf("Message sent: %d\n", counter);
    }
    led1 = !led1;
}

Thread thread;

void send_thread()
{
    while (true) {
        send();
        ThisThread::sleep_for(0.1);
    }
}


int main()
{

    can1.frequency(100000);
    can1.mode(CAN::Normal);

    printf("main()\n");
    CANMessage msg;

    // Lvgl init
    lv_init();
    tft_init();
    touchpad_init();

    ticker.attach(callback(&lv_ticker_func), TICKER_TIME); // Attach callback to ticker
    ui_init();


    thread.start(send_thread);

    while (1) {
        if (can1.read(msg)) {
            printf("Message received: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", msg.id, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6], msg.data[7]);
            send();
        }
        if(can1.rderror()) {
            printf("CAN read error\n");
            can1.reset();
        }
        if(can1.tderror()) {
            printf("CAN write error\n");
            can1.reset();
        }


        ThisThread::sleep_for(0.1);
    }
}


