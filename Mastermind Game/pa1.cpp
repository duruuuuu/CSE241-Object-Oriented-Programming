#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SIZE = 12;        // Constant for the maximum size of arrays
const int SENT_VAL = -999;      // Sentinal value to mark the end of the number in the integer arrays
const int MAX_TURNS = 100;      // Maximum number of iterations for guessing the secret number
const int GENERATION_INDEX = 1; // number of hte index in which the genersation type will be in the user input array

void clean_array(char arr[])
{ /* Function to clean the character array to make sure there are no complications in a loop/buffer */

    for (int i = 0; i < MAX_SIZE; i++)
        arr[i] = '\0'; // Filling the entire loop with a null character
}

void clean_array(int arr[])
{ /* Function to clean the integer array to make sure there are no complications in a loop/buffer */

    for (int i = 0; i < MAX_SIZE; i++)
        arr[i] = SENT_VAL; // Filling the entire loop with a sentinal value
}

void generate_random_number(int nums[], int length)
{ /* function to generate a random number of length given by the user */

    srand(time(0));

    for (int i = 0; i < length; i++)
    {
        bool isUnique = false;
        int randomNumber;

        while (!isUnique)
        {
            // Making sure that the first digit is never zero
            if (i == 0)
                randomNumber = 1 + (rand() % 10);

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

    // Assigning a sentinal value to the rest of the number to mark the end of the number
    for (int i = length; i < MAX_SIZE; i++)
        nums[i] = SENT_VAL;
}

int find_exact_digits(int secretNum[], int guess[])
{ /* Funtion to find the exact correct spot in the guessed number of the user */

    int count = 0;

    for (int i = 0; guess[i] != SENT_VAL; i++)
    { // If the number in the same index is equal, increment the count
        if (secretNum[i] == guess[i])
            count++; // If the digit in the secretnumber and guess array are the same in the same index, increment count
        else
            continue;
    }

    return count;
}

int find_misplaced_digits(int secretNum[], int guess[])
{ /* Function to find the misplaced digits in the guess of the user */

    int count = 0;
    for (int i = 0; secretNum[i] != SENT_VAL; i++)
    {
        for (int j = 0; guess[j] != SENT_VAL; j++)
        { // If the number in diffferent indices are equal, increment the count
            if ((i != j) && (secretNum[i] == guess[j]))
                count++;

            else
                continue;
        }
    }

    return count;
}

void check_user_input(char inputArr[])
{ /* Function to error check the user input at the start of the game */

    // Checking if the user entered a valid generation type (r or u)
    if (inputArr[GENERATION_INDEX] != 'r' && inputArr[GENERATION_INDEX] != 'u')
    {
        cout << "E0" << endl;
        exit(1);
    }

    // If the random number generator is followed by a 0 or negative number
    if (inputArr[GENERATION_INDEX] == 'r')
    {
        char enteredDigit = inputArr[2];            // assigning single character to entered no of digits
        int entered_digit_num = enteredDigit - '0'; // converting the character to an integer
        if (entered_digit_num < 1 || entered_digit_num > 9)
        {
            // If the entered value is not valid
            cout << "E0" << endl;
            exit(1);
        }

        else if (inputArr[3] != '\0')
        {
            // If the user entered a number larger than 9
            //(If the index 3 for the input array is not a null value, it means that the user entered a 2 digit number aka >9)
            cout << "E0" << endl;
            exit(1);
        }
    }

    // If the user generated number has digits which are not unique
    else if (inputArr[GENERATION_INDEX] == 'u')
    {
        for (int i = 2; inputArr[i] != '\0'; i++)
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

        // If the user enters a secret number whose left most digit is a zero (but the secret number itself is not just a single digit zero)
        if ((inputArr[2] == '0') && (inputArr[3] != '\0'))
        {
            cout << "E0" << endl;
            exit(1);
        }
    }
}

void check_user_input(int inputArr[], int secretNumber[])
{ /* Function to check the user input while guessing the secret number*/

    // keeping track of the sizes of the secret number and guessed number
    int secretNumberSize = 0;
    int inputNumberSize = 0;

    /* Couting the digits of the secret number and guessed number */
    for (int i = 0; i < MAX_SIZE; i++)
    { // Incrementing the size variables until we reach the sentinal value which marks the end of the number
        if (secretNumber[i] != -999)
            secretNumberSize++;

        if (inputArr[i] != -999)
            inputNumberSize++;
    }

    /* Checks if the input is a valid character (if it is between 0-9 and making sure it is a digit)*/
    for (int i = 0; i < inputNumberSize; i++)
    {
        if (inputArr[i] > 9 || inputArr[i] < 0)
        {
            cout << "E2" << endl;
            exit(1);
        }
    }

    /* Checks if the input has a valid number of digits
       (making sure the guessed number has an equal # of digits as the secret number )*/
    if (secretNumberSize != inputNumberSize)
    {
        cout << "E1" << endl;
        exit(1);
    }

    /* Checks to see if there are any repeating numbers*/
    for (int i = 0; i < inputNumberSize; i++)
    {
        for (int j = i + 1; j < inputNumberSize; j++)
        {
            if (inputArr[i] == inputArr[j])
            {
                cout << "E0" << endl;
                exit(1);
            }
        }
    }
}

void convert_input(char inputArr[], int numArr[])
{ /* Function to convert the input numbers from type char to type int */
    /* THIS FUNCTION IS USED FOR THE INITIAL -U CALL */

    // i starts from 3 because the secret number begins on the 3rd index of the character array
    int i;
    for (i = 2; inputArr[i] != '\0'; i++)
        numArr[i - 2] = (inputArr[i] - '0');

    // Filling the rest of the integer array with a sentinal value to mark the end of the secret number
    for (i -= 2; i < MAX_SIZE; i++)
        numArr[i] = SENT_VAL;
}

void convert_input(int numArr[], char inputArr[])
{ /* Function to convert the input of the guessed number */
    /* THIS FUNCTION IS USED TO CONVERT THE NUMBER ENTERED WHILE GUESSING */

    int i;
    for (i = 0; inputArr[i] != '\0'; i++)
        numArr[i] = (inputArr[i] - '0');

    // Filling the rest of the array with a sentinal value to mark the end of the array
    for (; i < MAX_SIZE; i++)
        numArr[i] = SENT_VAL;
}

int get_secret_number_size(int secretNumber[])
{ /* Function to get the number of digits in the secret number */
    int i;
    for (i = 0; secretNumber[i] != SENT_VAL; i++)
    {
        ; // Just incrementingg i until the loop hits the sentinal value
    }

    return i;
}

void guess_number(int secretNumber[], char generationType)
{ /* Function to implement the loop for guessing the number */

    // Arrays to hold the input guess numbers
    char inputCh[MAX_SIZE];
    int inputN[MAX_SIZE];

    // cleaning arrays to make sure they have proper null values and sentinal values
    clean_array(inputCh);
    clean_array(inputN);

    int iteration = 0;                                           // keeps track of the number of iterations for guessing
    int secretNumberSize = get_secret_number_size(secretNumber); // Getting the size of the secret number

    /* User starts guessing the number */
    while (iteration < MAX_TURNS)
    {
        char inputCh[MAX_SIZE];

        iteration++; // keeping track of teh iteration count, loop goes on while it is less that the max # of turns

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
            // If the number of exact digits found is the same as the number of digits in the secret nubmer
            cout << "FOUND " << iteration << endl;
            exit(1);
        }

        // Printing the exact and misplaced digits
        cout << exactDigits << " " << misplacedDigits << endl;

        /* Flushing the arrays manually so there are no problems with buffer or loop */
        clean_array(inputCh);
        clean_array(inputN);
    }

    /* If the user loses, display the correct secret number */
    if (iteration == MAX_TURNS)
        cout << "FAILED" << endl;
}

void game_play(char inputArr[])
{
    // Checking user input for errors
    check_user_input(inputArr);

    int secretNumber[MAX_SIZE]; // array to hold the secret number

    /* Initializing secret number array for user-generated option */
    if (inputArr[1] == 'u')
        convert_input(inputArr, secretNumber);

    /* Initializing secret number array for ranom generated option */
    else if (inputArr[1] == 'r')
        generate_random_number(secretNumber, (inputArr[2] - '0'));

    /* Starts the loop for guessing the number */
    guess_number(secretNumber, inputArr[1]);
}

int main(int argc, char **argv)
{
    /* Getting the input from the user */
    char userInput[MAX_SIZE];
    clean_array(userInput); // Cleaning array to avoid any problems with the buffer of the array

    // Transferring the initial command line input to a local array
    int k = 0;
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            userInput[k] = argv[i][j];
            k++;
        }
    }

    // Starting the game
    game_play(userInput);

    return 0;
}