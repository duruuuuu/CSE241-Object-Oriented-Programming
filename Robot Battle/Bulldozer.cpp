#include "Bulldozer.h"
#include "Robot.h"
#include "World.h"
#include <time.h>
#include <cstdlib>
#include <cstring>

using namespace std;

// Using no-args robot constructor (inherited)
Bulldozer::Bulldozer()
    : Robot{} {}

Bulldozer::Bulldozer(World *world, int x, int y, std::string name, int num)
    : Robot{world, x, y} // Robot Constructor (inherited)
{
    // Assigning points
    hitpoints = 200;
    strength = 50;

    // Assigning name
    char chNum = num + '0';
    this->name = "bulldozer_";
    this->name += chNum;
}

std::string Bulldozer::get_type() const
{
    return "BULLDOZER";
}

int Bulldozer::get_damage() const
{
    srand(time(NULL));

    int d_r = (rand() % strength) + 1;

    return d_r;
}
