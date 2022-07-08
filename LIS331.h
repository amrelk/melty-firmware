#pragma once
#include "hardware/i2c.h"

class LIS331
{
private:
    i2c_inst_t* i2cInst;
    uint8_t addr = 0x19;

    int reg_write(const uint8_t reg, uint8_t *buf, const uint8_t len);
    int reg_read(uint8_t reg, uint8_t *buf, const uint8_t len);
public:
    typedef enum {POWER_DOWN, NORMAL, LOW_POWER_0_5HZ, LOW_POWER_1HZ, LOW_POWER_2HZ, LOW_POWER_5HZ, LOW_POWER_10HZ} power_mode;
    typedef enum {FS_100G, FS_200G, FS_X, FS_400G} fs_range;
    LIS331();
    ~LIS331();
    void init(i2c_inst_t* inst);
    void setPowerMode(power_mode mode);
    void enableAllAxes(bool enabled = true);
    void enableAxes(bool xEnable, bool yEnable, bool zEnable);
    void setRange(fs_range range);
    void readAxes(int16_t &x, int16_t &y, int16_t &z);
    void readX(int16_t &x);
    void readY(int16_t &y);
    void readZ(int16_t &z);
    uint8_t dataAvailable();
};