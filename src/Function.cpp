#include "Fuction.hpp"
#include <sstream>

std::vector<String> Split(String str, char delimiter)
{
    std::vector<String> tabRes;
    int pos;

    // Serial.println("Str received : " + str);

    while ((pos = str.indexOf(delimiter)) != -1)
    {
        tabRes.push_back(str.substring(0, pos));
        str.remove(0, pos + 1);

        // Serial.println("Str push in vector : " + str);
    }
    tabRes.push_back(str);

    // Serial.println("Str push in vector : " + str);
    // Serial.println("Vector size : " + tabRes.size());

    return tabRes;
}