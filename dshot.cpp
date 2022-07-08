#include "dshot.h"
#include "dshot.pio.h"

DshotESC::DshotESC() {}

DshotESC::~DshotESC() {}

void DshotESC::init(uint pin) {
    pio = pio0;
    uint offset = pio_add_program(pio, &dshot_program);
    sm = pio_claim_unused_sm(pio, true);
    dshot_program_init(pio, sm, offset, pin);
    pio_sm_set_clkdiv(pio, sm, 17.36);
    gpio_set_function(pin, GPIO_FUNC_PIO0);
}

void DshotESC::send(uint16_t command) {
    bool telemetry_requested = false;
    uint16_t dshot_frame = (command << 5) | (telemetry_requested << 4);
    uint16_t checksum = (dshot_frame >> 4) ^ (dshot_frame >> 8) ^ (dshot_frame >> 12);
    dshot_frame |= checksum & 0x000f;
    pio_sm_put_blocking(pio, sm, dshot_frame << 16);
}