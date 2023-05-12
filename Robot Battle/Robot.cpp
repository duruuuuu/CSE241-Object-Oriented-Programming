#include "Robot.h"
#include "World.h"
class World;
using namespace std;

Robot::Robot() // No args constructor
    : world(NULL), fought(false), x(0), y(0)
{
    // Intentionally left empty
}

Robot::Robot(World *world, int x, int y)
    : fought(false)
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

void Robot::move()
{
    // Function to move the robot one space
    // We get a random direction at each move and go to that direction, if the direction we get is empty,
    // the robot forwards to that spot and gets another random direction to move to.
    // This is repeated until the random direction that the rbot moves to is occupied by another robot.
    // In which case, the robots fight.

    srand(time(NULL));
    while (true)
    {
        // world->display();
        // cout << "==========================" << endl;

        int dir = rand() % 4;

        if (dir == 0) // move left
        {
            // If the next cell is empty, move there
            if ((y > 0) && (world->get_at(x, y - 1)) == NULL)
            {
                world->set_at(x, y - 1, world->get_at(x, y));
                world->set_at(x, y, NULL);
                y--;
                continue;
            }

            // If the robot tries to move out of bounds
            else if (y <= 0)
                continue;

            // If a robot is occupying th cell we want to go to
            else
            {
                int axisX, axisY;
                Robot *deadOne = fight(world->get_at(x, y - 1)); // Robots fight and return the dead robot
                axisX = deadOne->x;
                axisY = deadOne->y;
                world->set_at(axisX, axisY, NULL); /// Set the dead robot's cell to NULL

                // if S is the dead one, move R to its place
                if (deadOne != this)
                {
                    world->set_at(axisX, axisY, this);
                    world->set_at(x, y, NULL);
                    x = axisX;
                    y = axisY;
                }

                delete deadOne; // delete the dead robot's pointer

                return;
            }
        }

        else if (dir == 1) // move right
        {
            if ((y < WORLD_SIZE - 1) && (world->get_at(x, y + 1) == NULL))
            {
                world->set_at(x, y + 1, world->get_at(x, y));
                world->set_at(x, y, NULL);
                y++;
                continue;
            }

            else if (y >= WORLD_SIZE - 1)
                continue;

            else
            {
                int axisX, axisY;
                Robot *deadOne = fight(world->get_at(x, y + 1));
                axisX = deadOne->x;
                axisY = deadOne->y;
                world->set_at(axisX, axisY, NULL);

                // if S is the dead one, move R to its place
                if (deadOne != this)
                {
                    world->set_at(axisX, axisY, this);
                    world->set_at(x, y, NULL);
                    x = axisX;
                    y = axisY;
                }

                delete deadOne;

                return;
            }
        }

        else if (dir == 2) // move up
        {
            if ((x > 0) && (world->get_at(x - 1, y) == NULL))
            {
                world->set_at(x - 1, y, world->get_at(x, y));
                world->set_at(x, y, NULL);
                x--;
                continue;
            }

            else if (x <= 0)
                continue;

            else
            {
                int axisX, axisY;
                Robot *deadOne = fight(world->get_at(x - 1, y));
                axisX = deadOne->x;
                axisY = deadOne->y;
                world->set_at(axisX, axisY, NULL);

                // if S is the dead one, move R to its place
                if (deadOne != this)
                {
                    world->set_at(axisX, axisY, this);
                    world->set_at(x, y, NULL);
                    x = axisX;
                    y = axisY;
                }

                delete deadOne;

                return;
            }
        }

        else if (dir == 3) // move down
        {
            if ((x < WORLD_SIZE - 1) && (world->get_at(x + 1, y) == NULL))
            {
                world->set_at(x + 1, y, world->get_at(x, y));
                world->set_at(x, y, NULL);
                x++;
                continue;
            }
            else if (x >= WORLD_SIZE - 1)
                continue;

            else
            {
                int axisX, axisY;
                Robot *deadOne = fight(world->get_at(x + 1, y));
                axisX = deadOne->x;
                axisY = deadOne->y;
                world->set_at(axisX, axisY, NULL);

                // if S is the dead one, move R to its place
                if (deadOne != this)
                {
                    world->set_at(axisX, axisY, this);
                    world->set_at(x, y, NULL);
                    x = axisX;
                    y = axisY;
                }

                delete deadOne;

                return;
            }
        }
    }
}

Robot *Robot::fight(Robot *S)
{
    // FIGHT LOOP
    while (true)
    {
        // Get damage of th attacker robot
        int d_r = get_damage();
        // Calculate the victim's new hitpoint after the attack
        int S_initHitpoints = S->get_hitpoints();
        S->set_hitpoints((S_initHitpoints - d_r));

        // Printing hit message
        std::cout << get_name() << "(" << get_hitpoints() << ") hits "
                  << S->get_name() << "(" << S_initHitpoints << ") with " << d_r << std::endl;

        std::cout << "The new hitpoints of " << S->get_name() << " is " << S->get_hitpoints() << std::endl;

        // If the victim robot is dead, return S.
        if (S->get_hitpoints() <= 0)
        {
            std::cout << S->get_name() << " IS DEAD." << std::endl;
            cout << "=================" << endl;
            return S;
        }

        // VICTIM"S TURN
        if (S->get_type() == "ROOMBA")
        { // IF the robot is a Roomba, attach twice because they are fast

            for (int i = 0; i < 2; i++)
            {
                int d_s = S->get_damage();
                int R_initHitpoints = get_hitpoints();
                hitpoints -= d_s;
                // Printing hit message
                std::cout << S->get_name() << "(" << S->get_hitpoints() << ") hits "
                          << get_name() << "(" << R_initHitpoints << ") with " << d_s << "(HIT " << i + 1 << ")" << std::endl;

                std::cout << "The new hitpoints of " << get_name() << " is " << get_hitpoints() << std::endl;

                if (get_hitpoints() <= 0)
                {
                    std::cout << get_name() << " IS DEAD." << std::endl;
                    cout << "=================" << endl;
                    return this;
                }
            }
        }

        // If the victim is not a Roomba
        else
        {
            int d_s = S->get_damage();
            int R_initHitpoints = get_hitpoints();
            hitpoints -= d_s;
            // Printing hit message
            std::cout << S->get_name() << "(" << S->get_hitpoints() << ") hits "
                      << get_name() << "(" << R_initHitpoints << ") with " << d_s << std::endl;

            std::cout << "The new hitpoints of " << get_name() << " is " << get_hitpoints() << std::endl;

            if (get_hitpoints() <= 0)
            {
                std::cout << get_name() << " IS DEAD." << std::endl;
                cout << "=================" << endl;
                return this;
            }
        }
    }
}