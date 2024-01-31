#include "Debug.hpp"

void Debug::printf(const char *msg)
{
    Communication::sendSerialString((uint8_t*)msg, strlen(msg));
    Communication::sendSerialChar('\n');
}

void Debug::printf(uint16_t number)
{
    Communication::sendSerialInteger(number);
    Communication::sendSerialChar('\n');
}
