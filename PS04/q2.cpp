#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class MyInteger
{
private:
    int n;

public:
    /* Constructors */
    MyInteger() { n = 0; }            // Default constructor
    MyInteger(int n) { this->n = n; } // User initialization constructor

    /* Member Functions */

    // Setter functions
    void set_integer(int n) { this->n = n; }

    // Getter functions
    int get_integer() { return n; }

    /* Overloaded Operators */
    const int operator[](int i)
    {
        int temp, count = 0;

        temp = n;
        while (temp > 10)
        {
            count++;
            temp /= 10;
        }

        if (i < 0 || count < i)
        {
            // If the index is less than 0 or if it is greater than the size of the number
            cout << "Invalid index value ";
            return -1;
        }

        else
        {
            temp = (int)(n / (pow(10, i)));
            return (temp % 10);
        }
    }
};

int main()
{
    MyInteger num(418);

    cout << num[0] << " " << num[1] << " " << num[2] << endl;
    cout << num[3] << endl;
    cout << num[-1] << endl;

    return 0;
}