#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void aaron_turn(bool aaron, bool &bob, bool &charlie)
{
    /* Function to simulate Aaron's turn */

    // If Aaron is already dead, return and do nothing
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

    int shot = rand() % 2; // 1-in-2 chance of winning
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

    // If charlie is still alive, 100% kill the next strongest person
    if (bob)
        bob = false;

    else if (!bob && aaron)
        aaron = false;
}

void simulate_turns(bool &aaron, bool &bob, bool &charlie)
{
    /* Function to simulate the turns in the loop */
    aaron_turn(aaron, bob, charlie);
    bob_turn(bob, aaron, charlie);
    charlie_turn(charlie, aaron, bob);
}

void increment_winner_score(int &aaron, int &bob, int &charlie, bool &aaronLife, bool &bobLife, bool &charlieLife)
{
    /* Function to increment the score of the winner */
    if (aaronLife && !bobLife && !charlieLife)
        aaron++;

    else if (bobLife && !aaronLife && !charlieLife)
        bob++;

    else if (charlieLife && !bobLife && !aaronLife)
        charlie++;
}

int main()
{
    srand(time(NULL));

    const int MAX_DUELS = 10000; // Number of duel simulations

    bool aaronLife, bobLife, charlieLife; // player's lives, true or false

    // Keeps track of the players wins
    int aaronWins = 0,
        bobWins = 0,
        charlieWins = 0;

    // Outer loop for the number of simulations and keeps tracks of each players wins
    for (int i = 0; i < MAX_DUELS; i++)
    {
        // Set lives to true at the beginning of each simulation
        aaronLife = true;
        bobLife = true;
        charlieLife = true;

        // Inner loop to do the simulations until someone is the winner or when two people are dead
        while (!(((charlieLife == false) && (bobLife == false)) || ((charlieLife == false) && (aaronLife == false)) || ((bobLife == false) && (aaronLife == false))))
            simulate_turns(aaronLife, bobLife, charlieLife);

        // Incrementing the win count of the winner
        increment_winner_score(aaronWins, bobWins, charlieWins, aaronLife, bobLife, charlieLife);
    }

    // Printing the statistics of the simulations
    cout << "AARON WINS: " << aaronWins << "/" << MAX_DUELS << " duels or " << (static_cast<double>(aaronWins) / MAX_DUELS) * 100 << "%" << endl;
    cout << "BOB WINS: " << bobWins << "/" << MAX_DUELS << " duels or " << (static_cast<double>(bobWins) / MAX_DUELS) * 100 << "%" << endl;
    cout << "CHALRLIE WINS: " << charlieWins << "/" << MAX_DUELS << " duels or " << (static_cast<double>(charlieWins) / MAX_DUELS) * 100 << "%" << endl;

    return 0;
}