#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int rollDice()
{
    /* Function to roll dice */
    srand(time(NULL));
    return (rand() % 6) + 1;
}

int humanTurn(unsigned int humanTotalScore)
{
    cout << "\nYOUR TURN! " << endl;
    unsigned int score = 0;
    int dieVal = 0;
    char input;

    while (1)
    {
        dieVal = rollDice();

        cout << "Roll amount: " << dieVal << endl;

        /* If the player rolls a 1, immediately stop the rolling loop */
        if (dieVal == 1)
            break;

        /* Add the die roll tot he score */
        score += dieVal;

        /* User prompt */
        cout << "Would you like to ROLL AGAIN (r) or HOLD (h)?" << endl;
        cin >> input;

        if (input == 'h')
            break;

        else
            continue;
    }

    /* Return 0 if player rolls 1 */
    if (dieVal == 1)
    {
        cout << "Sorry, your turn is over. You get no points." << endl;
        return 0;
    }

    /* Return the score after holding */
    else
    {
        cout << "Total accumulated points: " << score << endl;
        return score;
    }
}

int computerTurn(unsigned int computerTotalScore)
{
    cout << "\nCOMPUTER'S TURN" << endl;

    const int maxComputerScore = 20;
    unsigned int score = 0;
    int dieRoll = 0;

    while (score < maxComputerScore)
    {
        dieRoll = rollDice();
        cout << "Roll amount: " << dieRoll << endl;

        if (dieRoll == 1)
            break;

        score += dieRoll;

        // If the score reaches the upper roll amount, computer holds
        if (score >= maxComputerScore)
            break;
    }

    if (dieRoll == 1)
    {
        cout << "Computer has no points." << endl;
        return 0;
    }

    else
    {
        cout << "Computer holding... Total accumulated points: " << score << endl;
        return score;
    }
}

int main()
{
    const int maxScore = 100;
    unsigned int humanScore = 0,
                 computerScore = 0;

    /* Loop goes on until either player reaches the maximum score */
    while ((humanScore < maxScore) || (computerScore < maxScore))
    {
        if ((humanScore >= maxScore) || (computerScore >= maxScore))
            break;

        /* Calling the turn functions and adding the scores to local score vars */
        humanScore += humanTurn(humanScore);
        computerScore += computerTurn(computerScore);
    }

    if (humanScore > computerScore)
        cout << "##### YOU WIN!!! #####" << endl
             << "You: " << humanScore << "|| Computer: " << computerScore << endl;

    else
        cout << "##### YOU LOSE!!! #####" << endl
             << "Computer: " << computerScore << "|| You: " << humanScore << endl;
}
