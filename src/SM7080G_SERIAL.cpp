#include "SM7080G_SERIAL.hpp"

uint8_t nbError = 0;

String send_AT(String message, unsigned int time)
{
    char tmp_char = 0;
    String str = "";
    unsigned long period1 = millis();

    Serial.println(" ");
    Serial.println("=============== AT MESSAGE ===============");

    Sim7080G.println(message);

    // Serial.println("AT Message received : " + message);

    while (millis() - period1 < time && !str.endsWith("OK") && !str.endsWith(">"))
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
    str.trim();

    // Serial.println("str return len : " + str.length());

    return str;
}

void send_TCP_data(json *data)
{
    std::vector<std::uint8_t> vec = json::to_cbor(*data);

    Serial.println(" ");
    Serial.println("=============== AT MESSAGE CBOR ===============");

    Serial.printf("Vector size : %d \n", vec.size());

    send_AT("AT+CASEND=0," + String(vec.size()), 5000);
    for (int i = 0; i <= vec.size(); i++)
    {
        Sim7080G.write((char)vec[i]);
        Serial.print((char)vec[i]);
    }

    Sim7080G.print("\n");

    send_AT("AT+CACLOSE=0");
    
}