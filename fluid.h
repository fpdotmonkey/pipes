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

typedef enum {
    WATER,
    OTHER
} fluidType;

typedef struct {
    fluidType fluid;
    double mu; // Dynamic viscosity [Pa s]
    double rho; // Density [kg m^-3]
    double T; // Temperature [degC]
} fluid_t;

// Returns a fluid at temperature T, uses properties of fluidType.  If
// fluid type is not known to this program, mu and rho will be set to
// NaN.
//
// Currently available fluidType [temperature range]:
//   WATER [0-100degC]
//   OTHER [-] (Note: results in mu = rho = NaN
fluid_t initFluid(fluidType fluid, double T);

#endif
