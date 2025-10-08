#ifndef __PC_HARDWARESERIAL_H__
#define __PC_HARDWARESERIAL_H__


#include <Arduino.h>  // สำหรับ String, millis()
#include "Print.h"

#ifdef _WIN32

#include <thread>
#include <mutex>

#define WinSerial HardwareSerial

class HardwareSerial : public Print {
  public:
    HardwareSerial(String com_port) : _com_port(com_port), _is_inited(false) {}
    ~HardwareSerial();

    bool begin(uint32_t baud);
    void end();
    
    uint32_t available();
    char read();
    String readStringUntil(char terminator);
    void setTimeout(uint32_t timeout) { if(timeout > 0) _timeout = timeout; }

    inline size_t write(uint8_t c)    { return this->write((char) c);       }
    inline size_t write(char c)       { return this->_winserial_write(c);   }

    int32_t _winserial_read();
    size_t  _winserial_write(char c);
    void*   _hSerial = nullptr;        // Handle ของ COM port

  private:
    bool    _is_inited = false;
    String  _com_port;
    String  _serial_buffer;           // FIFO buffer
    uint32_t _timeout = 1000;         // Timeout สำหรับ readStringUntil
    std::thread _thread;
    std::mutex _mutex;
};

#endif // _WIN32
#endif // __PC_HARDWARESERIAL_H__
