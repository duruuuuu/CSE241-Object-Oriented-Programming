#ifndef _OPTIMUS_PRIME_H_
#define _OPTIMUS_PRIME_H_

#include "Humanic.h"

class OptimusPrime : public Humanic
{
    friend class World;

public:
    OptimusPrime();
    OptimusPrime(World *world, int x, int y);

    // TODO:define virctual functions
    int get_type();
    int get_damage();
};
#endif //_OPTIMUS_PRIME_H_