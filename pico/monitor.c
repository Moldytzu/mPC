#include <stdio.h>
#include "pico/stdlib.h"

// cpu pins
#define ADDRESS_START 0
#define ADDRESS_END 15
#define DATA_START 17
#define DATA_END 28
#define CLOCK 16
#define RW 28

bool clockState = false;

void printState()
{
    uint16_t address = 0;
    uint8_t data = 0;
    bool read = gpio_get(RW);

    for (int i = ADDRESS_START; i <= ADDRESS_END; i++)
    {
        bool state = gpio_get(i);
        // address >>= 1;
        // address |= state << 15;
        address <<= 1;
        address |= state;
    }

    for (int i = DATA_START; i <= DATA_END; i++)
    {
        bool state = gpio_get(i);
        // address >>= 1;
        // address |= state << 7;
        data <<= 1;
        data |= state;
    }

    printf("%s address: %x data: %x\n", read ? "r" : "w", address, data);
}

bool clockHandler(struct repeating_timer *t)
{
    clockState = !clockState;
    gpio_put(CLOCK, clockState);

    if (!clockState) // print state on falling edge
        printState();

    return true;
}

int main()
{
    stdio_usb_init();

    gpio_init(CLOCK);
    gpio_set_dir(CLOCK, GPIO_OUT);

    gpio_init(RW);
    gpio_set_dir(RW, GPIO_IN);

    for (int i = ADDRESS_START; i <= ADDRESS_END; i++)
    {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
    }

    for (int i = DATA_START; i <= DATA_END; i++)
    {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
    }

    struct repeating_timer timer;
    add_repeating_timer_us(-8 /*125 khz*/, clockHandler, NULL, &timer);

    while (1)
        ;
}