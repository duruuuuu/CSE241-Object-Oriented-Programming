#include "World.h"
#include "Robot.h"
using namespace std;
class Robot;
World::World()
{
    // Creating an empty world
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        for (int j = 0; j < WORLD_SIZE; j++)
            grid[i][j] = NULL;
    }
}

World::~World()
{
    // Destroying the world
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        for (int j = 0; j < WORLD_SIZE; j++)
        {
            if (grid[i][j] != NULL)
                delete (grid[i][j]);
        }
    }
}

Robot *World::get_at(int x, int y)
{
    // making sure we dont go ut of bounds and returning whatever is in the cell we want
    if ((x >= 0) && (x < WORLD_SIZE) && (y >= 0) && (y < WORLD_SIZE))
        return grid[x][y];
    else
        return NULL;
}

void World::set_at(int x, int y, Robot *mrRoboto)
{
    // Sets a robot to the indeces given in the parameter
    if ((x >= 0) && (x < WORLD_SIZE) && (y >= 0) && (y < WORLD_SIZE))
        grid[x][y] = mrRoboto;
}

void World::display()
{
    // Displays the world
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        for (int j = 0; j < WORLD_SIZE; j++)
        {
            if (grid[i][j] != NULL)
            {
                if (grid[i][j]->get_type() == "OPTIMUSPRIME")
                    std::cout << " O ";

                else if (grid[i][j]->get_type() == "ROBOCOP")
                    std::cout << " C ";

                else if (grid[i][j]->get_type() == "ROOMBA")
                    std::cout << " R ";

                else if (grid[i][j]->get_type() == "BULLDOZER")
                    std::cout << " B ";
            }
            else
                std::cout << " . ";
        }
        std::cout << std::endl;
    }
}

void World::simulate_one_turn()
{
    // Function to simulate one turn in the world.
    // Every robot is moved in one turn (unless they die first)

    int i, j;
    // Reset all robots to not fought (moved) for this turn yet
    for (i = 0; i < WORLD_SIZE; i++)
    {
        for (j = 0; j < WORLD_SIZE; j++)
        {
            if (grid[i][j] != NULL)
                grid[i][j]->fought = false;
        }
    }

    // Loop through cells and move if its a robot
    for (i = 0; i < WORLD_SIZE; i++)
    {
        for (j = 0; j < WORLD_SIZE; j++)
        {
            if ((grid[i][j] != NULL))
            {
                if (grid[i][j]->fought == false)
                {
                    grid[i][j]->fought = true; // Mark as moved
                    grid[i][j]->move();        // Move the robot
                    sweep_grid();
                }
            }
        }
    }
}

void World::sweep_grid()
{
    // Function checks the entire grid to see how many robots are left. If only one robot is left, the game ends
    int robotCount = 0;
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        for (int j = 0; j < WORLD_SIZE; j++)
        {
            if (grid[i][j] != NULL)
                robotCount++;
        }
    }

    if (robotCount == 1)
    { // If there is only one robot left, find that robot, display the winner message, terminate the program
        int i, j, flag = 0;
        for (i = 0; i < WORLD_SIZE; i++)
        {
            for (j = 0; j < WORLD_SIZE; j++)
            {
                if (grid[i][j] != NULL)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
        }

        std::cout << "THE WINNER IS: " << grid[i][j]->get_name() << std::endl;
        delete grid[i][j]; // Delete the last Robot's pointer
        exit(0);
    }

    else
        return;
}