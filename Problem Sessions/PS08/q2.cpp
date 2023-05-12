#include <iostream>
#include <string>
#include <vector>

template <typename T1, typename T2>
class Pair
{
private:
    T1 first;
    T2 second;

public:
    Pair(const T1 &_1st, const T2 &_2nd) : first(_1st), second(_2nd) {}

    void setFirst(const T1 &newFirst)
    {
        first = newFirst;
    }

    void setSecond(const T2 &newSecond)
    {
        second = newSecond;
    }

    T1 getFirst() const
    {
        return first;
    }

    T2 getSecond() const
    {
        return second;
    }
};

int main()
{
    Pair<char, char> p('A', 'B');
    std::cout << "First is " << p.getFirst() << std::endl;
    p.setFirst('Z');
    std::cout << "First changed to " << p.getFirst() << std::endl;
    std::cout << "The pair is: " << p.getFirst() << ", " << p.getSecond() << std::endl;

    Pair<int, std::string> p2(34, "Bill");
    Pair<std::string, int> p3("Bill", 34);
    std::cout << "The pair is: " << p2.getFirst() << ", " << p2.getSecond() << std::endl;

    std::cout << "\nMY OWN EXAMPLE: " << std::endl;

    Pair<std::string, std::string> p4("Meep", "Moop");
    Pair<std::string, bool> p5("I like chocolate", true);
    Pair<int, std::vector<std::string>> p6(123, {"one", "two", "three"});

    std::cout << "First Pair: " << p4.getFirst() << ", " << p4.getSecond() << std::endl;
    std::cout << "Second Pair: " << p5.getFirst() << ", " << p5.getSecond() << std::endl;
    std::cout << "Third Pair: " << p6.getFirst() << ", ";
    for (size_t i = 0; i < p6.getSecond().size(); i++)
        std::cout << p6.getSecond().at(i) << " ";
    std::cout << std::endl;

    p6.setFirst(241);
    p6.setSecond({"two", "four", "one"});

    std::cout << "Modified pair:" << std::endl;
    std::cout << p6.getFirst() << ", ";
    for (size_t i = 0; i < p6.getSecond().size(); i++)
        std::cout << p6.getSecond().at(i) << " ";
    std::cout << std::endl;

    return 0;
}
