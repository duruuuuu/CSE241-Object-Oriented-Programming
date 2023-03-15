#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

const int MAX_DIGITS = 20;

int split_digits(int *arr, int num)
{
    /* Function to split the digits into an array */
    int i;
    for (i = 0; num > 0; i++)
    {
        arr[i] = num % 10;
        num /= 10;
    }

    return i;
}

void input(int *num1, int *num2)
{
    /*  Function to display prompts and get input from user */
    int tempNum = 0;

    // Getting the first number
    cout << "Please enter the first number (no more than " << MAX_DIGITS << " digits)." << endl;
    cin >> tempNum;

    //  splitting the digits into array
    int num1Size = split_digits(num1, tempNum);

    /* cout << "You entered:\t";
    for (int j = num1Size - 1; j >= 0; j--)
        cout << num1[j];
    cout << endl; */

    cout << "Please enter the second number (no more than " << MAX_DIGITS << " digits)." << endl;
    cin >> tempNum;

    int num2Size = split_digits(num2, tempNum);

    /*cout << "You entered:\t";
    for (int j = num2Size - 1; j >= 0; j--)
        cout << num2[j];
    cout << endl;*/
}

int main()
{

    int num1[MAX_DIGITS], num2[MAX_DIGITS];

    input(num1, num2);
}