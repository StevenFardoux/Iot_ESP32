#include "SM7080G_POWER.hpp"
#include "SIM7080G_GNSS.hpp"

#define Sim7080G Serial1
#define Sim7080G_BAUDRATE 57600

unsigned long period;

void setup()
{
  pinMode(PIN_PWKEY, OUTPUT);

  Sim7080G.flush();
  reboot_SM7080G();

  Serial.begin(115200);

  Serial.println(" ");
  Serial.println("=============== STARTING ===============");

  Serial.println("Hello world !");

  Sim7080G.begin(Sim7080G_BAUDRATE, SERIAL_8N1, PIN_RX, PIN_TX);
  send_AT("AT+SIMCOMATI");

  setup_GNSS();

  period = millis();

  Serial.println("=======================================");
  Serial.println(" ");
}

void loop()
{
  if (millis() - period > 1000)
  {
    period = millis();

    battery_info();
    get_info_GNSS();
  }
}
