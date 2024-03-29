#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

const int MAX_DIGITS = 20;

void clean_array(int *arr)
{
    for (int i = 0; i < MAX_DIGITS; i++)
        arr[i] = 0;
}

void flip_digits(int *arr, int *size)
{
    /* Function to flip the digits in the array */
    for (int k = 0; k < *size / 2; k++)
    {
        int temp = arr[k];
        arr[k] = arr[*size - 1 - k];
        arr[*size - 1 - k] = temp;
    }
}

bool input(int *numArr, int *size)
{
    /*  Function to display prompts and get input from user */
    fflush(stdin);
    int digitCount = 0;
    char ch = '\0';
    int i = 0;

    // Getting the first number
    cout << "Please enter the first number (no more than " << MAX_DIGITS << " digits)." << endl;
    cin.get(ch);
    while (ch != '\n')
    {
        if (!isdigit(ch))
        {
            cout << "non-digit entered. Please enter a valid number..." << endl;
            return false;
        }
        numArr[i] = int(ch) - int('0');
        digitCount++;
        i++;
        cin.get(ch);
    }
    if (digitCount > MAX_DIGITS)
    {
        cout << "Input number is too large. Please enter a number with 20 digits or less.";
        return false;
    }
    *size = digitCount;

    flip_digits(numArr, size);
    return true;
}

int add(int *arr1, int *arr2, int *size, int *sum)
{
    // Finding the number with the longest digits
    int longerNumber = 0;
    if (size[0] >= size[1])
        longerNumber = 0;

    else
        longerNumber = 1;

    /* Adding the terms in a loop */
    int j = 0, sumDigitCount = 0;
    for (j = size[longerNumber] - 1; j >= 0; j--)
    {
        sumDigitCount++; // Incrementing the digit count of the sum

        // Checking for integer overflow
        if (sumDigitCount >= MAX_DIGITS)
        {
            cout << "Integer overflow has occured. Setting sum to 0..." << endl;
            // exit(1);
            return -1;
        }
        // Checking if one number is greater than the other
        if (j > size[1] - 1)
            sum[j] = arr1[j];

        else if (j > size[0] - 1)
            sum[j] = arr2[j];

        else
        {
            sum[j] = arr1[j] + arr2[j];
            if (sum[j] >= 10)
            {
                sum[j + 1] += 1; // If there is a carried over term
                sum[j] = sum[j] % 10;
            }
        }
    }
    /* Checking if there is a carred over term and returning the size of the digits accordingly */
    if (sum[sumDigitCount] == 1)
        return sumDigitCount + 1;

    else
        return sumDigitCount;
}

void print_sum(int *sumArr, int *size, int *num1, int *num2)
{
    /* Function to print the addition operation and the sum */
    int longestNumber = 0;
    int sizeDiff;

    if (size[2] == -1)
    {
        cout << endl;
        return;
    }

    if (size[0] >= size[1])
        longestNumber = 0;

    else
        longestNumber = 1;

    /* Printing the first number */
    cout << "\t\t";
    for (int j = (size[longestNumber] - 1); j >= 0; j--)
    {
        if (j > size[0] - 1)
            cout << " ";

        else
            cout << num1[j];
    }
    cout << endl;

    /* Printing the second number */
    cout << "\t\t";
    for (int j = (size[longestNumber] - 1); j >= 0; j--)
    {
        if (j > size[1] - 1)
            cout << " ";
        else
            cout << num2[j];
    }
    cout << endl;

    cout << "--------------------------------------" << endl
         << "\t\t";

    /* Printing the sum */
    for (int j = size[2] - 1; j >= 0; j--)
        cout << sumArr[j];
    cout << endl;
}

void do_addition()
{
    /* Function to do the actual addition program */

    int num1[MAX_DIGITS], num2[MAX_DIGITS]; // Arrays to hold the digits of each number
    int sizes[3];                           // Array to hold the sizes of all the arrays (num1, num2, sumArray)
    int sumArray[MAX_DIGITS] = {0};         // Array to hold the sum's digits
    int sumSize = 0;

    // Getting user inputs
    bool validInput1 = input(num1, &sizes[0]);
    if (validInput1 == false)
        return;

    bool validInput2 = input(num2, &sizes[1]);
    if (validInput2 == false)
        return;

    // Adding the numbers and getting the length of the sum
    sizes[2] = add(num1, num2, sizes, sumArray);

    // Printing the sum
    print_sum(sumArray, sizes, num1, num2);
}

int main()
{
    /* Loop to do the addition */
    int go = 1;
    while (go)
    {
        cout << "=========================================================================" << endl;
        do_addition(); // Addition function

        cout << "Would you like to go again? Enter 1 for yes, 0 to terminate the program." << endl;
        cin >> go;

        // Flushing the input stream to avoid problems in the next iteration
        cin.ignore();
        fflush(stdin);
        cout << endl;
    }

    return 0;
}