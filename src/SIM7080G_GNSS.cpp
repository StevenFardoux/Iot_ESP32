#include "SIM7080G_GNSS.hpp"

void setup_GNSS()
{
    String temp = "20250101235412";

    send_AT("AT+CGNSPWR=1");
    send_AT("AT+CGNSMOD=1,0,0,1,0");
}

void turn_off_GNSS()
{
    send_AT("AT+CGNSPWR=0");
}

void get_info_GNSS()
{
    String res = send_AT("AT+CGNSINF");
    std::vector<String> tabRes = Split(res, ',');
    std::vector<String> tabSplit;

    bool runStatus = atoi(tabRes[0].c_str()) == 1;
    bool fixStatus = atoi(tabRes[1].c_str()) == 1;


    struct tm time;
    if (tabRes[2].length() > 13)
    {
        time.tm_year = tabRes[2].substring(0, 4).toInt() - 1900;
        time.tm_mon = tabRes[2].substring(4, 6).toInt() - 1;
        time.tm_mday = tabRes[2].substring(6, 8).toInt();
        time.tm_hour = tabRes[2].substring(8, 10).toInt();
        time.tm_min = tabRes[2].substring(10, 12).toInt();
        time.tm_sec = tabRes[2].substring(12, 14).toInt();
    }
    uint64_t timestamp = mktime(&time);


    tabSplit = Split(tabRes[3], '.');
    floatGps latitude;
    if (tabSplit.size() > 1)
    {
        latitude.integer = atoi(tabSplit[0].c_str());
        latitude.decimal = atoi(tabSplit[1].c_str());
    }


    tabSplit = Split(tabRes[4], '.');
    floatGps longitude;
    if (tabSplit.size() > 1)
    {
        longitude.integer = tabSplit[0].toInt();
        longitude.decimal = tabSplit[1].toInt();
    }

    unsigned int altitude = tabRes[5].toInt();
    unsigned int speed = tabRes[6].toInt();
    unsigned int course = tabRes[7].toInt();


    Serial.println(" ");
    Serial.println("=============== GPS DATA ===============");

    Serial.printf("GNSS run status : %d \n", runStatus);
    Serial.printf("Fix status : %d \n", fixStatus);
    Serial.printf("Unix timestamp : %d \n", timestamp);
    Serial.printf("Latitude : %d.%d \n", latitude.integer, latitude.decimal);
    Serial.printf("Longitude : %d.%d \n", longitude.integer, longitude.decimal);
    Serial.printf("Altitude : %d \n", altitude);
    Serial.printf("Speed over ground : %d \n", speed);
    Serial.printf("Course ove ground : %d \n", course);

    Serial.println("=========================================");
    Serial.println(" ");
}