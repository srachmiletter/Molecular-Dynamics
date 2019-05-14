#include "RNG.hpp"

RNG::RNG() {
    vslNewStream(&stream, VSL_BRNG_MT19937, 777);
}

RNG::RNG(const int &seed) {
    vslNewStream(&stream, VSL_BRNG_MT19937, seed);
}

double RNG::Gaussian(const double &mean, const double &sigma) {
    double x[1]; //*x = 0;
    vdRngGaussian(VSL_RNG_METHOD_GAUSSIANMV_ICDF, stream, 1, x, mean, sigma);
    return x[0]; //*x;
}

RNG::~RNG(){ vslDeleteStream(&stream); }
