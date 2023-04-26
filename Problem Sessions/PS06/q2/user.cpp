#include <iostream>
#include <string>

using namespace std;
namespace
{
    string username;

    // Function chcecks whether the entered username is valid or not
    bool isValid()
    {
        if (username.length() == 8)

            return true;

        return false;
    }

}

namespace Authenticate
{
    void inputUserName()
    {
        do
        {
            cout << "Enter your username (8 letters only)" << endl;
            cin >> username;
        } while (!isValid());
    }

    string getUserName()
    {
        return username;
    }
}
