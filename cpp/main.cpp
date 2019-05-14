#include "Dynamics.hpp"
#include "Equilibrate.hpp"

int main() {
    
    clock_t ti = clock();

    // initialize system - must be square or cube
    System system(216, 3.0, 0.8442, 0.728); // (N, D, Rho, T):(1000, 3, 0.8442, 0.728)

    // equilibrate system
    Equilibrate::VVEquilibrate(system, 10000); // (system, eq_steps)

    // velocity verlet - runs dynamics and writes data to files
    // (system, time steps, rescale frequency, recording frequency)
    Dynamics::VelocityVerlet(system, 100000, 5000, 100);

    // print out some final values
    std::cout << "Final Temperature: " << system.T << std::endl;
    std::cout << "K, V, E: " << system.K << ", " << system.V << ", " << system.E << std::endl;
    
    clock_t tf = clock();
    double ttot = (tf - ti) / (double)CLOCKS_PER_SEC;
    fprintf(stderr, "Time elapsed: %f s\n", ttot);

    return 0;
}
