#pragma once
#include "SM7080G_SERIAL.hpp"
#include "SIM7080G_GNSS.hpp"
#include "SIM7080G_FSM.hpp"

// CATM1 state
#define SETUP 1
#define PDP 2
#define CEREG 3
#define IP 4
#define INFO 5


bool isConnected();
bool isRetrievesIP(String str);
uint8_t getCereg();

void setup_CATM1_fsm(uint8_t *state_CATM1);
void pdp_fsm(uint8_t *state_MAIN, uint8_t *state_CATM1);
void cereg_fsm(uint8_t *state_MAIN, uint8_t *state_CATM1);
void get_IP_fsm(uint8_t *state_CATM1);
void CATM1_info();

void CATM1_fsm(uint8_t *state);

void setup_CATM1();
void loop_CATM1();
