#ifndef _HUMANIC_H_
#define _HUMANIC_H_

#include "Robot.h"

class Humanic : public Robot
{
    friend class World;

public:
    Humanic();
    Humanic(World *world, int x, int y);

    // TODO:define virtual functions
    int get_type();
    int get_damage();
};
#endif //_HUMANIC_H_