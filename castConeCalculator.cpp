#include "castConeCalculator.h"

CastConeCalculator::CastConeCalculator(double param_arc, double param_range)
    : arc(param_arc), range(param_range)
{
}

// Checks if the target is in the line of sight on a arc.
bool CastConeCalculator::InLineOfSightArc(std::vector<int> caster, int casterDirection, std::vector<int> target)
{
    // Figure out vector from caster to target.
    EucVector casterToTarget(target[0] - caster[0], target[1] - caster[1]);

    // Figure out vector from caster to where they're looking at + range. 
    EucVector casterToAim((range * cos((casterDirection / 180.0) * M_PI)), (range * sin((casterDirection / 180.0) * M_PI))); 

    double dotProduct = CalcNormDotProduct(casterToTarget, casterToAim);

    double threshold = CalcThreshold(); 

    // Check if our target is within the cone.  
    if ((threshold + dotProduct) >= 1 && this->range >= casterToTarget.GetMagnitude())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Checks if the target is in the line of sight based on a line.
bool CastConeCalculator::InLineOfSightLine(std::vector<int> caster, int casterDirection, std::vector<int> target)
{
    EucVector casterToTarget(target[0] - caster[0], target[1] - caster[1]);

    EucVector casterToAim((range * cos((casterDirection / 180.0) * M_PI)), (range * sin((casterDirection / 180.0) * M_PI))); 

    //TO-DO:
    // Define the two points that make the base of the cone.
    // Define a line based on the two points.
    // Check whether the target is under the line using out made function.
}

double CastConeCalculator::CalcThreshold()
{
    return this->arc / 720.0;
}

double CastConeCalculator::CalcNormDotProduct(EucVector casterToTarget, EucVector casterToAim)
{
    //Figure out the degree between out two vectors. Formula: a . b / |a||b|
    double degree = (casterToAim.GetValues()[0] * casterToTarget.GetValues()[0] + casterToAim.GetValues()[1] * casterToTarget.GetValues()[1]) 
                    / (casterToTarget.GetMagnitude() * casterToAim.GetMagnitude());

    // Note: if the ot product of 2 normalzied vectors = 1 (they're facing each other).
    return cos(degree);
}

