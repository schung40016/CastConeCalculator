#include <iostream>
#include "eucVector.h"
#include "castConeCalculator.h"

int main()
{
    std::vector<double> casterPos = {0, 0};
    std::vector<double> targetPos = {5, 5};
    double directionAngle = 0.0;
    double arc = 0.0;
    double range = 10.0;

    std::cout << "Enter the direction angle, arc, and the range of the cone." << std::endl;
    std::cin >> directionAngle;
    std::cin >> arc;
    std::cin >> range;

    CastConeCalculator castConeCalculator(arc, range);

    std::cout << castConeCalculator.InLineOfSightArc(casterPos, directionAngle, targetPos);

    return 0;
};