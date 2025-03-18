#include "SM7080G_POWER.hpp"
#include "GNSS_POWER.hpp"
#include "GNSS_SERIAL.hpp"

#define Sim7080G Serial1
#define Sim7080G_BAUDRATE 57600

void setup()
{
  pinMode(PIN_PWKEY, OUTPUT);
  reboot_SM7080G();

  Serial.begin(115200);
  Serial.println("Hello world !");

  Sim7080G.begin(Sim7080G_BAUDRATE, SERIAL_8N1, PIN_RX, PIN_TX);
  String res = send_AT("AT+SIMCOMATI");

  turn_on_GNSS();
  set_mode();

  battery_info();
}

void loop()
{
  battery_info();

  GNSS_info();



  delay(1000);

  // Serial.println(millis());
}
