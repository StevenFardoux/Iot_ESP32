#include "SIM7080G_FSM.hpp"

unsigned long timeout;
uint8_t STATE = 1;


void sim7080g_fsm() 
{
    switch (STATE)
    {
    case TURN_ON:
        Serial.println("- TURN ON");
        turn_on_SM7080G();
        STATE = CATM1_INIT;
        timeout = millis();
        break;

    case CATM1_INIT:
        Serial.println("- INIT CATM1");
        CATM1_fsm(&STATE);
        break;

    case TURN_OFF:
        Serial.println("- TURN OFF");
        turn_off_SM7080G();
        // STATE = TURN_ON;
        break;

    default:
        break;
    }
}