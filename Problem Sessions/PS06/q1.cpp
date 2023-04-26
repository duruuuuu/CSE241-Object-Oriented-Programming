#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

class DynamicStringArray
{
public:
    DynamicStringArray();
    DynamicStringArray(const DynamicStringArray &otherObj);
    ~DynamicStringArray();
    DynamicStringArray &operator=(const DynamicStringArray &rightSide);

    int get_size() const;
    void addEntry(string newEntry);
    bool deleteEntry(string newEntry);
    string getEntry(int index);

private:
    string *dynamicArray;
    int size;
};

// Default Constructor
DynamicStringArray::DynamicStringArray()
{
    dynamicArray = NULL;
    size = 0;
}

// Copy Constructor
DynamicStringArray::DynamicStringArray(const DynamicStringArray &other)
{
    size = other.size;
    if (size == 0)
    {
        dynamicArray = NULL;
    }

    else
    { // Copying array elements to new object manually to avoid problrms with pointers
        dynamicArray = new string[size];
        for (int i = 0; i < size; i++)
        {

            dynamicArray[i] = other.dynamicArray[i];
        }
    }
}

// Desctructor
DynamicStringArray::~DynamicStringArray()
{
    // Deleting the dynamic array only if it exists
    if (dynamicArray != NULL)
        delete[] dynamicArray;
}

// Function that returns size
int DynamicStringArray::get_size() const
{
    return size;
}

// Adds an entry to a dynamic Array
void DynamicStringArray::addEntry(string newEntry)
{
    // Function creates a new array with size one largetr than the original array,
    // Copies all elements of original array to new array and adds the new element to the end

    string *newArray = new string[size + 1];
    for (int i = 0; i < size; i++)
        newArray[i] = dynamicArray[i];

    delete[] dynamicArray; // Deleting original array
    dynamicArray = newArray;
    newArray[size++] = newEntry;
}

// Removes an entry from the dynamic array.
bool DynamicStringArray::deleteEntry(string entry)
{
    string *result = NULL;

    int pos = -1;
    for (int i = 0; (i < size) && (pos == -1); i++)
    {
        if (dynamicArray[i] == entry)
            pos = i;
    }

    // if entry not found,exit
    if (pos == -1)
    {
        return false;
    }

    // IF the size is greater than 1, create a new dynamic array of one size smaller to copy thge array without the deleted element
    if (size > 1)

        result = new string[size - 1];

    for (int i = 0, j = 0; i < size; i++)
    {
        // skip over the deleted element and copies all the elements to the new array
        if (i != pos)
        {
            result[j++] = dynamicArray[i];
        }
    }

    // Decrease size, delete original array and assign it to the new array
    size--;
    delete[] dynamicArray;
    dynamicArray = result;
    return true;
}

// Returns a specific index
string DynamicStringArray::getEntry(int index)
{
    if ((index < 0) || (index >= size))
        return NULL;
    return dynamicArray[index];
}

// Assignment operator
DynamicStringArray &DynamicStringArray::operator=(const DynamicStringArray &other)
{
    // Overload assignment operator to avoid any problems with dynamic array and pointer assignment

    // If the calling object's array is not empty, delete it
    if (this->dynamicArray != NULL)
        delete[] dynamicArray;

    // If the rhs is empty, assign teh calling object to empty and null
    if (other.size == 0)
    {
        size = 0;
        dynamicArray = NULL;
    }

    else
    {
        size = other.size;
        dynamicArray = new string[size]; // Create a new array for the calling object same size as the rhs

        // Copy all the elements to the calling object's array
        for (int i = 0; i < size; i++)
            dynamicArray[i] = other.dynamicArray[i];
    }

    return *this;
}

int main()
{
    DynamicStringArray names;

    // List of names
    names.addEntry("Frank");
    names.addEntry("Wiggum");
    names.addEntry("Nahasapeemapetilon");
    names.addEntry("Quimby");
    names.addEntry("Flanders");

    // Output list
    cout << "List of names:" << endl;
    for (int i = 0; i < names.get_size(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;

    // Add and remove some names
    names.addEntry("Spuckler");
    cout << "After adding a name:" << endl;
    for (int i = 0; i < names.get_size(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;

    names.deleteEntry("Nahasapeemapetilon");
    cout << "After removing a name:" << endl;
    for (int i = 0; i < names.get_size(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;

    names.deleteEntry("Skinner");
    cout << "After removing a name that isn't on the list:" << endl;
    for (int i = 0; i < names.get_size(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;

    names.addEntry("Muntz");
    cout << "After adding another name:" << endl;
    for (int i = 0; i < names.get_size(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;

    // Remove all of the names by repeatedly deleting the last one
    while (names.get_size() > 0)
    {
        names.deleteEntry(names.getEntry(names.get_size() - 1));
    }

    cout << "After removing all of the names:" << endl;
    for (int i = 0; i < names.get_size(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;

    names.addEntry("Burns");
    cout << "After adding a name:" << endl;
    for (int i = 0; i < names.get_size(); i++)
        cout << names.getEntry(i) << endl;
    cout << endl;

    cout << "Testing copy constructor" << endl;
    DynamicStringArray names2(names);
    // Remove Burns from names
    names.deleteEntry("Burns");
    cout << "Copied names:" << endl;
    for (int i = 0; i < names2.get_size(); i++)
        cout << names2.getEntry(i) << endl;
    cout << endl;

    cout << "Testing assignment" << endl;
    DynamicStringArray names3 = names2;
    // Remove Burns from names2
    names2.deleteEntry("Burns");
    cout << "Copied names:" << endl;
    for (int i = 0; i < names3.get_size(); i++)
        cout << names3.getEntry(i) << endl;
    cout << endl;

    cout << "Enter a character to exit." << endl;
    char wait;
    cin >> wait;
    return 0;
}