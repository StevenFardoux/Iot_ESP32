#include "SIM7080G_TCP.hpp"

void TCP_send(uint8_t *state)
{
    String res = send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnkdc-185-223-151-250.a.free.pinggy.link\",38037");
    if (res != "0,0")
    {
        if (res == "0,0")
        {
            Serial.println("=======================================================================");
            Serial.println("* URL or IP incorect, chek TCP informations. Trying to get new IP.... *");
            Serial.println("=======================================================================");
            Serial.println("");

            *state = CATM1_INIT;
            return;
        }
        else
        {
            send_AT("AT+CACLOSE=0");
            return;
        }
    }

    json data = {
        {"data", "c'est moi et pas cbor"}};

    send_TCP_data(&data);

    send_AT("AT+CACLOSE=0");
}
