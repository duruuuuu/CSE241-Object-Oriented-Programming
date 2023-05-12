#ifndef _WORLD_H_
#define _WORLD_H_

#include "Robot.h"
const int WORLD_SIZE = 10;
class Robot;

class World
{
    friend class Robot;
    friend class Humanic;
    friend class OptimusPrime;
    friend class Robocop;
    friend class Roomba;
    friend class Bulldozer;

public:
    World();
    ~World();
    Robot *get_at(int x, int y);             // Function gets whats in a specific cell
    void set_at(int x, int y, Robot *robot); // Sets a robot to a cell
    void display();                          // prints the world
    void simulate_one_turn();                // goes for one turn
    void sweep_grid();                       // sweeps grid to count how many robots are left

private:
    Robot *grid[WORLD_SIZE][WORLD_SIZE];
};

#endif //_WORLD_H_