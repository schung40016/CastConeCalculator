#pragma once

#include "eucVector.h"

EucVector::EucVector(int x1, int y1)
{
    this->values[0] = x1;
    this->values[1] = y1;

}

// Getters and Setters
float EucVector::GetMagnitude() 
{
    this->magnitude = sqrt(pow((values[1]), 2) + pow((values[0]),2));

    return magnitude;
}

float EucVector::GetDirection() 
{
    this->direction = tan((values[1])/(values[0]));
}

std::vector<int> EucVector::GetValues()
{
    return this->values;
}
