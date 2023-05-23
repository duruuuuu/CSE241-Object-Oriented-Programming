#include <iostream>
#include "PFARRAYD.H"

using std::cin;
using std::cout;
using std::endl;

void testPFArrayD();

int main()
{
    cout << "This program tests the class PFArrayD.\n";

    char ans;
    do
    {
        testPFArrayD();
        cout << "Test again? (y/n) ";
        cin >> ans;
    } while ((ans == 'y') || (ans == 'Y'));
    return 0;
}

void testPFArrayD()
{
    int cap;
    cout << "Enter capacity of this super array: ";
    cin >> cap;
    PFArrayD temp(cap);
    cout << "Enter up to " << cap << " nonnegative numbers.\n";
    cout << "Place a negative number at the end.\n";

    double next;
    cin >> next;

    while ((next >= 0) && (!temp.full()))
    {
        try
        {
            temp.addElement(next);
        }
        catch (OutOfRange e)
        {
            cout << endl
                 << e.getMessage() << " " << e.getIndex() << endl;
        }
        catch (AnotherException e)
        {
            cout << "another exception" << endl;
        }
        cin >> next;
    }

    cout << "You entered the following "
         << temp.getNumberUsed() << " numbers: \n";

    int index;
    int count = temp.getNumberUsed();

    for (index = 0; index < count; index++)
    {
        try
        {
            cout << temp[index] << " ";
            cout << endl;
            cout << "(plus a sentinel value.)\n";
        }
        catch (OutOfRange e)
        {
            cout << endl
                 << e.getMessage() << " " << e.getIndex() << endl;
        }
    }

    // Test index out of range
    try
    {
        cout << temp[-1];
    }
    catch (OutOfRange e)
    {
        cout << endl
             << e.getMessage() << " " << e.getIndex() << endl;
    }

    // Test insert beyond declared size
    try
    {
        temp.addElement(99999);
    }
    catch (OutOfRange e)
    {
        cout << endl
             << e.getMessage() << " " << e.getIndex() << endl;
    }
}
