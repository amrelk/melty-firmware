#include "LIS331.h"
#include <cstring>

#define CTRL_REG1        0x20
#define CTRL_REG2        0x21
#define CTRL_REG3        0x22
#define CTRL_REG4        0x23
#define CTRL_REG5        0x24
#define HP_FILTER_RESET  0x25
#define REFERENCE        0x26
#define STATUS_REG       0x27
#define OUT_X_L          0x28
#define OUT_X_H          0x29
#define OUT_Y_L          0x2A
#define OUT_Y_H          0x2B
#define OUT_Z_L          0x2C
#define OUT_Z_H          0x2D
#define INT1_CFG         0x30
#define INT1_SOURCE      0x31
#define INT1_THS         0x32
#define INT1_DURATION    0x33
#define INT2_CFG         0x34
#define INT2_SOURCE      0x35
#define INT2_THS         0x36
#define INT2_DURATION    0x37
#define AUTO_INC         0x80

LIS331::LIS331() {}

LIS331::~LIS331() {}

void LIS331::init(i2c_inst_t* inst) {
    i2cInst = inst;
    setPowerMode(NORMAL);
    enableAllAxes();
}

void LIS331::setPowerMode(power_mode mode) {
    uint8_t data;
    reg_read(CTRL_REG1, &data, 1);
    data &= 0x1f; // clear top three bits
    data |= mode << 5; // set top three bits to mode
    reg_write(CTRL_REG1, &data, 1);
}

void LIS331::enableAxes(bool xEn, bool yEn, bool zEn) {
    uint8_t data;
    reg_read(CTRL_REG1, &data, 1);
    data &= 0xf8; // clear bottom three bits
    data |= (zEn & 0x1) << 2 | (yEn & 0x1) << 1 | (xEn & 0x1);
    reg_write(CTRL_REG1, &data, 1);
}

void LIS331::enableAllAxes(bool en) {
    enableAxes(en, en, en);
}

void LIS331::setRange(fs_range range) {
    uint8_t data;
    reg_read(CTRL_REG4, &data, 1);
    data &= 0xcf;
    data |= range << 4;
    reg_write(CTRL_REG4, &data, 1);
}

void LIS331::readAxes(int16_t &x, int16_t &y, int16_t &z) {
    uint8_t buf[6];
    reg_read(OUT_X_L, buf, 6);
    x = buf[0] | (buf[1] << 8);
    y = buf[2] | (buf[3] << 8);
    z = buf[4] | (buf[5] << 8);
    x >>= 4; y >>= 4; z >>= 4;
}

void LIS331::readX(int16_t &x) {
    uint8_t buf[2];
    reg_read(OUT_X_L, buf, 2);
    x = buf[0] | (buf[1] << 8);
    x >>= 4;
}

void LIS331::readY(int16_t &y) {
    uint8_t buf[2];
    reg_read(OUT_Y_L, buf, 2);
    y = buf[0] | (buf[1] << 8);
    y >>= 4;
}   

void LIS331::readZ(int16_t &z) {
    uint8_t buf[2];
    reg_read(OUT_Z_L, buf, 2);
    z = buf[0] | (buf[1] << 8);
    z >>= 4;
}

uint8_t LIS331::dataAvailable() {
    uint8_t buf;
    reg_read(STATUS_REG, &buf, 1);
    return buf & 0x07;
}

int LIS331::reg_write(const uint8_t reg, uint8_t *buf, const uint8_t len) {
    if (len < 1)
        return 0;
    uint8_t msg[len+1];
    msg[0] = reg | AUTO_INC;
    std::memcpy(msg+1, buf, len);
    i2c_write_blocking(i2cInst, addr, msg, len+1, false);
    return 0;
}

int LIS331::reg_read(uint8_t reg, uint8_t *buf, const uint8_t len) {
    if (len < 1)
        return 0;
    reg |= AUTO_INC;
    i2c_write_blocking(i2cInst, addr, &reg, 1, true);
    uint bytes_read = i2c_read_blocking(i2cInst, addr, buf, len, false);
    return bytes_read;
}