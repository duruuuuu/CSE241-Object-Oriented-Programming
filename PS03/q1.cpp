#include <iostream>

using namespace std;

class Coordinates
{
private:
    double x;
    double y;

public:
    // Setter functions (mutators)
    void set_coordinates(double a, double b)
    {
        x = a;
        y = b;
    }

    void set_x_coordinate(double a) { x = a; }
    void set_y_coordinate(double b) { y = b; }

    // Function to move the points to a specified distance
    void move_distance(double a, double b)
    {
        /* QUESTION!!! should the coordinates move from a certain
        point or set a new point */
        x += a;
        y += b;
    }

    // Function to rotate 90 degrees
    void rotate_90_degrees()
    {
        double tempX = x, tempY = y;

        x = tempY;
        y = tempX * (-1.0);
    }

    double get_x_coordinate() const { return x; }
    double get_y_coordinate() const { return y; }
};

int main()
{
    Coordinates c1;

    c1.set_coordinates(3, 7);
    cout << c1.get_x_coordinate() << "," << c1.get_y_coordinate() << endl;
    c1.move_distance(0, 3);
    cout << c1.get_x_coordinate() << "," << c1.get_y_coordinate() << endl;
    c1.rotate_90_degrees();
    cout << c1.get_x_coordinate() << "," << c1.get_y_coordinate() << endl;
}