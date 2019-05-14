#ifndef Atoms_hpp
#define Atoms_hpp

#include <stdio.h>
#include <iostream>
//#include <mathimf.h>
#include <cmath>

using namespace std;

class Atoms {
protected:
    int n,d; // number of particles, dimension
public:
    Atoms(); // default constructor
    Atoms(const int&n, const int& d); // simple constructor
    Atoms(const Atoms& rhs); // copy constructor
    Atoms & operator=(const Atoms &rhs); // assignment operator
    ~Atoms(); // destruction operator
    // Accessor functions
    inline int N(){return n;};
    inline int D(){return d;};
    friend ostream & operator << (ostream &os, const Atoms& rhs);
    double **r, **v, **f; // position, velocity, force // Very dangerous but needed.
};

#endif /* Atoms_hpp */

