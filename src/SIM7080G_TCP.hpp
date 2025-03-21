#pragma
#include "SM7080G_SERIAL.hpp"
#include "SIM7080G_FSM.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;


void TCP_send(uint8_t *state);