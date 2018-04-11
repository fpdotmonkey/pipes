#include <stdio.h>

#include "fluid.h"


int main(int argc, char* argv[]) {
    fluid water20;
    fluid ammonia50;

    water20 = initFluid(WATER, 20.0);
    ammonia50 = initFluid(OTHER, 50.0);

    printf("Expected values, FM White Fluid Mechanics Table A1\nName\tmu\t\trho\t\tT\n%s\t%f\t%f\t%f\n%s\t%f\t%f\t%f\n",
           "water", 1.003e-3, 998.0, 20.0,
           "ammonia", -1.0, -1.0, 50.0);

    printf("Calculated values\nName\tmu\t\trho\t\tT\n%s\t%f\t%f\t%f\n%s\t%f\t%f\t%f\n",
           water20.fluidType, water20.mu, water20.rho, water20.T,
           ammonia50.fluidType, ammonia50.mu, ammonia50.rho, ammonia50.T);
    
    return 0;
}
