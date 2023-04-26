#include <iostream>
#include <string>
#include <cctype>

using namespace std;

namespace
{
    string password;

    // // Function checks if the username is valid
    bool isValid()
    {
        bool hasNonAlpha = false;
        if (password.length() >= 8)
        {
            for (size_t i = 0; i < password.length(); i++)
            {
                if ((password[i] < 'A' || password[i] > 'Z') && (password[i] < 'a' || password[i] > 'z'))
                {
                    hasNonAlpha = true;
                    break;
                }
            }
        }
        return hasNonAlpha;
    }
}

namespace Authenticate
{
    void inputPassword()
    {
        do
        {
            cout << "Enter your password (at least 8 characters "
                 << "and at least one non-letter)" << endl;
            cin >> password;
        } while (!isValid());
    }
    string getPassword()
    {
        return password;
    }
}