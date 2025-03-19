#include "Fuction.hpp"


std::vector<String> Split(String str, char delimiter) 
{
    std::vector<String> tabRes;
    int pos;

    while ((pos = str.indexOf(delimiter)) != -1)
    {
        tabRes.push_back(str.substring(0, pos));
        str.remove(0, pos + 1);
    }
    tabRes.push_back(str);

    return tabRes;
}