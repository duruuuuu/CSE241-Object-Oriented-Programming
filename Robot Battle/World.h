#ifndef _WORLD_H_
#define _WORLD_H_

#include "Robot.h"

class World
{
public:
    World();
    ~World();
    // Robot *getAt(int x, int y);
    void set_at(int x, int y, Robot *robot);
    void display();
    void simulate_one_step();
};

#endif //_WORLD_H_