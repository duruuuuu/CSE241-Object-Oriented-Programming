#include "OptimusPrime.h"
#include "Robot.h"
#include "World.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

OptimusPrime::OptimusPrime() // No args constructor iherited from Humanic
    : Humanic{}
{
}

OptimusPrime::OptimusPrime(World *world, int x, int y, std::string name, int num)
    : Humanic{world, x, y}
{
    // Setting points info
    hitpoints = 100;
    strength = 100;

    // Setting the name of the robot
    char chNum = '0' + num;
    this->name = "optimusprime_";
    this->name += chNum;
}

std::string OptimusPrime::get_type() const
{
    return "OPTIMUSPRIME";
}

int OptimusPrime::get_damage() const
{
    srand(time(NULL));
    int d_r = rand() % strength + 1;
    int tacticalNuke = rand() % tacticalNukeChance;
    int strongAttack = rand() % strongAttackChance;

    // Check if the tactical nuke and string attack ill be applied
    if (tacticalNuke <= tacticalNukeChance)
        d_r += tacticalNukePoints;

    if (strongAttack <= strongAttackChance)
        d_r *= strongAttackPoints;

    return d_r;
}
