#include "Fuction.hpp"
#include <vector>

std::vector<String> Split(String str, char delimiter) 
{
    std::vector<String> tabRes;
    String res = "";
    int pos;
    
    while ((pos = str.indexOf(delimiter)) != -1)
    {
        tabRes.push_back(str.substring(0, pos));
        str.remove(0, pos + 1);
    }
    tabRes.push_back(str);

    return tabRes;
}