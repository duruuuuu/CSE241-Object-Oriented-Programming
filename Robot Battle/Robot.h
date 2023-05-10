#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "World.h"

class Robot
{
    friend class World;

public:
    Robot();
    Robot(World *world, int x, int y);
    ~Robot();

    virtual int get_type() = 0;   // Returns the type of the robot
    virtual int get_damage() = 0; // Gets the amount of damage a robot will inflict
};

#endif //_ROBOT_H_