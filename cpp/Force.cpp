#include "Force.hpp"

void Force::LJ(System &system) {
    int i,j,k;
    int n = system.n, d = system.d;
    double L = system.L, Linv = 1/L;
    double rij[d], d2, Fij; //, rc = 2.5, rc2 = rc*rc;
    double d2inv, d6inv;//, d8inv, d12inv, d14inv;
    double Vc = -0.0163;
    
    // set potential energy to zero
    system.V = 0.0;
    
    // set force to zero
    for(i=0; i<n; i++) {
        for(k=0; k<d; k++) {
            system.atoms.f[i][k] = 0.0; } }
    
    for (i=0; i<n; i++) {
        for (j=i+1; j<n; j++) {
            d2 = 0.0; //squared distance between particles
            for(k=0; k<d; k++) {
                rij[k] = system.atoms.r[i][k] - system.atoms.r[j][k];
                //rij[k] -= L*round(rij[k]*Linv);
                rij[k] -= L*(rij[k] <= 0 ? int(rij[k]*Linv - 0.5) : int(rij[k]*Linv + 0.5));
                //rij[k] -= L * (static_cast<int>(rij[k]*Linv + 1000.5) - 1000); // pbc
                d2 += rij[k]*rij[k];
            }
            
            // distance factors
            d2inv = 1.0 / d2;
            d6inv = d2inv * d2inv * d2inv;
    
            // Calculate force on each pair
            Fij = d2inv * d6inv * (d6inv - 0.5);
            if (d2 <= 6.25) { // rc*rc = 6.25
                for (k=0; k<d; k++) {
                    system.atoms.f[i][k] += Fij*rij[k];
                    system.atoms.f[j][k] -= Fij*rij[k];
                }
                // update potential energy
                system.V += 4.0 * d6inv * (d6inv - 1.0) - Vc;
            }
        }
    }
}
