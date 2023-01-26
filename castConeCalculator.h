#pragma once

#include <vector>
#include "eucVector.h"

class CastConeCalculator
{
private:
    float arc = 0.0f;
    float range = 0.0f;

    bool InLineOfSight(std::vector<int> caster, float casterDirection, std::vector<int> target);
};