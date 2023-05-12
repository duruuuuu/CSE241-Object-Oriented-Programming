#ifndef _ROBOCOP_H_
#define _ROBOCOP_H_

#include "Humanic.h"

// Class derived from abstract class Humanic
class Robocop : public Humanic
{
    friend class World;

public:
    Robocop();
    Robocop(World *world, int x, int y, std::string name, int num);

    virtual std::string get_type() const override; // Returns the type of the robot
    virtual int get_damage() const override;       // Gets the amount of damage a robot will inflict
    int get_strength() { return strength; }        // Pure virtual functions from Robot being defined
    int get_hitpoints() { return hitpoints; }
    std::string get_name() { return name; }
    void set_hitpoints(int hp) { hitpoints = hp; }

protected:
    std::string name;
};
#endif //_ROBOCOP_H_