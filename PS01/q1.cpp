#include <iostream>

void printPrime(const int min, const int max)
{
    /* Function to find and print prime numbers within  */

    int n = min;         // local variable to track the current number
    bool isPrime = true; // bool variable to check if a numbe is prime or not
    while (n <= max)
    {
        isPrime = true;
        for (int i = 2; i < n; i++)
        {
            if (n % i == 0)
            {
                // if the number is not prime, we exit the inner loop
                isPrime = false;
                break;
            }
        }
        // We print the nubmer if it is prime
        if (isPrime)
            std::cout << n << std::endl;

        // Increment the local variable that tracks our current number
        n++;
    }
}

int main()
{
    // Constant variables that can be changed depending on what you want your range to be
    const int upperLimit = 100;
    const int lowerLimit = 3;

    std::cout << "PRINTING PRIME NUMBERS FROM " << lowerLimit << " TO " << upperLimit << std::endl;

    // Calling function that prints the prime numbers in the given range
    printPrime(lowerLimit, upperLimit);

    return 0;
}