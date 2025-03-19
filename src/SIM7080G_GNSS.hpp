#include "SM7080G_SERIAL.hpp"
#include "Fuction.hpp"


struct floatGps
{
    uint8_t integer;
    uint32_t decimal;
};

void setup_GNSS();
void turn_off_GNSS();
void get_info_GNSS(); 