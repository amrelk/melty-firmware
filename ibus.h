#include <hardware/uart.h>

class IBus
{
private:
    static constexpr uint8_t max_frame_size = 0x20;
    static constexpr uint8_t protocol_overhead = 4;
    static constexpr uint8_t max_channels = (max_frame_size - protocol_overhead) / 2;

    uart_inst_t * uart;
    uint8_t byteIndex = 0;
    uint8_t frameLength;
    uint16_t checksum;
    uint8_t chkLsb;
    uint8_t buf[max_frame_size - protocol_overhead];
    uint16_t channel[max_channels];

    void handleInput(uint8_t);
    
public:
    IBus();
    ~IBus();
    void init(uart_inst_t * uart);
    uint16_t getChannel(uint8_t ch);
    void interruptHandler();
};