#ifndef System_hpp
#define System_hpp

#include "Atoms.hpp"
#include "RNG.hpp"

class System{
public:
    System(const int &n, const int &d, const double &rho, const double &T);
    Atoms atoms;
    double rho, T, L, m, epsilon, sigma;
    int n,d, nside;
    double E, V, K;
    void Initialize();
    void PrintConfig();
    void PrintVel();
    void SetCoords(const int &p, const double &rx, const double &ry, const double &rz); // 3D position
    void SetCoords(const int &p, const double &rx, const double &ry); // 2D position
    void SetVel(const int &p, const double &vx, const double &vy, const double &vz); // 3D velocity
    void SetVel(const int &p, const double &vx, const double &vy); // 2D velocity
    double SumVelX(), SumVelY(), SumVelZ();
};

#endif /* System_hpp */
