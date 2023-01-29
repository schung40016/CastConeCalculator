#pragma once

#include <vector>
#include <cmath>

//Represents a Euclidean 2D vector.
class EucVector 
{
private:
    double direction = 0.0f;
    double magnitude = 0.0f;
    std::vector<double> values = {0, 0};

public: 
    EucVector(double x1, double y1);

    // Getters and Setters
    double GetMagnitude(); // Formula: sqrt((y2-y1)^2 + (x2-x1)^2)

    double GetDirection(); // Formula: tan((y2-y1)/(x2-x1))

    std::vector<double> GetValues();
};