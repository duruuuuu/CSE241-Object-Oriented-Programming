#ifndef _HUMANIC_H_
#define _HUMANIC_H_

#include "Robot.h"

// Abstract class derived from Robot class
class Humanic : public Robot
{
    friend class World;

public:
    Humanic();
    Humanic(World *world, int x, int y);

    virtual std::string get_type() const = 0; // Returns the type of the robot
    virtual int get_damage() const = 0;       // Gets the amount of damage a robot will inflict

protected:
    const int tacticalNukeChance = 10;
    const int tacticalNukePoints = 50;
};
#endif //_HUMANIC_H_