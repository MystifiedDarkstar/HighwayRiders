#pragma once

#ifndef _MATHFUNCTIONS_H
#define _MATHFUNCTIONS_H

#include <random>
#include <iostream>
#include <algorithm>

namespace
{
    //Properties for the RNG
    std::random_device device;
    std::mt19937 randomGenerator(device());

    /// <summary>
    /// Returns a random integer between {min} and {max}
    /// </summary>
    /// <param name="min">The minimum value</param>
    /// <param name="max">The maximum value</param>
    /// <returns>A random integer</returns>
    int random(int min, int max)
    {
        //We have to do this because if the ranges aren't
        //ordered then C++ will throw an error
        int trueMin = std::min(min, max);
        int trueMax = std::max(max, min);

        //Build a uniform distribution
        std::uniform_int_distribution<int> udist(trueMin, trueMax);

        //Sample the distribution using the generator
        return udist(randomGenerator);
    }
    #define arraySize(x) sizeof(x)/sizeof(x[0])

    std::string ConvertTimeToString(float levelTime)
    {
        int temp = std::floor(levelTime);
        int minutesTenth, minutesUnit, secondsTenth, secondsUnit;

        int tempMins = temp / 60;
        minutesTenth = tempMins / 10;
        tempMins -= minutesTenth * 10;
        minutesUnit = tempMins;

        temp -= tempMins * 60;

        int tempSecs = temp;
        secondsTenth = temp / 10;
        tempSecs -= secondsTenth * 10;
        secondsUnit = tempSecs;

        std::string outputTime = std::to_string(minutesTenth) + " " + std::to_string(minutesUnit) + " : " + std::to_string(secondsTenth) + " " + std::to_string(secondsUnit);
        return outputTime;
    }
}

#endif 