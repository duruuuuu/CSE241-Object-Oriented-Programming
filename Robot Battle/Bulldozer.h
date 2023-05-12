#ifndef _BULLDOZER_H_
#define _BULLDOZER_H_

#include "Robot.h"

// Class derived publicly from Robot
class Bulldozer : public Robot
{
    friend class World;

public:
    Bulldozer();
    Bulldozer(World *world, int x, int y, std::string name, int num);

    virtual std::string get_type() const override; // Returns the type of the robot
    virtual int get_damage() const override;       // Gets the amount of damage a robot will inflict

    int get_strength() { return strength; }        // pure virtual function
    int get_hitpoints() { return hitpoints; }      // pure virtual Robot function
    std::string get_name() { return name; }        // pure virtual function
    void set_hitpoints(int hp) { hitpoints = hp; } // pure virtual function

protected:
    std::string name;
};
#endif //_BULLDOZER_H_