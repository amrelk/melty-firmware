#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"

#include "LIS331.h"
#include "dshot.h"
#include "ibus.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

LIS331 accel;
DshotESC esc1;
IBus rx;

bool send_dshot(struct repeating_timer *t) {
    esc1.send(500);
    return true;
}

int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    uart_init(uart1, 115200);
    
    gpio_set_function(5, GPIO_FUNC_UART);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    accel.init(I2C_PORT);
    accel.setRange(accel.FS_100G);

    esc1.init(19);

    esc1.send(0);

    rx.init(uart1);

    struct repeating_timer timer;
    add_repeating_timer_ms(-5, send_dshot, NULL, &timer);
    
    for (;;) {
        rx.interruptHandler();
        esc1.send(0);
        sleep_ms(100);
    }

    return 0;
}
