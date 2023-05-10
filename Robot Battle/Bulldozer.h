#ifndef _BULLDOZER_H_
#define _BULLDOZER_H_

#include "Robot.h"

class Bulldozer : public Robot
{
    friend class World;

public:
    Bulldozer();
    Bulldozer(World *world, int x, int y);

    // TODO:define virctual functions
    int get_type();
    int get_damage();
};
#endif //_BULLDOZER_H_