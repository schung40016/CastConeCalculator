#include "castConeCalculator.h"

CastConeCalculator::CastConeCalculator(double param_arc, double param_range)
    : arc(param_arc), range(param_range), threshold(this->arc / 720.0)
{
}

// Checks if the target is in the line of sight on a arc.
bool CastConeCalculator::InLineOfSightArc(std::vector<double> caster, double casterDirection, std::vector<double> target)
{
    // Figure out vector from caster to target.
    EucVector casterToTarget(target[0] - caster[0], target[1] - caster[1]);

    // Figure out vector from caster to where they're looking at + range. // CORRECT
    EucVector casterToAim(range * GetCosFromDeg(casterDirection), (range * GetSinFromDeg(casterDirection))); 

    double dotProduct = CalcNormDotProduct(casterToTarget, casterToAim);

    // Check if our target is within the cone.  
    return CheckIfWithinArc((this->threshold + dotProduct), casterToTarget.GetMagnitude());
}

// Checks if the target is in the line of sight based on a line.
bool CastConeCalculator::InLineOfSightLine(std::vector<double> caster, double casterDirection, std::vector<double> target)
{
    EucVector casterToTarget(target[0] - caster[0], target[1] - caster[1]);

    EucVector casterToAim((range * GetCosFromDeg(casterDirection)), (range * GetSinFromDeg(casterDirection))); 

    //TO-DO:
    // Define the two points that make the base of the cone.
    double adjustedArc = this->arc / 2.0;
    std::vector<double> point1 = { range * GetCosFromDeg(casterDirection + adjustedArc), range * GetSinFromDeg(casterDirection + adjustedArc)};
    std::vector<double> point2 = { range * GetCosFromDeg(casterDirection - adjustedArc), range * GetSinFromDeg(casterDirection - adjustedArc)};

    // Calculate the slope for our two vectors, we can use this to create a linear function. 
    double boundLine = CalcLineConst(point1, point2);
    double casterLine = CalcLineConst(caster, target);
    
    // Find where the cast line intersects with the bound line.
    double xIntercept = sqrt(casterLine * (1.0 / casterLine));
    double yIntercept = casterLine * xIntercept;

    EucVector casterToBound(xIntercept - caster[0], yIntercept - caster[1]);

    double dotProduct = CalcNormDotProduct(casterToTarget, casterToAim);

    // Check if our target is within the cone.  
    return CheckIfWithinArc((this->threshold + dotProduct), casterToBound.GetMagnitude());
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

double CastConeCalculator::CalcNormDotProduct(EucVector casterToTarget, EucVector casterToAim)
{
    //Figure out the degree between out two vectors. Formula: a . b / |a||b|
    double degree = (casterToAim.GetValues()[0] * casterToTarget.GetValues()[0] + casterToAim.GetValues()[1] * casterToTarget.GetValues()[1]) 
                    / (casterToTarget.GetMagnitude() * casterToAim.GetMagnitude());

    // Note: if the ot product of 2 normalzied vectors = 1 (they're facing each other).
    return GetCosFromDeg(degree);
}

double CastConeCalculator::GetCosFromDeg(double degree)
{
    return cos((degree / 180.0) * M_PI);
}

double CastConeCalculator::GetSinFromDeg(double degree)
{
    return sin((degree / 180.0) * M_PI);
}