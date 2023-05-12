#include "Humanic.h"
#include "Robot.h"
#include "World.h"
#include <iostream>

Humanic::Humanic()
    : Robot{} {}

Humanic::Humanic(World *world, int x, int y)
    : Robot{world, x, y} {}
