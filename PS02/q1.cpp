#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void aaron_turn(bool aaron, bool &bob, bool &charlie)
{
    /* Function to simulate Aaron's turn */

    // If Aaron is already dead, return
    if (!aaron)
        return;

    // Get a random 1-in-3 shot
    int shot = rand() % 3;
    if (shot == 1)
    {
        if (charlie)
            charlie = false;

        else if (!charlie && bob)
            bob = false;
    }
}

void bob_turn(bool bob, bool &aaron, bool &charlie)
{
    /* Function to simulate Bob's turn. Works the same was as Aaron's turn */
    if (!bob)
        return;

    int shot = rand() % 2;
    if (shot == 1)
    {
        if (charlie)
            charlie = false;

        else if (!charlie && aaron)
            aaron = false;
    }
}

void charlie_turn(bool charlie, bool &aaron, bool &bob)
{
    /* Function to simulate Charlie's turn. Works the same way as Aaron and Bob's turns */
    if (!charlie)
        return;

    if (bob)
        bob = false;

    else if (!bob && aaron)
        aaron = false;
}

int main()
{
    srand(time(NULL));

    const int MAX_DUELS = 10000; // Number of duel simulations
    bool aaronLife, bobLife, charlieLife;
    int aaronWins = 0,
        bobWins = 0,
        charlieWins = 0;

    // Outer loop for the number of simulations and keeps tracks of each players wins
    for (int i = 0; i < MAX_DUELS; i++)
    {
        aaronLife = true;
        bobLife = true;
        charlieLife = true;

        // Inner loop to do the simulations until someone is the winner
        while (!(((charlieLife == false) && (bobLife == false)) || ((charlieLife == false) && (aaronLife == false)) || ((bobLife == false) && (aaronLife == false))))
        {
            aaron_turn(aaronLife, bobLife, charlieLife);
            bob_turn(bobLife, aaronLife, charlieLife);
            charlie_turn(charlieLife, aaronLife, bobLife);
        }

        // Incrementing the win count of the winner
        if (aaronLife && !bobLife && !charlieLife)
            aaronWins++;

        else if (bobLife && !aaronLife && !charlieLife)
            bobWins++;

        if (charlieLife && !bobLife && !aaronLife)
            charlieWins++;
    }
    cout << "AARON WINS: " << aaronWins << "/" << MAX_DUELS << " duels. " << (static_cast<double>(aaronWins) / MAX_DUELS) * 100 << "%" << endl;
    cout << "BOB WINS: " << bobWins << "/" << MAX_DUELS << " duels. " << (static_cast<double>(bobWins) / MAX_DUELS) * 100 << "%" << endl;
    cout << "CHALRLIE WINS: " << charlieWins << "/" << MAX_DUELS << " duels. " << (static_cast<double>(charlieWins) / MAX_DUELS) * 100 << "%" << endl;

    return 0;
}