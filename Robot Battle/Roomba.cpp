#include "Roomba.h"
#include "Robot.h"
#include "World.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

Roomba::Roomba()
    : Robot{} {}

Roomba::Roomba(World *world, int x, int y, std::string name, int num)
    : Robot{world, x, y}
{
    hitpoints = 10;
    strength = 3;

    char chNum = num + '0';
    this->name = "roomba_";
    this->name += chNum;
}

std::string Roomba::get_type() const
{
    return "ROOMBA";
}

int Roomba::get_damage() const
{
    srand(time(NULL));

    int d_r = (rand() % strength) + 1;

    return d_r;
}

Robot *Roomba::fight(Robot *S)
{ /* Roomba's fight function is overrides Robot's original function because Roombas attack twice since they are fast. */
    while (true)
    {
        // Roomba is very fast so it attacks twice
        for (int i = 0; i < 2; i++)
        {
            int d_r = get_damage();
            int S_initHitpoints = S->get_hitpoints();
            S->set_hitpoints((S_initHitpoints - d_r));

            // Printing hit message
            std::cout << get_name() << "(" << get_hitpoints() << ") hits "
                      << S->get_name() << "(" << S_initHitpoints << ") with " << d_r << "(HIT " << i + 1 << ")" << std::endl;

            std::cout
                << "The new hitpoints of " << S->get_name() << " is " << S->get_hitpoints() << std::endl;

            if (S->get_hitpoints() <= 0)
            {
                std::cout << S->get_name() << " IS DEAD." << std::endl;
                cout << "=================" << endl;
                return S;
            }
        }

        if (S->get_type() == "ROOMBA")
        {

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