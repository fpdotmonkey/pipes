//
// pipe.h
//
// Copyright (c) 2018 Fletcher Porter
//

// This class calculates the flow and pressure drop through a
// turbulent pipe using the explicit form of the Colebrook formula
// developed by Haaland, given in (6.49) in FM White, Fluid Mechanics
// 8th Edition.
//
// When defining a pipe_t, unknown member quantities should be defined
// to be NaN.  However, if a member quantity below needs a quantity
// (indicated in the accompanying comment) that has been defined by
// the user to be NaN or negative, the function will return NaN and
// issue a warning note in stdout.
//
// The results of these functions are valid for Re > 2.0e3

#ifndef PIPE_H
#define PIPE_H

#include <math.h>
#include <stdio.h>

#include "fluid.h"

typedef struct {
    double L; // Pipe length [m]
    double D; // Pipe diameter [m]
    double e; // Pipe roughness [m]
    fluid fluid; // Viscosity, density, and temperature of the fluid
    double Re; // Reynolds number [-]
    double dP; // Pressure drop in the pipe [Pa]
    double g; // Gravitational acceleration [m s^-2]
} pipe_t;

// Given pipe.Re, pipe.e, pipe.D, pipe.L, pipe.fluid.mu, and
// pipe.fluid.rho calculates pipe.dP
double pipePressureLoss(pipe_t pipe);

// Given pipe.e, pipe.D, pipe.L, pipe.fluid.mu, and pipe.fluid.rho
// calculates flow rate Q [m^3 s^-1]
double pipeFlowRate(pipe_t pipe);

// Given Q, pipe.e, pipe.L, pipe.fluid.mu, and pipe.fluid.rho
// calculates pipe.D
double pipeDiameter(pipe_t pipe, double Q);

// Given Q, pipe.e, pipe.D, pipe.fluid.mu, and pipe.fluid.rho calculates L
double pipeLength(pipe_t pipe, double Q);


#endif
