#include "SM7080G_POWER.hpp"


void turn_on_SM7080G()
{
    digitalWrite(PIN_PWKEY, LOW);
    delay(200);
    digitalWrite(PIN_PWKEY, OUTPUT_OPEN_DRAIN);
    delay(3000);
}


String turn_off_SM7080G() 
{
   return send_AT("AT+CPOWD=1");
}

void reboot_SM7080G() 
{
    turn_off_SM7080G();
    turn_on_SM7080G();
}

void hard_resest_SIM7080G() 
{
    digitalWrite(PIN_PWKEY, LOW);
    delay(15000);
    digitalWrite(PIN_PWKEY, OUTPUT_OPEN_DRAIN);
    delay(3000);
}

void battery_info() 
{
    String res = send_AT("AT+CBC");
    
    Serial.println("");
    Serial.println("=============== BATTERY INFO ===============");

    Serial.println("Charge status : " + res.substring(res.indexOf(",") -1, res.indexOf(",")));
    Serial.println("Battery connection level : " + res.substring(res.indexOf(",") + 1, res.lastIndexOf(",")));
    Serial.println("Battery voltage : " + res.substring(res.lastIndexOf(",") + 1) + " mV");  

    Serial.println("============================================");
    Serial.println("");
}