#include "eucVector.h"

EucVector::EucVector(double x1, double y1)
{
    this->values[0] = x1;
    this->values[1] = y1;
}

// Getters and Setters
double EucVector::GetMagnitude() 
{
    this->magnitude = sqrt(pow((values[1]), 2) + pow((values[0]), 2));

    return magnitude;
}

double EucVector::GetDirection() 
{
    this->direction = tan((values[1])/(values[0]));

    return this->direction;
}

std::vector<double> EucVector::GetValues()
{
    return this->values;
}
