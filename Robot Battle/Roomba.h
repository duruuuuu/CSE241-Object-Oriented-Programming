#ifndef _ROOMBA_H_
#define _ROOMBA_H_

#include "Robot.h"

class Roomba : public Robot
{
    friend class World;

public:
    Roomba();
    Roomba(World *world, int x, int y, std::string name, int num);

    virtual std::string get_type() const override; // Returns the type of the robot
    virtual int get_damage() const override;       // Gets the amount of damage a robot will inflict
    int get_strength() { return strength; }        // Defining pure virtual functions
    int get_hitpoints() { return hitpoints; }
    std::string get_name() { return name; }
    void set_hitpoints(int hp) { hitpoints = hp; }
    Robot *fight(Robot *S) override; // Overriding fight fxn to allow for double attack

protected:
    std::string name;
};
#endif //_ROOMBA_H_