#include "hardware/pio.h"

class DshotESC
{
private:
    PIO pio;
    uint sm;
    double baudToClk(uint baud);
public:
    DshotESC();
    ~DshotESC();
    void init(uint pin);
    void send(uint16_t throttle);
};