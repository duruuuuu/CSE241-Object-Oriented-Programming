/* missing: overflow warning, printing the first digit if sum  is longer than longest number*/

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

void input(int *num1, int *num2, int *size)
{
    /*  Function to display prompts and get input from user */
    int tempNum = 0;
    // int size[2];

    // Getting the first number
    cout << "Please enter the first number (no more than " << MAX_DIGITS << " digits)." << endl;
    cin >> tempNum;

    //  splitting the digits into array
    size[0] = split_digits(num1, tempNum);

    cout << "Please enter the second number (no more than " << MAX_DIGITS << " digits)." << endl;
    cin >> tempNum;

    size[1] = split_digits(num2, tempNum);
}

int add(int *arr1, int *arr2, int *size, int *sum)
{
    int longerNumber = 0;

    if (size[0] >= size[1])
        longerNumber = 0;

    else
        longerNumber = 1;
    int j = 0;
    for (j = size[longerNumber] - 1; j >= 0; j--)
    {
        if (j > size[1] - 1)
            sum[j] = arr1[j];

        else if (j > size[0] - 1)
            sum[j] = arr2[j];

        else
        {
            sum[j] = arr1[j] + arr2[j];
            if (sum[j] >= 10)
            {
                sum[j + 1] += 1;
                sum[j] = sum[j] % 10;
            }
        }
    }
    return j;
}

void print_sum(int *sumArr, int *size, int *num1, int *num2)
{
    /* Function to print the addition operation and the sum */
    int longestNumber = 0;
    int sizeDiff;
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

    cout << "-----------------------------------------------" << endl
         << "\t\t";

    /* Printing the sum */
    for (int j = size[longestNumber] - 1; j >= 0; j--)
        cout << sumArr[j];
    cout << endl;
}

int main()
{
    int num1[MAX_DIGITS], num2[MAX_DIGITS];
    int sizes[2];
    int sumArray[MAX_DIGITS] = {0};
    int sumSize = 0;

    input(num1, num2, sizes);
    sumSize = add(num1, num2, sizes, sumArray);
    print_sum(sumArray, sizes, num1, num2);
}