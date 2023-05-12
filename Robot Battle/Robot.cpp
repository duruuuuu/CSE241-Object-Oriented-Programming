#include "Robot.h"
#include "World.h"
class World;
Robot::Robot()
    : world(NULL), fought(false), x(0), y(0), alive(true) {}

Robot::Robot(World *world, int x, int y)
    : fought(false), alive(true)
{
    this->world = world;
    this->x = x;
    this->y = y;

    world->set_at(x, y, this);
}

Robot::~Robot()
{
    /// Intentionally left empty
}