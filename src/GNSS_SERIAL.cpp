#include "GNSS_SERIAL.hpp"


void GNSS_info() {
    send_AT("AT+CGNSINF");
}

void set_mode() {
    String res = send_AT("AT+CGNSMOD=1,0,0,1,0");

    
}