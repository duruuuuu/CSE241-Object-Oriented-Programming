#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "Robot.h"
#include "Humanic.h"
#include "OptimusPrime.h"
#include "Roomba.h"
#include "World.h"
#include "Bulldozer.h"
#include "Robocop.h"

using namespace std;

// const int WORLD_SIZE = 10;
const int INIT_ROBOTS = 5;

int main()
{
    srand(time(NULL));

    // Creating world using World class constructor
    World w;

    // Creating robots
    int robotCount = 0;

    // // Randomly place OPTIMUS PRIME robots
    // while (robotCount < INIT_ROBOTS)
    // {
    //     int x = rand() % WORLD_SIZE;
    //     int y = rand() % WORLD_SIZE;

    //     if (w.get_at(x, y) == NULL) // make sure ant is in an empty spot
    //     {
    //         robotCount++;
    //         OptimusPrime *r1 = new OptimusPrime(&w, x, y, "optimusprime", robotCount);
    //     }
    // }

    // robotCount = 0;
    // // Randomly place ROBOCOP robots
    // while (robotCount < INIT_ROBOTS)
    // {
    //     int x = rand() % WORLD_SIZE;
    //     int y = rand() % WORLD_SIZE;

    //     if (w.get_at(x, y) == NULL) // make sure ant is in an empty spot
    //     {
    //         robotCount++;
    //         Robocop *r2 = new Robocop(&w, x, y, "robocop", robotCount);
    //     }
    // }

    robotCount = 0;
    // Randomly place ROOMBA robots
    while (robotCount < INIT_ROBOTS)
    {
        int x = rand() % WORLD_SIZE;
        int y = rand() % WORLD_SIZE;

        if (w.get_at(x, y) == NULL) // make sure ant is in an empty spot
        {
            robotCount++;
            Roomba *r3 = new Roomba(&w, x, y, "roomba", robotCount);
        }
    }

    robotCount = 0;
    // Randomly place BULLDOZER robots
    while (robotCount < INIT_ROBOTS)
    {
        int x = rand() % WORLD_SIZE;
        int y = rand() % WORLD_SIZE;

        if (w.get_at(x, y) == NULL) // make sure ant is in an empty spot
        {
            robotCount++;
            Bulldozer *r4 = new Bulldozer(&w, x, y, "bullldozer", robotCount);
        }
    }
    string s;
    while (true)
    {
        // w.display();
        w.simulate_one_turn();
        cout << endl
             << "Press enter for the next step" << endl;
        getline(cin, s);
        /*
        for (int i = 0; i < WORLD_SIZE; i++)
        {
            for (int j = 0; j < WORLD_SIZE; j++)
            {
                if (w.get_at(i, j) != NULL)
                {
                    cout << w.get_at(i, j)->get_type() << "\t\t" << w.get_at(i, j)->get_name()
                         << "\t\tStrength: " << w.get_at(i, j)->get_strength()
                         << "\t\tHitpoints: " << w.get_at(i, j)->get_hitpoints() << endl;
                }
            }
        }
        */
    }
}
