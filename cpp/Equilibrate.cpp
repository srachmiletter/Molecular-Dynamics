#include "Equilibrate.hpp"

// Equilibrate system via verlocity verlet integration
void Equilibrate::VVEquilibrate(System &system, int eq_steps) {
    double dt = 0.001, hdt = 0.5 * dt; // size of time step, half time step
    int n = system.n, d = system.d; // n particles, d dimensions
    double dni = 1.0/(d*n);
    int i, j, k; // for loop dummy variables

    double T0 = system.T;

    cout << "Equilibrating system." << endl;
    for (i=0; i<eq_steps; i++) {

        // calculate positions at time t+dt
        for (j=0; j<n; j++) {
            for (k=0; k<d; k++) {
                system.atoms.r[j][k] += dt*system.atoms.v[j][k];
                system.atoms.r[j][k] += hdt*dt*system.atoms.f[j][k];
            }
        }

        //calculate the velocities at point t + dt using the forces at time t:
        for (j=0; j<n; j++) {
            for (k=0; k<d; k++) {
                system.atoms.v[j][k] += hdt*system.atoms.f[j][k];
            }
        }

        //calculate force a(t+dt)
        Force::LJ(system);

        //calculate velocity v(t+dt)
        system.K = 0.0; // reset kinetic energy
        for (j=0; j<n; j++) {
            for (k=0; k<d; k++) {
                system.atoms.v[j][k] += hdt*system.atoms.f[j][k];
            }
        }

        // calculate temperature & rescale velocity
        if ((i % 50) == 0) {
            system.T = 0.0;
            for (j=0; j<n; j++) {
                for (k=0; k<d; k++) {
                    system.T += system.atoms.v[j][k] * system.atoms.v[j][k];
                }
            }
            system.T *= 48.0 * dni;
            
            for (j=0; j<n; j++) {
                for (k=0; k<d; k++) {
                    system.atoms.v[j][k] *= sqrt(T0/system.T);
                }
            }
            
        }

    }

}
