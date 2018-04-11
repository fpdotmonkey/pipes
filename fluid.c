//
// fluid.c
//
// Copyright (c) 2018 Fletcher Porter
//

#include "fluid.h"

static double getViscosity(fluidType fluid, double T) {
    double mu;
    
    switch (fluid) {
    case WATER:
        // According to FM White, Fluid Mechanics, Table A1 
        mu = 1.788e-3 * exp(-1.704 - 1448.5/(T+273.15)
                            + 521927/(T+273.15)/(T+273.15));
        break;
        
    default:
        mu = NAN;
        break;
    }
    
    return mu;
}

static double getDensity(fluidType fluid, double T) {
    double rho;
    
    switch (fluid) {
    case WATER:
        // According to FM White, Fluid Mechanics, Table A1 
        rho = 1000 - 0.0178 * pow(fabs(T - 4), 1.7);
        break;

    default:
        rho = NAN;
        break;
    }
    
    return rho;
}

// Returns a fluid at temperature T, uses properties based on fluidType.  If
// fluid type is not known to this program, mu and rho will be set to
// NaN.
//
// Currently available fluidType [temperature range]:
//   WATER [0-100degC]
//   OTHER [-] (Note: results in mu = rho = NaN)
fluid_t initFluid(fluidType fluid, double T) {
    fluid_t out;
    
    out.fluid = fluid;
    out.mu = getViscosity(fluid, T);
    out.rho = getDensity(fluid, T);
    out.T = T;
    
    return out;
}
