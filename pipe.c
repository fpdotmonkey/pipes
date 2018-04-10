//
// pipe.c
//
// Copyright (c) 2018 Fletcher Porter
//

#include "pipe.h"

#define MIN_RE 2.0e3

// Calculates the friction factor of a pipe
static double frictionFactor(double Re, double eD) {
    double f;
    
    if (Re > MIN_RE) {
        // Friction factor calculated with (6.49) in FM White Fluid Mechanics
        f = 1.63638/pow(log(0.23404 * pow(eD, 1.11) + 6.9/Re), 2);
    } else {
        // (6.13) in FM White Fluid Mechanics
        f = 64 / Re;
    }
    return f;
}

// Given pipe.Re, pipe.e, pipe.D, pipe.L, pipe.fluid.mu, and
// pipe.fluid.rho calculates pipe.dP
double pipePressureLoss(pipe_t pipe) {

    if (pipe.Re > 0 && pipe.e > 0 && pipe.D > 0 && pipe.L > 0
        && pipe.fluid.mu > 0 && pipe.fluid.rho > 0) {
        double f = frictionFactor(pipe.Re, pipe.e / pipe.D);
        
        double dP = f * pipe.L * pipe.Re*pipe.Re * pipe.fluid.mu*pipe.fluid.mu
            / (2 * pow(pipe.D, 3) * pipe.fluid.rho);

        return dP;
    } else {
        printf("pipePressureLoss() WARNING pipe.Re, pipe.e, pipe.D, pipe.L, pipe.fluid.mu, and pipe.fluid.rho must all be defined to be positive doubles, otherwise output will be NaN\n");
        
        return NAN;
    }
}

// Given pipe.e, pipe.D, pipe.L, pipe.fluid.mu, and pipe.fluid.rho
// calculates flow rate Q [m^3 s^-1]
double pipeFlowRate(pipe_t pipe) {
    if (pipe.e > 0 && pipe.D > 0 && pipe.L > 0
        && pipe.fluid.mu > 0 && pipe.fluid.rho > 0) {
        const double convergenceLimit = 0.0001; // Arbitrary difference between
                                                // one friction factor and the
                                                // next that is iterated

        double Re = 4.0e3; // Initially fully rough flow is assumed,
                           // corresponding to this Reynolds number

        double f = 0;
        double fold = INFINITY; // Selected so convergence doesn't happen on the
                                // first iteration by chance
    
        while (fabs(f - fold) > convergenceLimit) { // This is known to converge
                                                    // quickly (~5 iterations)
            fold = f;
            f = frictionFactor(Re, pipe.e / pipe.D);
            Re = pow(2 * pipe.dP * pow(pipe.D, 3) * pipe.fluid.rho
                     / (f * pipe.L * pow(pipe.fluid.mu, 2)), 0.5);
        }

        // Flow rate [m^3 s^-1]
        double Q = Re * M_PI/4 * pipe.D * pipe.fluid.mu / pipe.fluid.rho;

        return Q;
    } else {
        printf("pipeFlowRate() WARNING pipe.e, pipe.D, pipe.L, pipe.fluid.mu, and pipe.fluid.rho must all be defined to be positive doubles, otherwise output will be NaN\n");
                
        return NAN;
    }
}

// Given Q, pipe.e, pipe.L, pipe.fluid.mu, and pipe.fluid.rho
// calculates pipe.D
double pipeDiameter(pipe_t pipe, double Q) {
    if (Q > 0 && pipe.e > 0 && pipe.L > 0
        && pipe.fluid.mu > 0 && pipe.fluid.rho > 0) {
        const double convergenceLimit = 0.0001; // Arbitrary difference between
                                                // one friction factor and the
                                                // next that is iterated
    
        double f = 0.03; // An arbitrary initial guess for f
        double fnew = INFINITY; // Selected so convergence doesn't happen on the
                                // first iteration by chance
        double D;
        
        while (fabs(f - fnew) > convergenceLimit) { // This is known to converge
                                                    // quickly (~5 iterations)
            fnew = f;
            D = pow(8 * f * pipe.L * Q*Q * pipe.fluid.rho
                    / (M_PI*M_PI * pipe.dP), 0.2);
            double Re = 4 * Q * pipe.fluid.rho / (M_PI * pipe.fluid.mu * D);
            f = frictionFactor(Re, pipe.e / D);
        }

        return D;
    } else {
        printf("pipeDiameter() WARNING Q, pipe.e, pipe.L, pipe.fluid.mu, and pipe.fluid.rho must all be defined to be positive doubles, otherwise output will be NaN\n");

        return NAN;
    }
}

// Given Q, pipe.e, pipe.D, pipe.fluid.mu, and pipe.fluid.rho calculates L
double pipeLength(pipe_t pipe, double Q) {
    if (Q > 0 && pipe.e > 0 && pipe.D
        && pipe.fluid.mu > 0 && pipe.fluid.rho > 0) {
        double Re = 4 * Q * pipe.fluid.rho / (M_PI * pipe.fluid.mu * pipe.D);
        double f = frictionFactor(Re, pipe.e / pipe.D);
        
        double L = 2 * pipe.dP * pow(pipe.D, 3.0) * pipe.fluid.rho
            / (f * Re*Re * pipe.fluid.mu*pipe.fluid.mu);
        
        return L;
    } else {
        printf("pipeLength() WARNING Q, pipe.e, pipe.D, pipe.fluid.mu, and pipe.fluid.rho must all be defined to be positive doubles, otherwise output will be NaN\n");
        
        return NAN;
    }
}
