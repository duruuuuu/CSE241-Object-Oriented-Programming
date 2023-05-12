#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <iostream>
#include <string>
#include "World.h"

// Forward declaring class World
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

    virtual int get_strength() = 0; // Pure virtual functions will be define in children classes
    virtual int get_hitpoints() = 0;
    virtual std::string get_name() = 0;
    virtual void set_hitpoints(int hp) = 0;

    void move();                    // Function to move the robot
    virtual Robot *fight(Robot *S); // Function for fighting robots

protected:
    int x, y;    // Coordinates of the robot in the world
    bool fought; // Flag to check if the robot has fought (moved) in a dignle turn yet or not
    int strength;
    int hitpoints;
    std::string name;
    World *world;
};

#endif //_ROBOT_H_