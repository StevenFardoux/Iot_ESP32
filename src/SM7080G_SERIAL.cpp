#include "SM7080G_SERIAL.hpp"

String send_AT(String message, unsigned int time)
{
    char tmp_char = 0;
    String str = "";
    unsigned long period1 = millis();

    Serial.println(" ");
    Serial.println("=============== AT MESSAGE ===============");

    Sim7080G.println(message);

    while (millis() - period1 < time && !str.endsWith("OK"))
    {
        if (Sim7080G.available())
        {
            tmp_char = Sim7080G.read();
            str += tmp_char;
        }
    }
    if (str == nullptr)
    {
        return "";
    }

    // Remove first "\n"
    // Serial.println("str len 1 : " + str.length());
    str.remove(0, 2);
    Serial.println("AT response : " + str);

    Serial.println("==========================================");
    Serial.println(" ");

    // Serial.println("AT res : " + str);
    // Serial.println("str len 2 : " + str.length());
    str.remove(0, str.indexOf(':') + 2);

    // Serial.println("str len 3 : " + str.length());

    str.remove(str.indexOf('\n'), str.length());

    // Serial.println("str return : " + str);

    return str;
}
