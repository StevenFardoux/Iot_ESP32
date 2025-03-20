#include "SIM7080G_CATM1.hpp"

bool isConnected(String str)
{
    if (str == nullptr || !str)
        return false;
    if (atoi(str.c_str()) <= 4)
    {
        // Serial.println("Return false");

        return false;
    }
    else
    {
        // Serial.println("Return true");

        return true;
    }
}

bool isRetrievesIP(String str)
{
    String resIp = Split(str, ',')[2]; // Retrives juste IP
    String splitIp = Split(resIp, '.')[0]; // Retrieves first bit of IP
    splitIp = splitIp.substring(1, splitIp.length()); // Remove " from the beginning

    Serial.println("Res AT CNACT? : " + str);
    Serial.println("Res Spit IP : " + resIp);
    Serial.println("Split bit IP : " + splitIp);
    Serial.printf("atoi bit IP : %d \n", atoi(splitIp.c_str()));

    if (atoi(splitIp.c_str()) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void setup_CATM1()
{
    String resAT, resPDP, resSignal = "";
    unsigned long timer;

    // You must turn off GNSS before turning on CATM1
    turn_off_GNSS();

    // see datasheet
    send_AT("AT+CNMP=38");

    /*
    WARNING on the ARGALI SIM C3 V1.0 the SIMCOM processor used is
    SIM7080G-M that does not feature NB-IOT.
    1 -> CAT-M1 et 2 -> NB-IOT
    */
    send_AT("AT+CMNB=1");

    // APP Network Deactive(PDP context)
    send_AT("AT+CNACT=0,0");

    // paramétrage de l'APN (Access Point Name)
    send_AT("AT+CGDCONT=1,\"IP\",\"iot.1nce.net\"");
    send_AT("AT+CGNAPN");
    send_AT("AT+CNCFG=0,1,iot.1nce.net");

    // APP Network Active (PDP context)
    // You should wait for a valid response : +APP PDP: 0,ACTIVE

    resAT = send_AT("AT+CNACT=0,1", 15000);

    if (resAT != "")
    {
        resPDP = Split(resAT, ',')[1];

        if (resPDP != "")
        {
            Serial.println("No response from PDP");
        }
        else
        {
            Serial.printf("PDP est %d \n", resPDP);
        }
    }

    /*
    We wait for the SIM7080G to register to the local 4G antenna
    Correct registration :
    AT+CEREG?
    +CEREG: 0,5
    */

    timer = millis();
    resAT = "";
    while (true)
    {
        if (millis() - timer > 1000)
        {
            resAT = send_AT("AT+CEREG?");

            Serial.println("Response : " + resAT);
            resAT.trim();

            if (resAT != "")
            {
                resSignal = Split(resAT, ',')[1];

                Serial.println("Signal : " + resSignal);
            }

            if (isConnected(resSignal))
            {

                break;
            }
            timer = millis();
        }
    }


    // informations for you on CAT-M1 connexion
    send_AT("AT+CGATT?");

    timer = millis();
    resAT = "";
    while (true)
    {
        if (millis() - timer > 1000)
        {
            resAT = send_AT("AT+CNACT?");

            if (isRetrievesIP(resAT))
            {
                break;
            }
            timer = millis();
        }
    }

    send_AT("AT+GSN");
    send_AT("AT+CCID");
    send_AT("AT+COPS?");
    send_AT("AT+CEREG?");

    // signal quality
    send_AT("AT+CSQ");
}

void loop_CATM1()
{
    send_AT("AT+CEREG?");
    send_AT("AT+CSQ");
}
