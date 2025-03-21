#pragma once
#include "SIM7080G_CATM1.hpp"
#include "SM7080G_POWER.hpp"
#include "SIM7080G_TCP.hpp"

#define TURN_ON 1
#define CATM1_INIT 2
#define TURN_OFF 3
#define TCP 4
#define NOTHING 99


void sim7080g_fsm();