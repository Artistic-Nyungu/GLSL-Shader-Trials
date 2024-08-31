#pragma once

#include "config.h"

using namespace std;

int genRandInt(int min, int max)
{
    return rand()%(max - min + 1) + min;
}

float genRandFloat(float min, float max)
{
    std::stringstream ss;
    int minUnits, maxUnits, minDecimalPoints, maxDecimalPoints;
    bool isUnits = true;

    ss << min;
    std::string value;
    ss >> value;
    for(char digit: value)
    {
        if(isUnits && digit == '.')
        {
            isUnits = false;
            ss >> minUnits;
            continue;
        }
        
        ss << digit;
    }
    ss >> minDecimalPoints;


    isUnits = true;
    ss << max;
    value;
    ss >> value;
    for(char digit: value)
    {
        if(isUnits && digit == '.')
        {
            isUnits = false;
            ss >> maxUnits;
            continue;
        }
        
        ss << digit;
    }
    ss >> maxDecimalPoints;


    ss << ((minUnits == maxUnits) ? 0 : genRandInt(minUnits, maxUnits)) << '.' << ((minDecimalPoints == maxDecimalPoints) ? 0 : genRandInt(minDecimalPoints, maxDecimalPoints));

    float randF;
    ss >> randF;

    return randF;
}


