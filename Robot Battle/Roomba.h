#ifndef _ROOMBA_H_
#define _ROOMBA_H_

#include "Robot.h"

class Roomba : public Robot
{
    friend class World;

public:
    Roomba();
    Roomba(World *world, int x, int y);

    // TODO:define virctual functions
    int get_type();
    int get_damage();
};
#endif //_ROOMBA_H_