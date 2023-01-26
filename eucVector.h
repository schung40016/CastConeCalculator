#pragma once

#include <vector>
#include <cmath>

//Represents a Euclidean 2D vector.
class EucVector 
{
private:
    float direction = 0.0f;
    float magnitude = 0.0f;
    std::vector<int> values = {0, 0};

public: 
    EucVector(int x1, int y1);

    // Getters and Setters
    float GetMagnitude(); // Formula: sqrt((y2-y1)^2 + (x2-x1)^2)

    float GetDirection(); // Formula: tan((y2-y1)/(x2-x1))

    std::vector<int> GetValues();
};