#include <iostream>
#include <vector>

using namespace std;

class Vector2D
{
private:
    int x, y;

public:
    /* Constructors */

    Vector2D() // Default constructor
    {
        x = 0;
        y = 0;
    }

    Vector2D(int x, int y) // Constructor that takes in coordinate input
    {
        this->x = x;
        this->y = y;
    }

    /* Member functions */

    // Setter functions (mutators)
    void set_coordinates(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void set_x_coordinate(int x) { this->x = x; }
    void set_y_coordinate(int y) { this->y = y; }

    // Getter functions (accessors)
    int GetX() { return x; }
    int GetY() { return y; }
    int print_coordinates() { cout << "x: " << x << ", y: " << y << endl; }

    /* Overloaded Operators */
    const int operator*(const Vector2D &other) { return ((this->x * other.x) + (this->y * other.y)); }
};

int main()
{
    Vector2D v1(10, 0), v2(0, 10), v3(10, 10), v4(5, 4);

    cout << "(" << v1.GetX() << ", " << v1.GetY() << ") * (" << v2.GetX() << ", " << v2.GetY() << ") = " << v1 * v2 << endl;
    cout << "(" << v2.GetX() << ", " << v2.GetY() << ") * (" << v3.GetX() << ", " << v3.GetY() << ") = " << v2 * v3 << endl;
    cout << "(" << v3.GetX() << ", " << v3.GetY() << ") * (" << v4.GetX() << ", " << v4.GetY() << ") = " << v3 * v4 << endl;

    return 0;
}