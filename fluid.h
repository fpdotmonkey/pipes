//
// fluid.h
//
// Copyright (c) 2018 Fletcher Porter
//

// This gives the viscosity and density of a fluid at a particular
// temperature

#ifndef FLUID_H
#define FLUID_H

#include <string.h>
#include <math.h>

typedef struct {
    char* fluidType;
    double mu; // Dynamic viscosity [Pa s]
    double rho; // Density [kg m^-3]
    double T; // Temperature [degC]
} fluid;

// Returns a fluid at temperature T, uses properties of fluidType.  If
// fluid type is not known to this program, mu and rho will be set to
// -1.
//
// Currently available fluidType [temperature range]:
//   water [0-100degC]
fluid initFluid(char* fluidType, double T);

#endif
