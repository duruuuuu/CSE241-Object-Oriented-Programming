#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void shoot(bool shooter, int shooterNum, bool &target)
{
    /* Function for taking turns shooting
       Returns 1 if the target is hit, 0 otherwise. */

    int hit = 0;

    if (!shooter)
        return;

    if (shooterNum == 0)
        hit = (rand() % 3);

    else if (shooterNum == 1)
        hit = (rand() % 2);

    else if (shooterNum == 2)
        hit = 1;

    if (hit)
        target = false;
}

int main()
{
    srand(time(NULL));

    const int MAX_DUELS = 10000; // Number of duel simulations

    const int AARON = 0;
    const int BOB = 1;
    const int CHARLIE = 2;

    int aaronWins = 0,
        bobWins = 0,
        charlieWins = 0;

    for (int i = 0; i < MAX_DUELS; i++)
    {
        bool aaronLife = true,
             bobLife = true,
             charlieLife = true;

        while (!((charlieLife == false && bobLife == false) || (charlieLife == false && aaronLife == false) || (bobLife == false && aaronLife == false)))
        {
            if (aaronLife)
            {
                // Aarons turn to shoot
                if (charlieLife)
                    shoot(aaronLife, 0, charlieLife);

                else if (charlieLife == false && bobLife == true)
                    shoot(aaronLife, 0, bobLife);

                else if (!charlieLife && !bobLife)
                    break;
            }

            if (bobLife)
            {
                // Bob's turn to shoot
                if (charlieLife == true)
                    shoot(bobLife, 1, charlieLife);

                else if (charlieLife == false && aaronLife == true)
                    shoot(bobLife, 1, aaronLife);

                else if (!charlieLife && !aaronLife)
                    break;
            }

            if (charlieLife)
            {
                // Charlies's turn to shoot
                if (bobLife == true)
                    shoot(charlieLife, 2, bobLife);

                else if (bobLife == false && aaronLife == true)
                    shoot(charlieLife, 2, aaronLife);

                else if (!bobLife && !aaronLife)
                    break;
            }

            if (bobLife == false && charlieLife == false)
            {
                aaronWins++;
                break;
            }

            else if (aaronLife == false && bobLife == false)
            {
                charlieWins++;
                break;
            }

            else if (aaronLife == false && charlieLife == false)
            {
                bobWins++;
                break;
            }
        }
    }
    cout << "AARON WINS: " << aaronWins << "/" << MAX_DUELS << " duels. " << (static_cast<double>(aaronWins) / MAX_DUELS) * 100 << "%" << endl;
    cout << "BOB WINS: " << bobWins << "/" << MAX_DUELS << " duels. " << (static_cast<double>(bobWins) / MAX_DUELS) * 100 << "%" << endl;
    cout << "CHALRLIE WINS: " << charlieWins << "/" << MAX_DUELS << " duels. " << (static_cast<double>(charlieWins) / MAX_DUELS) * 100 << "%" << endl;

    return 0;
}