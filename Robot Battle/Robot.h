#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <iostream>
#include <string>
#include "World.h"
class World;
class Robot
{
    friend class World;

public:
    Robot();
    Robot(World *world, int x, int y);
    virtual ~Robot();

    virtual std::string get_type() const = 0; // Returns the type of the robot
    virtual int get_damage() const = 0;       // Gets the amount of damage a robot will inflict

    virtual int get_strength() = 0;
    virtual int get_hitpoints() = 0;
    virtual std::string get_name() = 0;
    virtual void move() = 0; // returns true if a robot is found, false if not
    virtual void fight(Robot *S) = 0;
    virtual void set_hitpoints(int hp) = 0;
    bool alive;

protected:
    int x, y;
    bool fought;
    int strength;
    int hitpoints;
    std::string name;
    World *world;
};

#endif //_ROBOT_H_