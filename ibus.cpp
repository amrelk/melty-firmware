#include "ibus.h"
#include "cstdio"
#include <hardware/irq.h>

void IBus::init(uart_inst_t * uart) {
    this->uart = uart;
    /*irq_add_shared_handler(UART0_IRQ + uart_get_index(uart), ([this] {this->interruptHandler();}),
                           PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);*/
    
}

uint16_t IBus::getChannel(uint8_t ch) {
    return channel[ch-1];
}

void IBus::interruptHandler() {
    while (uart_is_readable(uart)) {
        handleInput(uart_getc(uart));
    }
    //irq_clear(UART0_IRQ + uart_get_index(uart));
}

void IBus::handleInput(uint8_t byte) {
    if (byteIndex == 0) {
        if (byte == 0x20) {// <= max_frame_size && byte >= protocol_overhead) {
            frameLength = byte;
            checksum = 0xFFFF - byte;
            byteIndex = 1;
        } else {
            byteIndex = 0;
        }
    } else if (byteIndex == 1) {
        if (byte == 0x40) {
            checksum -= byte;
            byteIndex = 2;
        } else {
            byteIndex = 0; //we don't know how to handle anything except 0x40 lol
        }
    } else if (byteIndex < frameLength - 2) {
        buf[byteIndex - 2] = byte;
        checksum -= byte;
        byteIndex++;
    } else if (byteIndex == frameLength - 2) {
        chkLsb = byte;
        byteIndex++;
    } else if (byteIndex == frameLength - 1) {
        if (checksum == (byte << 8) | chkLsb) {
            for (uint8_t i = 0; i < frameLength - protocol_overhead; i += 2) {
                channel[i / 2] = buf[i] | (buf[i + 1] << 8);
            }
        }
        byteIndex = 0;
    } else {
        byteIndex = 0;
    }
}

IBus::IBus() {}
IBus::~IBus() {}