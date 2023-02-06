#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_set>

using namespace std;

// function to generate a random number of length given by the user
string generate_random_number(int n)
{
    string result;
    vector<int> numbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        int j = rand() % (10 - i);
        result += to_string(numbers[j]);
        swap(numbers[j], numbers[9 - i]);
    }

    return result;
}

// error checking to see if the length given for the random generation is valid
int input_error_checking(int n)
{
    if (n > 9 || n < 1)
    {
        cout << "Please enter a valid number length. It cannot be more than 9, or less than 1" << endl;
        return 1;
    }

    else
        return 0;
}

// error chrcking to see if user given secret number is valid
int input_error_checking(string s)
{
    if (s.at(0) == '0')
    {
        cout << "Please enter a valid secret number. (Leftmost digit cannot be 0.)" << endl;
        return 1;
    }

    else
    {
        int flag = 0;
        for (int i = 0; i < s.length(); i++)
        {
            for (int j = i + 1; j < s.length(); j++)
            {
                if (s.at(i) == s.at(j))
                {
                    cout << "Please enter a valid number. (The number cannot contain repeating digits.)" << endl;
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
        }

        if (flag == 0)
            return 0;

        else
            return 1;
    }
}

bool input_error_checking(size_t length1, size_t length2)
{
    if (length1 != length2)
    {
        cout << "E1" << endl;
        return false;
    }

    else
        return true;
}

int find_exact_digits(string secretNum, string guess)
{
    int count = 0;
    for (size_t i = 0; i < secretNum.length(); i++)
    {
        if (secretNum.at(i) == guess.at(i))
            count++;
        else
            continue;
    }

    return count;
}

int find_misplaced_digits(string secretNum, string guess)
{
    int count = 0;
    for (size_t i = 0; i < secretNum.length(); i++)
    {
        for (size_t j = 0; j < guess.length(); j++)
        {
            if ((i != j) && (secretNum.at(i) == guess.at(j)))
                count++;

            else
                continue;
        }
    }

    return count;
}

int main()
{
    string generatingType, // how he number will be generated whether the user enters -u or -r
        num,               // following the generating type, user will enter either the secret number or its length
        trash;             // trash variable for the word mastermind in the initial input

    int error = 1; // flag variable for error checking while the user enters info
    while (error)
    {
        cin >> trash >> generatingType >> num;
        if (generatingType == "-r" || generatingType == "-u") // checking if the generating type is correct
        {
            // checking if the user-entered number is valid
            if (generatingType == "-u")
            {
                error = input_error_checking(num);
            }

            // if the generating type is random, check if the length is valid
            else if (generatingType == "-r")
            {
                int n = stoi(num);
                error = input_error_checking(n);
            }
        }

        // if the generating type is invalid
        else
        {
            cout << "Please enter a valid generation type. (-r for random generation, -u for user generation.)" << endl;
            continue;
        }
    }

    // generating a random number
    int length = 0; // variabe to hold the length of the secret number given by the user
    if (generatingType == "-r")
    {
        length = stoi(num);                   // converting string of secret number length to int
        num = generate_random_number(length); // generating a random secret number
        // cout << num << endl;
    }

    bool flag = true;
    string guess;
    int cExact, cMisplaced, count = 0;
    const int lives = 100;
    while (flag && count < lives)
    {
        count++; // incrementing the number of guessing iteration
        cin >> guess;

        // checking if the length of the guess is valid
        flag = input_error_checking(guess.length(), num.length());

        // find digits in the right spot
        cExact = find_exact_digits(num, guess);

        // find digits in the wrong spot
        cMisplaced = find_misplaced_digits(num, guess);

        // if the secret number is found, exit the game.
        if (guess == num)
        {
            cout << "FOUND " << count << endl;
            flag = false;
            break;
        }

        // printing the exact and misplaced digits
        cout << cExact << " " << cMisplaced << endl;
    }

    if (count >= lives)
    {
        cout << "YOU COULD NOT FIND THE SECRET NUMBER. IT WAS " << num << endl;
    }

    return 0;
}