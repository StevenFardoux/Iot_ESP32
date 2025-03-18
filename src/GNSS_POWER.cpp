#include "GNSS_POWER.hpp"

void turn_on_GNSS() 
{
    send_AT("AT+CGNSPWR=1");
}

void turn_off_GNSS() 
{
    send_AT("AT+CGNSPWR=0");
}