//
// fluid.c
//
// Copyright (c) 2018 Fletcher Porter
//

#include "fluid.h"

static double getViscosity(char* fluidType, double T) {
    double mu;
    
    if (! strncmp("water", fluidType, 5)) { // strncmp returns false if they
                                            // are the same
        // According to FM White, Fluid Mechanics, Table A1 
        mu = 1.788e-3 * exp(-1.704 - 1448.5/(T+273.15)
                            + 521927/(T+273.15)/(T+273.15));
    } else {
        mu = NAN;
    }
    
    return mu;
}

static double getDensity(char* fluidType, double T) {
    double rho;
    if (! strncmp("water", fluidType, 5)) {
        // According to FM White, Fluid Mechanics, Table A1 
        rho = 1000 - 0.0178 * pow(fabs(T - 4), 1.7);
    } else {
        rho = NAN;
    }
    return rho;
}

fluid_t initFluid(char* fluidType, double T) {
    fluid_t fluid;
    
    fluid.fluidType = fluidType;
    fluid.mu = getViscosity(fluidType, T);
    fluid.rho = getDensity(fluidType, T);
    fluid.T = T;
    
    return fluid;
}
