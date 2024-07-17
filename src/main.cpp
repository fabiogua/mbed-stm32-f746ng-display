#include "mbed.h"

// Define CAN interface pins
#define CAN_RD PB_8  // Adjust according to your hardware
#define CAN_TD PB_9
/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN not supported for this target
#endif


#include "mbed.h"


Ticker ticker;
DigitalOut led1(LED1);
/** The constructor takes in RX, and TX pin respectively.
  * These pins, for this example, are defined in mbed_app.json
  */
CAN can1(CAN_RD, CAN_TD);
char counter = 0;

void send()
{
    printf("send()\n");
    if (can1.write(CANMessage(1337, &counter, 1))) {
        printf("wloop()\n");
        counter++;
        printf("Message sent: %d\n", counter);
    }
    led1 = !led1;
}

int main()
{

    can1.frequency(100000);
    can1.mode(CAN::Normal);

    printf("main()\n");
    // ticker.attach(&send, 1);
    CANMessage msg;
    while (1) {
        if (can1.read(msg)) {
            printf("Message received: %d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", msg.id, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6], msg.data[7]);
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
