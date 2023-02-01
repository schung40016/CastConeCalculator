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

    bool InLineOfSightArc(std::vector<double> caster, int casterDirection, std::vector<double> target);

    bool InLineOfSightLine(std::vector<double> caster, int casterDirection, std::vector<double> target);

    bool CheckIfWithinArc(double limit, double magnitude);

    double CalcLineConst(std::vector<double> point1, std::vector<double> point2);

    double CalcThreshold();

    double CalcNormDotProduct(EucVector CasterToTarget, EucVector CasterToAim);
};