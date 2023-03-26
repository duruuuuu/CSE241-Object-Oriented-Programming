#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Image
{
private:
    string filename;

public:
    // Constructors

    // Member Functions
    void set_image_filename();
};

void Image::set_image_filename()
{
    /* Member functino to enter and set the filename of the image */
    string s;
    cout << "Enter the filename (Please make sure to enter the full filename including the extension type): ";
    cin >> s;

    this->filename = s;
}

int save_image_menu()
{
    cout << "SAVE IMAGE DATA MENU: " << endl;
    cout << "0 - Up" << endl;
    cout << "1 - Enter A Filename" << endl;

    int n;
    cin >> n;
    return n;
}

int scripts_menu()
{
    cout << "SCRIPTS MENU: " << endl;
    cout << "0 - Up" << endl;
    cout << "1 - Convert to Grayscale (D)" << endl;

    int n;
    cin >> n;
    return n;
}

int open_image_menu()
{
    cout << "OPEN AN IMAGE MENU: " << endl;
    cout << "0 - Up" << endl;
    cout << "1 - Enter the Name of the Image" << endl;

    int n;
    cin >> n;
    return n;
}

int display_menu()
{
    cout << "MAIN MENU: " << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Open An Image (D)" << endl;
    cout << "2 - Save Image Data" << endl;
    cout << "3 - Scripts" << endl;

    int n;
    cin >> n;
    return n;
}

int main()
{
    Image i;
    int input = display_menu();

    while (input)
    {
        int input2 = 0;
        if (input == 1)
        {
            input2 = open_image_menu();

            if (input2 == 1)
                // Todo
                ;
        }

        else if (input == 2)
        {
            input2 = save_image_menu();

            if (input2 == 1)
                ;
        }

        else if (input == 3)
        {
            input2 = scripts_menu();

            if (input2 == 1)
                ;
        }

        input = display_menu();
    }
}