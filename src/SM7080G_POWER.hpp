#pragma once
#include "Arduino.h"
#include "SM7080G_SERIAL.hpp"
#include "ARGARI_PINOUT.hpp"

void turn_on_SM7080G();
void reboot_SM7080G();
void hard_resest_SIM7080G();
void battery_info();

String turn_off_SM7080G();