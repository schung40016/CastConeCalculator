#include "castConeCalculator.h"

CastConeCalculator::CastConeCalculator(double param_arc, double param_range)
    : arc(param_arc), range(param_range)
{
}

// Checks if the target is in the line of sight on a arc.
bool CastConeCalculator::InLineOfSightArc(std::vector<double> caster, int casterDirection, std::vector<double> target)
{
    // Figure out vector from caster to target.
    EucVector casterToTarget(target[0] - caster[0], target[1] - caster[1]);

    // Figure out vector from caster to where they're looking at + range. 
    EucVector casterToAim((range * cos((casterDirection / 180.0) * M_PI)), (range * sin((casterDirection / 180.0) * M_PI))); 

    double dotProduct = CalcNormDotProduct(casterToTarget, casterToAim);

    double threshold = CalcThreshold(); 

    // Check if our target is within the cone.  
    return CheckIfWithinArc((threshold + dotProduct), casterToTarget.GetMagnitude());
}

// Checks if the target is in the line of sight based on a line.
bool CastConeCalculator::InLineOfSightLine(std::vector<double> caster, int casterDirection, std::vector<double> target)
{
    EucVector casterToTarget(target[0] - caster[0], target[1] - caster[1]);

    EucVector casterToAim((range * cos((casterDirection / 180.0) * M_PI)), (range * sin((casterDirection / 180.0) * M_PI))); 

    //TO-DO:
    // Define the two points that make the base of the cone.
    double adjustedArc = this->arc / 2.0;
    std::vector<double> point1 = { range * cos(((casterDirection + adjustedArc) / 180.0) * M_PI), range * sin(((casterDirection + adjustedArc) / 180.0) * M_PI)};
    std::vector<double> point2 = { range * cos(((casterDirection - adjustedArc) / 180.0) * M_PI), range * sin(((casterDirection - adjustedArc) / 180.0) * M_PI)};

    // Calculate the slope for our two vectors, we can use this to create a linear function. 
    double boundLine = CalcLineConst(point1, point2);
    double casterLine = CalcLineConst(caster, target);
    
    // Find where the cast line intersects with the bound line.
    double xIntercept = sqrt(casterLine * (1.0 / casterLine));
    double yIntercept = casterLine * xIntercept;

    EucVector casterToBound(xIntercept - caster[0], yIntercept - caster[1]);

    double dotProduct = CalcNormDotProduct(casterToTarget, casterToAim);

    double threshold = CalcThreshold();
    
    // Check if our target is within the cone.  
    return CheckIfWithinArc((threshold + dotProduct), casterToBound.GetMagnitude());
}    

bool CastConeCalculator::CheckIfWithinArc(double limit, double magnitude)
{
    if (limit >= 1 && this->range >= magnitude)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double CastConeCalculator::CalcLineConst(std::vector<double> point1, std::vector<double> point2)
{
    if (point1[0] > point2[1])
    {
        std::vector<double> temp = {};
        temp = point1;
        point1 = point2;
        point2 = temp; 
    }

    // Define a line based on the two points.
    return (point2[1] - point1[1]) / (point2[0] - point1[1]);
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

