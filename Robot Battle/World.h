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
    Robot *get_at(int x, int y);
    void set_at(int x, int y, Robot *robot);
    void display();
    void simulate_one_turn();
    void sweep_grid();
    void fight(Robot *R, Robot *S);
    void findIndexes(int *x, int *y, Robot *rob);

private:
    Robot *grid[WORLD_SIZE][WORLD_SIZE];
};

#endif //_WORLD_H_