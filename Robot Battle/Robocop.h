#ifndef _ROBOCOP_H_
#define _ROBOCOP_H_

#include "Humanic.h"

class Robocop : public Humanic
{
    friend class World;

public:
    Robocop();
    Robocop(World *world, int x, int y);

    // TODO:define virctual functions
    int get_type();
    int get_damage();
};
#endif //_ROBOCOP_H_