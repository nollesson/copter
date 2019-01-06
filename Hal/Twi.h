#pragma once

#include <stdint.h>

namespace twi
{
void init();
bool testAddress(uint8_t addr);
bool writeData(uint8_t const address, uint8_t const *const data, int const size, bool shouldStop=true);
bool readData(uint8_t const address, uint8_t *const data, int const size, bool shouldStop=true);
}

