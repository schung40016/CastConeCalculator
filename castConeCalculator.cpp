#include "castConeCalculator.h"

CastConeCalculator::CastConeCalculator(double param_arc, double param_range)
    : arc(param_arc), range(param_range)
{
}

bool CastConeCalculator::InLineOfSightArc(std::vector<int> caster, int casterDirection, std::vector<int> target)
{
    // Figure out vector from caster to target.
    EucVector CasterToTarget(target[0] - caster[0], target[1] - caster[1]);

    // Figure out vector from caster to where they're looking at + range. 
    EucVector CasterToAim((range * cos((casterDirection / 180.0) * M_PI)), (range * sin((casterDirection / 180.0) * M_PI))); 

    //Figure out the degree between out two vectors. Formula: a . b / |a||b|
    double degree = (CasterToAim.GetValues()[0] * CasterToTarget.GetValues()[0] + CasterToAim.GetValues()[1] * CasterToTarget.GetValues()[1]) 
                    / (CasterToTarget.GetMagnitude() * CasterToAim.GetMagnitude());

    // Note: if the ot product of 2 normalzied vectors = 1 (they're facing each other).
    double dotProduct = cos(degree);

    // Calculate threshold (degree of our cone, "width").
    double threshold = this->arc / 720.0; 

    // Check if our target is within the cone.  
    if ((threshold + dotProduct) >= 1 && this->range >= CasterToTarget.GetMagnitude())
    {
        return true;
    }
    else
    {
        return false;
    }
}