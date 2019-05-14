#include "Dynamics.hpp"

// create files
ofstream file_energies;
ofstream file_positions;
ofstream file_velocity;

void Dynamics::VelocityVerlet(System &system, int time_steps, int rescale, int record) {
    double dt = 0.001, hdt = 0.5 * dt; // size of time step, half time step
    int n = system.n, d = system.d;
    int i, j, k; // for loop variables
    double dni = 1.0/(d*n);
    double T0 = 0.728;

    // open files
    file_energies.open("energies.txt");
    file_positions.open("positions.txt");
    file_velocity.open("velocity.txt");

    // run dynamics and record data
    cout << "Running dynamics." << endl;
    for (i=0; i<time_steps; i++) {

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
        for (j=0; j<n; j++) {
            for (k=0; k<d; k++) {
                system.atoms.v[j][k] += hdt*system.atoms.f[j][k];
            }
        }

        // temperature
        system.T = 0.0;
        for (j=0; j<n; j++) {
            for (k=0; k<d; k++) {
                system.T += system.atoms.v[j][k]*system.atoms.v[j][k];
            }
        }
        system.T *= 48.0*dni;
        
        //rescale velocity
        if ((i % rescale) == 0) {
            for (j=0; j<n; j++) {
                for (k=0; k<d; k++) {
                    system.atoms.v[j][k] *= sqrt(T0/system.T);
                }
            }
        }

        //calculate kinetic energy
        system.K = 0.0;
        for (j=0; j<n; j++) {
            for (k=0; k<d; k++) {
                system.K += system.atoms.v[j][k] * system.atoms.v[j][k];
            }
        }
        system.K *= 24.0;

        // total energy
        system.E = system.K + system.V;

        // record energies
        file_energies << system.T << "\t" << system.K << "\t" << system.V << "\t" << system.E << endl;

        // record positions & velocity
        if ((i % record) == 0) {
            for (j=0; j<n; j++) {
                for (k=0; k<d; k++) {
                    file_positions << system.atoms.r[j][k] << "\t";
                    file_velocity << system.atoms.v[j][k] << "\t";
                }
                file_positions << endl;
                file_velocity << endl;
            }
        }

    }
    
    // close files
    file_positions.close();
    file_energies.close();
    file_velocity.close();

    cout << "Finished." << endl;
}
