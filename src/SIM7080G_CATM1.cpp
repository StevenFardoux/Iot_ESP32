#include "SIM7080G_CATM1.hpp"

unsigned long timerReset;
uint8_t STATE_CATM1 = 1;

bool isConnected(String str)
{
    if (str == nullptr || !str)
        return false;
    if (atoi(str.c_str()) <= 4)
    {
        switch (atoi(str.c_str()))
        {
        case 0:
            if (millis() - timerReset > 5000)
            {
                Serial.println("Signal 0 : reset..");
                hard_resest_SIM7080G();
            }
            break;

        case 2:
            if (millis() - timerReset > 240000)
            {
                Serial.println("Signal 2 : reset..");
                hard_resest_SIM7080G();
            }
            break;

        case 3:
            if (millis() - timerReset > 20000)
            {
                Serial.println("Signal 2 : reset..");
                hard_resest_SIM7080G();
            }
            break;

        default:
            break;
        }
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
    String resIp = Split(str, ',')[2];                // Retrives juste IP
    String splitIp = Split(resIp, '.')[0];            // Retrieves first bit of IP
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

uint8_t getCereg()
{
    String resAT = send_AT("AT+CEREG?");
    uint8_t resSignal = 0;

    // Serial.println("Response : " + resAT);
    resAT.trim();

    if (resAT != "")
    {
        resSignal = atoi(Split(resAT, ',')[1].c_str());
        // Serial.println("Signal : " + resSignal);
    }

    return resSignal;
}

void setup_CATM1_fsm(uint8_t *state_CATM1)
{
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

    *state_CATM1 = PDP;
}

void pdp_fsm(uint8_t *state_MAIN, uint8_t *state_CATM1)
{
    String resAT = send_AT("AT+CNACT=0,1", 15000);
    String resPDP;

    if (resAT != "")
    {
        resPDP = Split(resAT, ',')[1];

        if (resPDP != "")
        {
            Serial.println("No response from PDP");
            // *state_MAIN = TURN_OFF;
            *state_CATM1 = CEREG; // Temporaire
        }
        else
        {
            Serial.printf("PDP is %d \n", resPDP);
            *state_CATM1 = CEREG;
        }
    }
}

void cereg_fsm(uint8_t *state_MAIN, uint8_t *state_CATM1)
{
    uint8_t cereg = getCereg();

    if (cereg == 5)
    {
        *state_CATM1 = IP;
    }
    if (cereg == 0 && timerReset >= 5000)
    {
        *state_MAIN = TURN_OFF;
    }
    if (cereg == 2 && timerReset >= 240000)
    {
        *state_MAIN = TURN_OFF;
    }
    if (cereg == 3 && timerReset >= 20000)
    {
        *state_MAIN = TURN_OFF;
    }
}

void get_IP_fsm(uint8_t *state_CATM1)
{
    String resAT = send_AT("AT+CNACT?");

    if (isRetrievesIP(resAT))
    {
        // *state_CATM1 = TURN_OFF;
    }
}

void CATM1_info()
{
    send_AT("AT+CEREG?");
    send_AT("AT+CSQ");
}

void CATM1_fsm(uint8_t *state_MAIN)
{
    switch (STATE_CATM1)
    {
    case SETUP:
        Serial.println("    |_ SETUP CATM1");
        setup_CATM1_fsm(&STATE_CATM1);
        break;

    case PDP:
        Serial.println("    |_ PDP CATM1");
        pdp_fsm(state_MAIN, &STATE_CATM1);
        timerReset = millis();
        break;

    case CEREG:
        Serial.println("    |_ CEREG CATM1");
        cereg_fsm(state_MAIN, &STATE_CATM1);
        break;

    case IP:
        Serial.println("    |_ IP CATM1");
        get_IP_fsm(state_MAIN);
        break;

    case INFO:
        Serial.println("    |_ INFO CATM1");
        CATM1_info();
        break;

    default:
        break;
    }
}

void setup_CATM1()
{
    String resAT, resPDP, resSignal = "";
    unsigned long timer;

    // APP Network Active (PDP context)
    // You should wait for a valid response : +APP PDP: 0,ACTIVE

    /*
    We wait for the SIM7080G to register to the local 4G antenna
    Correct registration :
    AT+CEREG?
    +CEREG: 0,5
    */

    timerReset = millis();
    timer = millis();
    resAT = "";

    while (true)
    {
        if (millis() - timer > 1000)
        {
            String resAT = send_AT("AT+CEREG?");

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
