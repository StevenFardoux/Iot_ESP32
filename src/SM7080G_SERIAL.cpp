#include "SM7080G_SERIAL.hpp"


String send_AT(String message)
{
    char tmp_char = 0;
    String str = "";
    unsigned long period1 = millis();

    Sim7080G.println(message);

    while (millis() - period1 < 2000 && !str.endsWith("OK"))
    {
        if (Sim7080G.available())
        {
            tmp_char = Sim7080G.read();
            str += tmp_char;
        }
    }
    Serial.println(str);
    return str;
}

void everyXs()
{
}