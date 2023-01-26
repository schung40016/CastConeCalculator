#pragma once

#include "castConeCalculator.h"

bool CastConeCalculator::InLineOfSight(std::vector<int> caster, float casterDirection, std::vector<int> target)
{
    // Figure out vector from caster to target.
    EucVector CasterToTarget(target[0] - caster[0], target[1] - caster[1]);

    // Figure out vector from caster to where they're looking at + range. 
    EucVector CasterToAim((range * cos(casterDirection)), (range * sin(casterDirection))); 

    //Figure out the degree between out two vectors. Formula: a . b / |a||b|
    float degree = (CasterToAim.GetValues()[0] * CasterToTarget.GetValues()[0] + CasterToAim.GetValues()[1] * CasterToTarget.GetValues()[1]) 
                    / (CasterToTarget.GetMagnitude() * CasterToAim.GetMagnitude());

    float dotProduct = cos(degree);
}