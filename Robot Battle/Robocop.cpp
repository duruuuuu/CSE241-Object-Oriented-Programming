#include "Robocop.h"
#include "Robot.h"
#include "World.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

Robocop::Robocop()
    : Humanic{} {}

Robocop::Robocop(World *world, int x, int y, std::string name, int num)
    : Humanic{world, x, y}
{
    hitpoints = 40;
    strength = 30;

    char chNum = num + '0';
    this->name = "robocop_";
    this->name += chNum;
}

std::string Robocop::get_type() const
{
    return "ROBOCOP";
}

int Robocop::get_damage() const
{
    srand(time(NULL));

    int d_r = rand() % strength;
    int tacticalNuke = rand() % tacticalNukeChance;

    if (tacticalNuke <= tacticalNukeChance)
        d_r += tacticalNukePoints;

    return d_r;
}