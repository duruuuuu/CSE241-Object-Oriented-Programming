#include <iostream>

class Fraction
{
private:
    int numerator;
    int denominator;

public:
    // Setter functions (mutators)
    void set_numerator(int n) { numerator = n; }
    void set_denominator(int n) { denominator = n; }

    // Getter functions
    double get_value() { return (numerator * 1.0) / denominator; }
    void print_simplified_fraction()
    {
        /* Getting the greatest common factor */
        int gcd = 0;
        int n1 = numerator, n2 = denominator;
        // swapping variables n1 and n2 if n2 is greater than n1.
        if (n2 > n1)
        {
            int temp = n2;
            n2 = n1;
            n1 = temp;
        }

        for (int i = 1; i <= n2; ++i)
        {
            if (n1 % i == 0 && n2 % i == 0)
            {
                gcd = i; // setting the gcd
            }
        }

        // Getting the simplified values
        numerator /= gcd;
        denominator /= gcd;

        std::cout << numerator << "/" << denominator << std::endl;
    }
};

int main()
{
    Fraction f1; // Creating f1 object

    f1.set_numerator(2);                      // setting the numerator to 2
    f1.set_denominator(6);                    // setting the denominator to 6
    std::cout << f1.get_value() << std::endl; // printing the decimal value
    f1.print_simplified_fraction();           // printing the simplified version

    return 0;
};
