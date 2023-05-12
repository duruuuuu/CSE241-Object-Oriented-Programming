#include "Bulldozer.h"
#include "Robot.h"
#include "World.h"
#include <time.h>
#include <cstdlib>
#include <cstring>
using namespace std;
Bulldozer::Bulldozer()
    : Robot{} {}

Bulldozer::Bulldozer(World *world, int x, int y, std::string name, int num)
    : Robot{world, x, y}
{
    hitpoints = 200;
    strength = 50;

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

void Bulldozer::move()
{
    cout << "bulldozer move" << endl;

    srand(time(NULL));

    while (true)
    {
        cout << "===========" << endl;
        world->display();
        int dir = rand() % 4;

        // cout << "hey " << dir << endl;
        if (dir == 0) // move left
        {
            // If the next cell is empty
            if ((y > 0) && (world->get_at(x, y - 1)) == NULL)
            {
                world->set_at(x, y - 1, world->get_at(x, y));
                world->set_at(x, y, NULL);
                y--;
                continue;
            }
            else if (y <= 0)
                continue;

            // if there is a robot in the next cell
            else
            {
                fight(world->get_at(x, y - 1));
                if (world->get_at(x, y - 1)->alive == false)
                {
                    delete world->get_at(x, y - 1);
                    world->set_at(x, y - 1, NULL);
                }

                else if (this->alive == false)
                {
                    // delete this;
                    world->set_at(x, y, NULL);
                }
                // std::cout << "hey return (up)" << std::endl;
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
                fight(world->get_at(x, y + 1));
                if (world->get_at(x, y + 1)->alive == false)
                {
                    delete world->get_at(x, y + 1);
                    world->set_at(x, y + 1, NULL);
                }
                else if (this->alive == false)
                {
                    // delete this;
                    world->set_at(x, y, NULL);
                }
                // std::cout << "hey return (right)" << std::endl;

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
                fight(world->get_at(x - 1, y));
                if (world->get_at(x - 1, y)->alive == false)
                {
                    delete world->get_at(x - 1, y);
                    world->set_at(x - 1, y, NULL);
                }
                else if (this->alive == false)
                {
                    // delete this;
                    world->set_at(x, y, NULL);
                }
                // std::cout << "hey return (left)" << std::endl;

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
                fight(world->get_at(x + 1, y));
                if (world->get_at(x + 1, y)->alive == false)
                {
                    delete world->get_at(x + 1, y);
                    world->set_at(x + 1, y, NULL);
                }
                else if (this->alive == false)
                {
                    // delete this;
                    world->set_at(x, y, NULL);
                }
                // std::cout << "hey return (right)" << std::endl;

                return;
            }
        }
    }
}

void Bulldozer::fight(Robot *S)
{
    while (true)
    {
        cout << "bulldozer fight" << endl;
        int d_r = get_damage();
        int S_initHitpoints = S->get_hitpoints();
        S->set_hitpoints((S_initHitpoints - d_r));

        // Printing hit message
        std::cout << get_name() << "(" << get_hitpoints() << ") hits "
                  << S->get_name() << "(" << S_initHitpoints << ") with " << d_r << std::endl;

        std::cout << "The new hitpoints of " << S->get_name() << " is " << S->get_hitpoints() << std::endl;

        if (S->get_hitpoints() <= 0)
        {
            std::cout << S->get_name() << " IS DEAD." << std::endl;
            cout << "=================" << endl;
            S->alive = false;
            return;
        }

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
            this->alive = false;
            return;
        }
    }
}