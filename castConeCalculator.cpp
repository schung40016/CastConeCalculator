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
    return CheckIfWithinArc((this->threshold + dotProduct), casterToTarget.GetMagnitude(), this->range);
}

// Checks if the target is in the line of sight based on a line.
bool CastConeCalculator::InLineOfSightLine(std::vector<double> caster, double casterDirection, std::vector<double> target)
{
    EucVector casterToTarget(target[0] - caster[0], target[1] - caster[1]);

    EucVector casterToAim((range * GetCosFromDeg(casterDirection)), (range * GetSinFromDeg(casterDirection))); 

    double adjustedArc = this->arc / 2.0;

    double positiveSide = casterDirection + adjustedArc;
    double negativeSide = casterDirection - adjustedArc;

    std::vector<double> point1 = { range * GetCosFromDeg(positiveSide) + caster[0], range * GetSinFromDeg(positiveSide) + caster[1]};
    std::vector<double> point2 = { range * GetCosFromDeg(negativeSide) + caster[0], range * GetSinFromDeg(negativeSide) + caster[1]};

    // Calculate the slope for our two vectors, we can use this to create a linear function. 
    std::vector<double> boundLine = CalcLineForm(point1, point2);
    std::vector<double> casterLine = CalcLineForm(caster, target);
    
    // Find the x and y values for where the two lines intersect.
    std::vector<double> intercepts = CalcIntersectPoint(boundLine, casterLine);

    EucVector casterToBound(intercepts[0] - caster[0], intercepts[1] - caster[1]);

    double dotProduct = CalcNormDotProduct(casterToTarget, casterToAim);

    // Check if our target is within the cone.  
    return CheckIfWithinArc((this->threshold + dotProduct), casterToTarget.GetMagnitude(), casterToBound.GetMagnitude());
}    

bool CastConeCalculator::CheckIfWithinArc(double dotLimit, double magnitude, double rangeLimit)
{
    if (dotLimit >= 1 && rangeLimit >= magnitude)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<double> CastConeCalculator::CalcLineForm(std::vector<double> point1, std::vector<double> point2)
{
    // Swap points depending on which x value is lower. 
    if (point1[0] > point2[1])
    {
        std::vector<double> temp = {};
        temp = point1;
        point1 = point2;
        point2 = temp; 
    }

    // Define a line based on the two points.
    double slope = (point2[1] - point1[1]) / (point2[0] - point1[0]);

    // Calculate the y-intercept.
    double yInt = point1[1] - (point1[0] * slope);

    return {slope, yInt};
}

double CastConeCalculator::CalcNormDotProduct(EucVector casterToTarget, EucVector casterToAim)
{
    //Figure out the degree between out two vectors. Formula: a . b / |a||b|
    double dotProd = (casterToAim.GetValues()[0] * casterToTarget.GetValues()[0] + casterToAim.GetValues()[1] * casterToTarget.GetValues()[1]) 
                    / (casterToTarget.GetMagnitude() * casterToAim.GetMagnitude());

    // Note: if the ot product of 2 normalzied vectors = 1 (they're facing each other).
    return dotProd;
}

std::vector<double> CastConeCalculator::CalcIntersectPoint(std::vector<double> line1, std::vector<double> line2)
{
    double xIntercept =  (line2[1] - line1[1]) / (line1[0] - line2[0]);
    double yIntercept = line2[1] + (line2[0] * xIntercept);

    return {xIntercept, yIntercept};
}

double CastConeCalculator::GetCosFromDeg(double degree)
{
    return cos((degree / 180.0) * M_PI);
}

double CastConeCalculator::GetSinFromDeg(double degree)
{
    return sin((degree / 180.0) * M_PI);
}