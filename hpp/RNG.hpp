#ifndef RNG_hpp
#define RNG_hpp

#include <stdio.h>
#include <mkl.h>
#include "mkl_vsl.h"

class RNG{
public:
    RNG(); // Take the default seed
    RNG(const int &seed);
    double Gaussian(const double &mean, const double &sigma);
    //double Uniform();
    ~RNG();
private:
    VSLStreamStatePtr stream;
};

#endif /* RNG_hpp */
