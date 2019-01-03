#pragma once

#include <stdint.h>

namespace twi
{
void init();
bool testAddress(uint8_t addr);
}

