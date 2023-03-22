#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> suitorsVec;
    int suitorsNum = 0;

    cout << "Enter the number of suitors: ";
    cin >> suitorsNum;

    for (int i = 0; i < suitorsNum; i++)
        suitorsVec.push_back(i + 1);

    const int countAhead = 2;
    int currSuitor = 0;
    int i;
    if (suitorsNum < 1)
    { // if there is 0 or an invalid number of suitors
        cout << "There are no suitors" << endl;
        exit(1);
    }

    else if (suitorsNum == 1)
    { // if there is only 1 suitor
        cout
            << "You are the only suitor. You have the princess' hand in marriage." << endl;
        exit(1);
    }

    else // if there is more than 1 suitor
    {
        currSuitor = 0;
        while (suitorsVec.size() > 1)
        {
            // Counting three people starting from the first person
            for (i = 0; i < countAhead; i++)
            {
                currSuitor++;

                // IF the end is reached, go back to the beginning
                if (currSuitor == suitorsVec.size())
                    currSuitor = 0;
            }
            // Eliminate current suitor which is the 3rd in line suitor
            suitorsVec.erase(suitorsVec.begin() + currSuitor);
            if (currSuitor == suitorsVec.size())
                currSuitor = 0;
        }
    }

    cout << "To win the princess' hand in marriage, you must be in the " << suitorsVec.at(0) << ". position." << endl;
}