#include <iostream>

using namespace std;
double get_larger_size(double lValue, double rValue);

class Polynomial
{
private:
    double *coeffient;
    int size;

public:
    /* Constructors */
    Polynomial();                               // Deafult constructor
    Polynomial(const Polynomial &);             // Copy constructor
    Polynomial(double coefficient[], int size); // Parametrized Constructor
    ~Polynomial();                              // Destructor

    /* Member Functions */
    int get_size();

    /* Overloaded Operators */
    const Polynomial &operator=(const Polynomial &rValue);
    double &operator[](int degree);
    const double &operator[](int degree) const;

    /* friend functions / overloaded operators */
    friend double evaluate(const Polynomial &ploy, double arg);
    friend Polynomial operator+(const Polynomial &lValue, const Polynomial &rValue);
    friend Polynomial operator-(const Polynomial &lValue, const Polynomial &rValue);
    friend Polynomial operator*(const Polynomial &lValue, const Polynomial &rValue);
};

Polynomial::Polynomial()
{ /* Default constructor creates an empty polynomial */
    coeffient = 0;
    size = 0;
}

Polynomial::Polynomial(const Polynomial &rValue)
{ /* Copy Constructor */
    size = rValue.size;

    // Creating a new coefficient array usingt he one given as a parameter
    coeffient = new double[rValue.size];

    // Copying all of the right hand side values to a new coefficient array
    for (int i = 0; i < rValue.size; i++)
        coeffient[i] = rValue.coeffient[i];
}

Polynomial::Polynomial(double coefficient[], int newSize)
{ /* Parametrized constructor to create an arbitrary polynomial */

    size = newSize;

    // Creating a new coefficient array with the given array in the parameter
    this->coeffient = new double[size];

    // Copying all the given array contents to the new coefficient array
    for (int i = 0; i < size; i++)
        this->coeffient[i] = coefficient[i];
}

Polynomial::~Polynomial() { delete[] coeffient; } // Decconstructor to delete the coefficients array

int Polynomial::get_size() { return size; } // Function to return size

const Polynomial &Polynomial::operator=(const Polynomial &rValue)
{ /* Equals operator to assign the given parameter data to a new polynomial variable */

    // If the coefficients given in the parameter are already the same as our current coefficient
    if (rValue.coeffient == coeffient)
        return rValue;

    else
    {
        // Delete the current coefficient to create a new one
        delete[] coeffient;
        coeffient = new double[rValue.size];

        // Copy all of the given coefficient values from the parameter to our newly created array
        for (int i = 0; i < rValue.size; i++)
            coeffient[i] = rValue.coeffient[i];

        size = rValue.size;
    }

    return rValue;
}

const double &Polynomial::operator[](int degree) const { return coeffient[degree]; }

double &Polynomial::operator[](int degree) { return coeffient[degree]; }

Polynomial operator+(const Polynomial &lValue, const Polynomial &rValue)
{ /* Operator + to add two Polynomials together */

    Polynomial retVal;

    // Getting the polynomial with the larger size as a reference to use for the sum polynomial
    int sizeMax = get_larger_size(lValue.size, rValue.size);
    double *sumCoefs = new double[sizeMax];

    // adding all the coefficient values
    for (int i = 0; i < sizeMax; i++)
        sumCoefs[i] = lValue.coeffient[i] + rValue.coeffient[i];

    // Assigning our new values to our returning value polynomial
    retVal.coeffient = sumCoefs;
    retVal.size = sizeMax;

    return retVal;
}

Polynomial operator-(const Polynomial &lValue, const Polynomial &rValue)
{ /* Operator to subtract two polynomial coefficients */

    Polynomial retVal;

    // Getting the polynomial with the larger size as a reference to use for the sum polynomial
    int sizeMax = get_larger_size(lValue.size, rValue.size);
    double *diffCoefs = new double[sizeMax];

    // adding all the coefficient values
    for (int i = 0; i < sizeMax; i++)
        diffCoefs[i] = lValue.coeffient[i] - rValue.coeffient[i];

    // Assigning our new values to our returning value polynomial
    retVal.coeffient = diffCoefs;
    retVal.size = sizeMax;

    return retVal;
}

Polynomial operator*(const Polynomial &lValue, const Polynomial &rValue)
{ /* Operator to multiply two coefficients */

    Polynomial retVal;

    int prodSize = (lValue.size + rValue.size) - 1;
    double *prodCoefs = new double[prodSize];

    for (int i = 0; i < prodSize; i++)
        prodCoefs[i] = 0;

    for (int i = 0; i < lValue.size; i++)
        for (int j = 0; j < rValue.size; j++)
            prodCoefs[i + j] += lValue[i] * rValue[j];

    retVal.coeffient = prodCoefs;
    retVal.size = prodSize;

    return retVal;
}

double evaluate(const Polynomial &poly, double constantVal)
{ /* Function to evaluate polynomial as a value of type double */

    double value = 0;

    // Starting from the end of the polynomial (The highest degree),
    // adding all of hte terms together while multiplying the given constant term
    for (int i = poly.size - 1; i >= 0; i--)
    {
        int constant = 1;
        for (int j = 0; j < i; j++)
            constant *= constantVal;

        value += poly[i] * constant;
    }

    return value;
}

double get_larger_size(double lValue, double rValue)
{
    if (lValue > rValue)
        return lValue;

    else
        return rValue;
}

int main()
{
    Polynomial empty;
    double one[] = {1};
    Polynomial One(one, 1);
    double quad[] = {3, 2, 1};
    double cubic[] = {1, 2, 0, 3};
    Polynomial q(quad, 3);
    Polynomial c(cubic, 4);
    Polynomial p = q;
    Polynomial r;
    r = q;
    r = c;

    cout << "TEST DATA GIVEN IN THE PDF\n====================================" << endl;
    cout << "Polynomial q" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "term with degree " << i << " has coefficient " << q[i] << endl;
    }

    cout << "Polynomial c" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "term with degree " << i << " has coefficient " << c[i] << endl;
    }

    cout << "Value of q(2) is  " << evaluate(q, 2) << endl;
    cout << "Value of p(2) is  " << evaluate(p, 2) << endl;
    cout << "Value of r(2) is  " << evaluate(r, 2) << endl;
    cout << "Value of c(2) is  " << evaluate(c, 2) << endl;

    r = q + c;
    cout << "Value of (q + c)(2) is " << evaluate(r, 2) << endl;
    r = q - c;
    cout << "value of (q - c)(2) is " << evaluate(r, 2) << endl;
    r = q * c;
    cout << "size of q*c is " << r.get_size() << endl;
    cout << "Polynomial r (= q * c) " << endl;

    for (int i = 0; i < r.get_size(); i++)
        cout << "term with degree " << i << " has coefficient " << r[i] << endl;
    cout << "value of (q * c)(2) is " << evaluate(r, 2) << endl;

    cout << "\n\nTEST DATA GIVEN BY ME\n====================================" << endl;
    double quadMine[] = {5, 9, 3};
    double cubicMine[] = {8, 6, 4, 2};
    Polynomial qMine(quadMine, 3);
    Polynomial cMine(cubicMine, 4);

    cout << "Polynomial q" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "term with degree " << i << " has coefficient" << qMine[i] << endl;
    }

    cout << "Polynomial c" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "term with degree " << i << " has coefficient " << cMine[i] << endl;
    }

    cout << "Value of q(5) is  " << evaluate(qMine, 5) << endl;
    cout << "Value of c(5) is  " << evaluate(cMine, 5) << endl;

    Polynomial f;
    f = qMine + cMine;
    cout << "Value of (q + c)(2) is " << evaluate(r, 2) << endl;
    f = qMine - cMine;
    cout << "value of (q - c)(2) is " << evaluate(r, 2) << endl;
    f = qMine * cMine;
    cout << "size of q*c is " << f.get_size() << endl;
    cout << "Polynomial f (= q * c) " << endl;

    for (int i = 0; i < f.get_size(); i++)
        cout << "term with degree " << i << " has coefficient " << f[i] << endl;

    cout << "value of (q * c)(2) is " << evaluate(f, 2) << endl;

    return 0;
}
