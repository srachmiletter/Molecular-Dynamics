#ifndef Dynamics_hpp
#define Dynamics_hpp

#include "Force.hpp"
#include <fstream>

namespace Dynamics {
    void VelocityVerlet(System &system, int time_steps, int rescale, int record);
}

#endif /* Dynamics_hpp */
