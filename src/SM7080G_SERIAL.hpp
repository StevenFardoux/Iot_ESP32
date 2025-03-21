#pragma once
#include "Arduino.h"
#include "SM7080G_POWER.hpp"

#define Sim7080G Serial1

String send_AT(String message, unsigned int time = 2000);

