#include <stdio.h>
#include "pico/stdlib.h"

const uint8_t clockPin = 16;
bool clockState = false;

void printState()
{
    uint16_t address = 0;

    for (int i = 0; i <= 15; i++)
    {
        bool state = gpio_get(i);
        address >>= 1;
        address |= state << 15;
    }

    printf("address: %x\n", address);
}

bool clockHandler(struct repeating_timer *t)
{
    clockState = !clockState;
    gpio_put(clockPin, clockState);

    printState();

    return true;
}

int main()
{
    stdio_usb_init();

    set_sys_clock_khz(133000, true);

    gpio_init(clockPin);
    gpio_set_dir(clockPin, GPIO_OUT);

    for (int i = 0; i <= 15; i++)
    {
        gpio_init(i);
        gpio_set_dir(i, GPIO_IN);
    }

    struct repeating_timer timer;
    add_repeating_timer_us(10 /*100 khz*/, clockHandler, NULL, &timer);

    while (1)
        ;
}