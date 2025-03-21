#pragma once
#include "Arduino.h"
#include "SM7080G_POWER.hpp"
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


#define Sim7080G Serial1

String send_AT(String message, unsigned int time = 2000);
void send_TCP_data(json *data);

