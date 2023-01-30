#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include "eucVector.h"

class CastConeCalculator
{
private:
    double arc = 0.0f;
    double range = 0.0f;

public:
    CastConeCalculator(double arc, double range);

    bool InLineOfSightArc(std::vector<int> caster, int casterDirection, std::vector<int> target);

    bool InLineOfSightLine(std::vector<int> caster, int casterDirection, std::vector<int> target);

    double CalcThreshold();

    double CalcNormDotProduct(EucVector CasterToTarget, EucVector CasterToAim);
};