#ifndef _OPTIMUS_PRIME_H_
#define _OPTIMUS_PRIME_H_

#include "Humanic.h"

class OptimusPrime : public Humanic
{
    friend class World;

public:
    OptimusPrime();
    OptimusPrime(World *world, int x, int y, std::string name, int num);

    virtual std::string get_type() const override; // Returns the type of the robot
    virtual int get_damage() const override;       // Gets the amount of damage a robot will inflict
    int get_strength() { return strength; }        // Pure virtual functtions being defined
    int get_hitpoints() { return hitpoints; }
    std::string get_name() { return name; }
    void set_hitpoints(int hp) { hitpoints = hp; }

protected:
    std::string name;
    const int strongAttackChance = 15;
    const int strongAttackPoints = 2;
};
#endif //_OPTIMUS_PRIME_H_