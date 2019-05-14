#include "System.hpp"

int i,j,k; // for loop variables

// constructor
System::System(const int &n, const int &d, const double &rho, const double &T):n(n),d(d),rho(rho),T(T),m(0),E(0),V(0),K(0){
    atoms = Atoms(n,d);
    Initialize();
}

// Set three-dimensional coordinates
void System::SetCoords(const int &p, const double &rx, const double &ry, const double &rz) {
    atoms.r[p][0] = rx;
    atoms.r[p][1] = ry;
    atoms.r[p][2] = rz;
    return;
}

// Set two-dimensional coordinates
void System::SetCoords(const int &p, const double &rx, const double &ry) {
    atoms.r[p][0] = rx;
    atoms.r[p][1] = ry;
    return;
}

// Set three-dimensional velocity
void System::SetVel(const int &p, const double &vx, const double &vy, const double &vz) {
    atoms.v[p][0] = vx;
    atoms.v[p][1] = vy;
    atoms.v[p][2] = vz;
    return;
}

// Set two-dimensional velocity
void System::SetVel(const int &p, const double &vx, const double &vy) {
    atoms.v[p][0] = vx;
    atoms.v[p][1] = vy;
    return;
}

// sum each velocity component
double System::SumVelX() {
    double VelSumX = 0;
    for (i=0; i<n; i++) {
        VelSumX = VelSumX + atoms.v[i][0];
    }
    return VelSumX;
}
double System::SumVelY() {
    double VelSumY = 0;
    for (i=0; i<n; i++) {
        VelSumY = VelSumY + atoms.v[i][1];
    }
    return VelSumY;
}
double System::SumVelZ() {
    double VelSumZ = 0;
    for (i=0; i<n; i++) {
        VelSumZ = VelSumZ + atoms.v[i][2];
    }
    return VelSumZ;
}

// Initialize system on cubic lattice with gaussian velocity
void System::Initialize(){
    std::cout << "N:" << n << "\t" << "d:" << d << "\t" << "Rho:" << rho << "\t" << "T:" << T << endl;
    
    double box_vol = n / rho; // volume of box containing particles
    if (d==3) {
        L = cbrt(box_vol); // length of one side of box
        nside = cbrt(n); // particles per side of box
    }
    if (d==2) {
        L = sqrt(box_vol);
        nside = sqrt(n);
    }
    double spacing = L / nside; // spacing between particles
    int rcount = 0, vcount = 0; // used in lattice construction & velocity distribution
    epsilon = 1.0; //1.65*exp10(-21); // energy [J]
    sigma = 1.0; // 3.405*exp10(-10); // particle diameter [m]

    // build cubic lattice
    if (d==3) { // three dimensions
        for (i=0; i<nside; i++) {
            for (j=0; j<nside; j++) {
                for (k=0; k<nside; k++) {
                    System::SetCoords(rcount, i*spacing, j*spacing, k*spacing);
                    rcount++;
                }
            }
        }
    }
    else { // two dimensions
        for (i=0; i<nside; i++) {
            for (j=0; j<nside; j++) {
                System::SetCoords(rcount, i*spacing, j*spacing);
                rcount++;
            }
        }
    }
    
    // assign initial random velocity
    double kb = 1.0; // 1.381*exp10(-23); // boltzmann constant
    double Tstar = kb*T/epsilon; // unitless temp
    //double m = 6.634*exp10(-26); // particle mass (Argon)
    double vstar = sqrt(Tstar/48); // unitless velocity
    RNG a; // random number generator
    for (i=0; i<n; i++) {
        if (d == 3) { // 3D
            System::SetVel(vcount, a.Gaussian(0,vstar), a.Gaussian(0,vstar), a.Gaussian(0,vstar));
        }
        else { // 2D
            System::SetVel(vcount, a.Gaussian(0,vstar), a.Gaussian(0,vstar));
        }
        vcount++;
    }
    
    // shift velocities for zero net momentum
    double svx = SumVelX(), svy = SumVelY(), svz = SumVelZ();
    //cout << svx << ", " << svy << ", " << svz << endl;
    if (d==3) { // 3D
        for (i=0; i<n; i++) {
            atoms.v[i][0] -= svx/n;
            atoms.v[i][1] -= svy/n;
            atoms.v[i][2] -= svz/n;
        }
    }
    else if (d==2) { // 2D
        for (i=0; i<n; i++) {
            atoms.v[i][0] -= svx/n;
            atoms.v[i][1] -= svy/n;
        }
    }
    
}

// Print coordinates
void System::PrintConfig() {
    for (i=0; i<n; i++) {
        for (k=0; k<d; k++)
            cout << atoms.r[i][k] << "\t";
        cout << endl;
    }
    return;
}

// Print velocity
void System::PrintVel() {
    for (i=0; i<n; i++) {
        for (k=0; k<d; k++)
            cout << atoms.v[i][k] << "\t";
        cout << endl;
    }
    return;
}
