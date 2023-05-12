#include <iostream>

template <typename T>
class Set
{
private:
    T *items;     // Dynamically allocated array to store items
    int size;     // Number of items in the set
    int capacity; // Capacity of the array

public:
    Set()
    {
        capacity = 10; // Initial capacity
        size = 0;
        items = new T[capacity];
    }

    ~Set()
    {
        delete[] items;
    }

    void add(const T &item)
    {
        // Check if item already exists in the set
        for (int i = 0; i < size; i++)
        {
            if (items[i] == item)
            {
                return; // Item already in the set, do nothing
            }
        }

        // If the array is full, resize it
        if (size == capacity)
        {
            capacity *= 2;
            T *newItems = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                newItems[i] = items[i];
            }
            delete[] items;
            items = newItems;
        }

        // Add the new item to the set
        items[size] = item;
        size++;
    }

    int getSize() const
    {
        return size;
    }

    T *getArray() const
    {
        T *newArray = new T[size];
        for (int i = 0; i < size; i++)
        {
            newArray[i] = items[i];
        }
        return newArray;
    }
};

int main()
{
    Set<int> s1;
    Set<std::string> s2;
    int *intArray = nullptr;
    std::string *stringArray = nullptr;
    int i;

    // Add some sample integers to the set
    s1.add(10);
    s1.add(20);
    s1.add(15);
    s1.add(20);
    intArray = s1.getArray();
    std::cout << "Set one has " << s1.getSize() << " items. Here they are:\n";
    for (i = 0; i < s1.getSize(); i++)
    {
        std::cout << intArray[i] << '\n';
    }
    if (intArray != nullptr)
    {
        delete[] intArray;
    }

    // Add some sample strings to the set
    s2.add("butter");
    s2.add("hamburgers");
    s2.add("pizza");
    s2.add("hotdogs");
    s2.add("pizza");
    stringArray = s2.getArray();
    std::cout << "Set two has " << s2.getSize() << " items. Here they are:\n";
    for (i = 0; i < s2.getSize(); i++)
    {
        std::cout << stringArray[i] << '\n';
    }
    if (stringArray != nullptr)
    {
        delete[] stringArray;
    }

    std::cout << "\nMY OWN EXAMPLES: " << std::endl;
    Set<double> s3;
    double *doubleArray = nullptr;

    s3.add(3.14);
    s3.add(5.334);
    s3.add(7.77);
    s3.add(3.14);

    doubleArray = s3.getArray();
    std::cout << "Set 3 has " << s3.getSize() << " items. Here they are:" << std::endl;
    for (int i = 0; i < s3.getSize(); i++)
        std::cout << doubleArray[i] << std::endl;

    if (doubleArray != nullptr)
        delete[] doubleArray;

    return 0;
}
