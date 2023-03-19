/*
    QUESTIONS:
        1. Progrma run thing, typo?
        2. Should the program end if the user guessed a number with a repeating digit?
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SIZE = 12;
const int SENT_VAL = -999;
const int MAX_TURNS = 100;

void clean_array(char *arr)
{
    /* Function to clean the character array to make sure there are no complications in a loop/buffer*/
    for (int i = 0; i < MAX_SIZE; i++)
        arr[i] = '\0';
}

void clean_array(int *arr)
{
    /* Function to clean the integer array to make sure there are no complications in a loop/buffer*/
    for (int i = 0; i < MAX_SIZE; i++)
        arr[i] = SENT_VAL;
}

void generate_random_number(int *nums, int length)
{
    /* function to generate a random number of length given by the user */
    srand(time(0));

    for (int i = 0; i < length; i++)
    {
        bool isUnique = false;
        int randomNumber;

        while (!isUnique)
        {
            randomNumber = rand() % 10; // Generate a random number from 0 to 9

            // Check if the random number is unique
            isUnique = true;
            for (int j = 0; j < i; j++)
            {
                if (nums[j] == randomNumber)
                {
                    isUnique = false;
                    break;
                }
            }
        }

        nums[i] = randomNumber; // Store the unique random number in the array
    }

    for (int i = length; i < MAX_SIZE; i++)
        nums[i] = SENT_VAL;
}

int find_exact_digits(int *secretNum, int *guess)
{
    /* Funtion to find the exact correct spot in the guessed number of the user */
    int count = 0;
    for (int i = 0; guess[i] != SENT_VAL; i++)
    {
        if (secretNum[i] == guess[i])
            count++;
        else
            continue;
    }

    return count;
}

int find_misplaced_digits(int *secretNum, int *guess)
{
    /* Function to find the misplaced digits in the guess of the user */
    int count = 0;
    for (int i = 0; secretNum[i] != SENT_VAL; i++)
    {
        for (int j = 0; guess[j] != SENT_VAL; j++)
        {
            if ((i != j) && (secretNum[i] == guess[j]))
                count++;

            else
                continue;
        }
    }

    return count;
}

void check_user_input(char *inputArr)
{
    /* Function to error check the user input at the start of the game */

    if (inputArr[1] != 'r' && inputArr[1] != 'u')
    {
        cout << "E0" << endl;
        exit(1);
    }

    // If the random number generator is followed by a 0 or negative number
    if (inputArr[1] == 'r')
    {
        if (inputArr[3] < '1')
            cout << "E0" << endl;
        exit(1);
    }

    // If the user generated number has digits which are not unique
    if (inputArr[1] == 'u')
    {
        for (int i = 3; inputArr[i] != '\0'; i++)
        {
            for (int j = i + 1; inputArr[j] != '\0'; j++)
            {
                if (inputArr[i] == inputArr[j])
                {
                    cout << "E0" << endl;
                    exit(1);
                }
            }
        }
    }
}

void check_user_input(int *inputArr, int *secretNumber)
{
    /* Function to check the user input while guessing the secret number*/

    int secretNumberSize = 0;
    int inputNumberSize = 0;

    /* Couting the digits of the secret number and guessed number */
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (secretNumber[i] != -999)
            secretNumberSize++;

        if (inputArr[i] != -999)
            inputNumberSize++;
    }

    /* Checks if the input is a valid character */
    if (inputArr[0] > 9 || inputArr[0] < 0)
    {
        cout << "inputArr: " << inputArr[0] << endl;
        cout << "E2" << endl;
        exit(1);
    }

    /* Checks if the input has a valid number of digits */
    else if (secretNumberSize != inputNumberSize)
    {
        cout << "E1" << endl;
        exit(1);
    }
}

void convert_input(char *inputArr, int *numArr)
{
    /* Fucntion to convert the input numbers from type char to type int */
    /* THIS FUNCTION IS USED FOR THE INITIAL -U CALL */

    int i;
    for (i = 3; inputArr[i] != '\0'; i++)
        numArr[i - 3] = (inputArr[i] - '0');

    for (i -= 3; i < MAX_SIZE; i++)
        numArr[i] = SENT_VAL;
}

void convert_input(int *numArr, char *inputArr)
{
    /* Function to convert the input of the guessed number */
    /* THIS FUNCTION IS USED TO CONVERT THE NUMBER ENTERED WHILE GUESSING */
    int i;
    for (i = 0; inputArr[i] != '\0'; i++)
        numArr[i] = (inputArr[i] - '0');

    for (; i < MAX_SIZE; i++)
        numArr[i] = SENT_VAL;
}

int get_secret_number_size(int *secretNumber)
{
    /* Function to get the number of digits in the secret number */
    int i;
    for (i = 0; secretNumber[i] != SENT_VAL; i++)
    {
        ;
    }

    return i;
}

void guess_number(int *secretNumber, char generationType)
{
    /* Function to implement the loop for guessing the number */
    // Arrays to hold the input guess numbers
    char inputCh[MAX_SIZE];
    int inputN[MAX_SIZE];

    // cleaning arrays to make sure they have proper null values and sentinal values
    clean_array(inputCh);
    clean_array(inputN);

    int iteration = 0;
    int secretNumberSize = get_secret_number_size(secretNumber);

    /* Prints the secret number for testing purposes */
    for (int j = 0; secretNumber[j] != SENT_VAL; j++)
        cout << secretNumber[j];
    cout << endl;

    /* User starts guessing the number */
    while (iteration < 100)
    {
        char inputCh[MAX_SIZE];

        iteration++;

        // Getting the guess of the user
        cin.getline(inputCh, MAX_SIZE);

        // converting input from char to int
        convert_input(inputN, inputCh);

        // Error checking input to make sure it is valid
        check_user_input(inputN, secretNumber);

        // finding the exact and misplaced digits
        int exactDigits = find_exact_digits(secretNumber, inputN);
        int misplacedDigits = find_misplaced_digits(secretNumber, inputN);

        /* If the secret number is found, exit the game. */
        if (exactDigits == secretNumberSize)
        {
            cout << "FOUND " << iteration << endl;
            exit(1);
        }

        // Printing the exact and misplaced digits
        cout << exactDigits << " " << misplacedDigits << endl;

        /* Flushing the arrays so there are no problems with buffer or loop */
        clean_array(inputCh);
        clean_array(inputN);
    }
}

void game_play(char *inputArr)
{
    // Checking user input for errors
    check_user_input(inputArr);

    int secretNumber[MAX_SIZE];

    /* Initializing secret number array for user-generated option */
    if (inputArr[1] == 'u')
        convert_input(inputArr, secretNumber);

    /* Initializing secret number array for ranom generated option */
    else if (inputArr[1] == 'r')
        generate_random_number(secretNumber, (inputArr[3] - '0'));

    /* Starts the loop for guessing the number */
    guess_number(secretNumber, inputArr[1]);
}

int main()
{
    /* Getting the input from the user */
    char userInput[MAX_SIZE];
    cin.getline(userInput, MAX_SIZE);

    game_play(userInput);

    return 0;
}