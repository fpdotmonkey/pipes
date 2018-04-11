#include <stdio.h>

#include "pipe.h"

int main(int argc, char* argv[]) {
    //
    // FM White Fluid Mechanics Example 6.6
    //
    
    fluid_t water = initFluid(WATER, 20);
    pipe_t pipe66 = { 60, 0.15, 0.12e-3, water, NAN, NAN, 9.81 };
    double V66 = 2; // m s^-1
    
    printf("FM White Example 6.6:\nCompute the pressure loss in %f m of horizontal %f m diameter asphaulted cast iron pipe (e = %f m) carrying water with a mean velocity of %f m s^-1\n\n", pipe66.L, pipe66.D, pipe66.e, V66);

    pipe66.Re = pipe66.fluid.rho * V66 * pipe66.D / pipe66.fluid.mu;

    printf("First, the Reynolds number for the pipe must be calculated.\nRe = rho * V * D / mu = %f\n Finally the pressure loss can be calculated with pipePressureLoss() to be dP = %f Pa, compared to the text which has dP = 15960 Pa.\n\n\n", pipe66.Re, pipePressureLoss(pipe66));


    //
    // FM White Fluid Mechanics 6.9
    //
    
    fluid_t oil = { OTHER, 0.019, 950, NAN };
    pipe_t pipe69 = { 100, 0.30, 6.0e-5, oil, NAN, 74556, 9.81 };
    
    printf("FM White Fluid Mechanics Example 6.9:\nOil, with rho = %f kg m^-3 and mu = %f Pa s, flows through a D = %f m L = %f m pipe with dP = %f Pa.  The roughness ratio e/D = %f.  Find the average velocity and flow rate.\n\n", pipe69.fluid.rho, pipe69.fluid.mu, pipe69.D, pipe69.L, pipe69.dP, pipe69.e/pipe69.D);

    double Q69 = pipeFlowRate(pipe69);
    
    printf("The flow rate in the pipe according to pipeFlowRate() is %f m^3 s^-1, compared to 0.342 m^3 s^-1 in the text\n\n\n", Q69);
    

    //
    // FM White Fluid Mechanics 6.10
    //
    
    printf("FM White Fluid Mechancis Example 6.10:\nWork Example 6.9 backward; assume that Q = %f m^3 s^1 and e = %f m are known, but that D is unknown.  Recall L = %f m, rho = %f kg m^-3, mu = %f Pa s, and dP = %f Pa.\n\n", Q69, pipe69.e, pipe69.L, pipe69.fluid.rho, pipe69.fluid.mu, pipe69.dP);

    printf("The diameter of the pipe according to pipeDiameter() is %f m, compared to 0.30 m in the text\n\n\n", pipeDiameter(pipe69, Q69));


    //
    // FM White Fluid Mechanics 6.12
    //
    
    pipe_t asphault = { NAN, 0.15, 0.12e-3, water, NAN, NAN, 9.81 };
    double p = 447.0;  // Pump power delivery
    double V = 2.0;  // Flow velocity

    printf("FM White Fluid Mechanics Example 6.12:\nA pump delivers %f W to water at %f degC, flowing in a %f m diameter asphalted cast iron horizontal pipe (e = %f m) at V = %f m s^-1.  What is the proper pipe length to match these conditions?\n\n", p, asphault.fluid.T, asphault.D, asphault.e, V);

    double Q612 = M_PI / 4 * asphault.D*asphault.D * V;
    asphault.dP = p / Q612;

    printf("First, the pipe flow and pressure loss must be calculated.\nQ = pi/4 * D^2 * V = %f\ndP = p / Q = %f\nFinally, L is calculated to be L = %f, compared to 48.1 m in the text\n\n\n", Q612, asphault.dP, pipeLength(asphault, Q612));


    //
    // Does pipe.h break properly?
    //

    fluid_t NaNfluid = initFluid(OTHER, NAN);
    pipe_t NaNpipe = { NAN, NAN, NAN, NaNfluid, NAN, NAN, NAN };
    double NaNQ = NAN;

    pipePressureLoss(NaNpipe);
    pipeFlowRate(NaNpipe);
    pipeDiameter(NaNpipe, NaNQ);
    pipeLength(NaNpipe, NaNQ);
    
    return 0;
}
