#include <iostream>
#include <cstdlib>
using namespace std;
namespace
{
    int lev = 0;
    void f(int throw_level)
    {
        ++lev;
        cout << "lev ==" << lev << endl;
        if (throw_level == lev)
        {
            throw lev;
        }
        else
            f(throw_level);
    }
}
int main()
{

    int depth = 10;
    int cath_level;
    cout << "Enter an exception level greater than or equal to 0 : ";
    cin >> cath_level;
    cout << endl;
    try
    {
        if (cath_level == 0)
            throw 0;
        else
            f(cath_level);
    }
    catch (int depth)
    {
        cout << "Caught exception at level " << depth << endl;
    }
    return 0;
}