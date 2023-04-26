#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Student
{
private:
    string name;
    int numClasses;
    string *classList;

public:
    /* Constructors */
    Student();                  // Default Constructor
    Student(string n, int num); // Initializing constructor
    ~Student();                 // Destructor

    /* Member Functions */

    // Setter functions
    void set_name(string s);
    void set_numClasses(int num);
    void set_classList();

    // Getter functions
    string get_name() const;
    int get_numClasses() const;
    void get_classList() const;

    void InputData();
    void OutputData() const;
    void ResetClasses();
    Student &operator=(const Student &rightSide);
};

Student::Student()
{ /* Default constructor sets everything to zero or null */
    numClasses = 0;
    classList = NULL;
    name = "";
}

Student::Student(string n, int num)
{ /* Constructor to initialize data given by the user */
    name = n;
    numClasses = num;

    classList = new string[numClasses];
}

Student::~Student()
{ /* Destructor deletes the class list only if it exists */
    if (classList != NULL)
    {
        delete[] classList;
    }
}

void Student::ResetClasses()
{ /* Function to reset classes by deleting the class list, setting it to null, and resetting number of classes */
    if (classList != NULL)
    {
        delete[] classList;
        classList = NULL;
    }
    numClasses = 0;
}

void Student::InputData()
{ /* Function to get input from the user */
    int i;
    ResetClasses();

    cout << "Enter a student's name: " << endl;
    getline(cin, name);
    cout << "Enter the number of classes they take:" << endl;
    cin >> numClasses;
    cin.ignore(2, '\n'); // Clearing buffer

    if (numClasses > 0) // Making sure the student takes at least one class
    {
        // Creating a new class list using dynamic memory from the size that the user gave
        classList = new string[numClasses];
        for (i = 0; i < numClasses; i++)
        {
            // Getting the name of each class the student takes and putting it in the class list array
            cout << "Enter name of class" << (i + 1) << endl;
            getline(cin, classList[i]);
        }
    }
    cout << endl;
}

void Student::OutputData() const
{ /* Function to display the student's name and all the classes they take */
    int i;
    cout << "Student Name: " << name << endl;
    cout << "Total classes enrolled: " << numClasses << endl;

    // Printing the classes one by one.
    for (i = 0; i < numClasses; i++)
        cout << (i + 1) << ". " << classList[i] << endl;
    cout << endl;
}

Student &Student::operator=(const Student &rValue)
{ /* Assignment operator that correctly makes a copy of the list courses */

    // If the class lists are already all the same, return the current Student object
    if (this->classList == rValue.classList)
        return *this;

    ResetClasses();                 // Resetting the classes for the current object
    name = rValue.name;             // Copying the name of the student
    numClasses = rValue.numClasses; // Copying the number of classes of hte student

    if (numClasses > 0)
    {
        classList = new string[numClasses]; // Creating a new classList array using the size given in the parameter

        // Copying all of the classes from the given lsit to the current list
        for (int i = 0; i < numClasses; i++)
            classList[i] = rValue.classList[i];
    }

    return *this;
}

void Student::set_name(string s) { name = s; }

void Student::set_numClasses(int num) { numClasses = num; }

void Student::set_classList()
{
    if (numClasses > 0 && classList != NULL) // Making sure the student takes at least one class and that there is a list created
    {
        for (int i = 0; i < numClasses; i++)
        {
            // Getting the name of each class the student takes and putting it in the class list array
            cout << "Enter name of class" << (i + 1) << endl;
            getline(cin, classList[i]);
        }
    }
    cout << endl;
}

string Student::get_name() const { return name; }

int Student::get_numClasses() const { return numClasses; }

void Student::get_classList() const
{ /*Function to get teh class list */
    for (int i = 0; i < numClasses; i++)
        cout << i + 1 << ". " << classList[i] << endl;
}

int main()
{

    cout << "TEST DATA GIVEN IN THE PDF\n========================================" << endl;
    Student s1, s2;
    s1.InputData();
    cout << "Student 1's data:" << endl;
    s1.OutputData();
    cout << endl;
    s2 = s1;
    cout << "Student 2's data after assignment from student 1:" << endl;
    s2.OutputData();

    s1.ResetClasses();
    cout << "Student 1's data after reset:" << endl;
    s1.OutputData();
    cout << "Student 2's data, should still have original classes:" << endl;
    s2.OutputData();
    cout << endl;

    cout << "TEST DATA GIVEN BY ME\n========================================" << endl;
    Student s3, s4;

    s3.InputData();
    s4.InputData();

    cout << "Student 3's data:" << endl;
    s3.OutputData();

    cout << "Student 4's data: " << endl;
    s4.OutputData();

    return 0;
}
