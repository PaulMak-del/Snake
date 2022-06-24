//
// Created by pawel on 16.06.2022.
//
#ifndef MY_MATH
#define MY_MATH

#include <cmath>
#include "myMath.h"

float getDistance(sf::Vector2f v1, sf::Vector2f v2)
{
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

#endif