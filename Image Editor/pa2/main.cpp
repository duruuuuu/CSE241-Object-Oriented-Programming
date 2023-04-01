#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/********* PIXEL CLASS *********/
class Pixel
{ /* Class to store the coilor values of each pixel in the image  */
private:
    int r, g, b; // integer values for red, green, and blue pixels

public:
    Pixel();                             // Default constructor
    Pixel(int red, int green, int blue); // Constructor which initializes the pixel colors
    Pixel(int red);

    // Setter functions
    void set_pixel_values(int red, int green, int blue);
    void set_red_pixel(int red);
    void set_green_pixel(int green);
    void set_blue_pixel(int blue);

    // Getter functions
    int get_red_pixel();
    int get_green_pixel();
    int get_blue_pixel();
};

Pixel::Pixel() // Default constructor
{
    r = 0;
    g = 0;
    b = 0;
}

Pixel::Pixel(int red, int green, int blue) // Constructor which initializes the pixel colors
{
    r = red;
    g = green;
    b = blue;
}

// Setter functions for individual pixel values
void Pixel::set_red_pixel(int red) { r = red; }

void Pixel::set_green_pixel(int green) { g = green; }

void Pixel::set_blue_pixel(int blue) { b = blue; }

// Getter functions to get the individual pixel values
int Pixel::get_red_pixel() { return r; }

int Pixel::get_green_pixel() { return g; }

int Pixel::get_blue_pixel() { return b; }

void Pixel::set_pixel_values(int red, int green, int blue) // Function to set the pixel values
{
    r = red;
    g = green;
    b = blue;
}

/********* IMAGE CLASS *********/
class Image
{ /* Class to store the image and its file information */
private:
    // stores the name of the file
    string filename;

    // Colour channel coefficients
    float c_r;
    float c_g;
    float c_b;

    // FILE HEADER INFORMATION
    string magicNumber; // Magic number aka image type
    int height;         // Row count
    int width;          // Coloumn count
    int maxColorVal;    // Max color value of the image pixels

    const int magicNumberIndex = 0;
    const int heightIndex = 1;
    const int widthIndex = 2;
    const int maxColorIndex = 3;
    const int pixelStartIndex = 4;

    // vector of type Pixel to hold the pixel values of the image
    vector<vector<Pixel>> pixelVector;

    /* PRIVATE MEMBER FUNCTIONS */
    void store_pixel_values(vector<string> &fileVector);                   // For copying the pixel values from the file to the vector
    int calculate_grayscale_values(int i, int j);                          // For calculating the greyscale values according to the coefficient channels
    void delete_comments(ifstream &imageFile, vector<string> &fileVector); // Function to delete any comments from the file
    void check_fileheader(vector<string> &fileVector);                     // Function for chekcing the file for errors
    void set_image_filename(string s);                                     // Setter function to set the image's filename
    void set_coefficient_channels(float red, float green, float blue);     // Setter function for the coefficient values
    void set_magic_number(string s);
    void set_height(int h);
    void set_width(int w);
    void set_height_width(int h, int w);
    void set_max_color_value(int maxColor);

public:
    // Constructors
    Image();                                // Default Constructor
    Image(string s);                        // Constructor which initializes the filename
    Image(int row, int col, int maxColour); // Initializes height, width, and max color value

    // Member Functions
    string get_filename();
    int open_image_file();
    void convert_to_greyscale(float r, float b, float c);
    void save_as_file();
};

Image::Image()
{ // Default constructor sets filename to null for error checking when trying to modify a file
    filename = "\0";
}

Image::Image(string s)
{ // Constructor which initializes filenames

    filename = s;
    /*
    set_image_filename(s);

    // If teh file could not be opened
    ifstream imageFile(filename);
    if (!imageFile.is_open())
    {
        cerr << "Failed to open file." << endl;
        return;
    }

    vector<string> fileVector;
    delete_comments(imageFile, fileVector); // Checking the file for comments and deleting them
    pixelVector.clear();                    // Clearing the vector to make sure the last opened imnage is deleted
    store_pixel_values(fileVector);         // Copy the pixel values to local object vector

    imageFile.close(); // closing file
    */
}

Image::Image(int row, int col, int maxColour)
{ // Constructor which initializes header information
    height = row;
    width = col;
    maxColorVal = maxColour;
}

void Image::set_image_filename(string s) { filename = s; } // Setter function for filename

string Image::get_filename() { return filename; } // Getter function for filiename

void Image::set_magic_number(string s) { magicNumber = s; }

void Image::set_height(int h) { height = h; }

void Image::set_width(int w) { width = w; }

void Image::set_height_width(int h, int w)
{
    height = h;
    width = w;
}

void Image::set_max_color_value(int maxColor) { maxColorVal = maxColor; }

void Image::set_coefficient_channels(float red, float green, float blue)
// setter funcion for coefficient values
{
    c_r = red;
    c_g = green;
    c_b = blue;
}

void Image::delete_comments(ifstream &imageFile, vector<string> &fileVector)
{ /*
     Function creates a temporary string vector that takes in the original image file
     and stores it without the comments, if any.
 */

    // Read the file line by line
    string line;
    while (getline(imageFile, line))
    {
        // Do not store the line if it starts with a # symbol (comment line)
        if (line[0] == '#')
            continue;

        size_t position = 0;
        while (position < line.size())
        {
            size_t start = line.find_first_not_of(" \t\r\n", position);

            if (start == string::npos)
                break;

            size_t end = line.find_first_of(" \t\r\n", start + 1);
            if (end == string::npos)
                end = line.size();

            fileVector.push_back(line.substr(start, end - start));
            position = end;
        }
    }
}

void Image::check_fileheader(vector<string> &fileVector)
{ /* Function for error-checking the file header and making sure the file is of correct format */

    // Store header information in the object variables
    magicNumber = fileVector[magicNumberIndex];
    height = stoi(fileVector[heightIndex]);
    width = stoi(fileVector[widthIndex]);
    maxColorVal = stoi(fileVector[maxColorIndex]);

    /* If the magic number is wrong */
    if (magicNumber != "P3")
    {
        cerr << "Invalid image format" << endl; // Display error message
        return;
    }
}

void Image::store_pixel_values(vector<string> &fileVector)
{ /* Function to copy the pixel values from the file and store them in the image object's vector*/

    // Making sure there are no errors or invalid data in the header of the file
    check_fileheader(fileVector);

    int rIndex = pixelStartIndex, gIndex = pixelStartIndex + 1, bIndex = pixelStartIndex + 2;

    // Copying the pixel values to the object's vector
    for (int i = 0; i < height; i++)
    {
        vector<Pixel> innerVector; // Creating a temporary vector for the 2nd dimension of the array
        innerVector.resize(width); // Re-sizing the vector according to the width count

        for (int j = 0; j < width; j++)
        {
            // Creating a temporary pixel object and assigning it to the inner vector
            int r, g, b;
            r = stoi(fileVector[rIndex]);
            g = stoi(fileVector[gIndex]);
            b = stoi(fileVector[bIndex]);
            Pixel temp(r, g, b);
            innerVector[j] = temp;

            // Incrementing pixel value indices
            rIndex += 3;
            gIndex += 3;
            bIndex += 3;
        }

        pixelVector.push_back(innerVector);
    }
}

int Image::open_image_file()
{ /*transfer to construcotr*/
    string s;
    cin >> s;
    filename = s;
    set_image_filename(s);

    // If teh file could not be opened
    ifstream imageFile(filename);
    if (!imageFile.is_open())
    {
        cerr << "Failed to open file." << endl;
        set_image_filename("\0");
        return 0;
    }

    vector<string> fileVector;
    delete_comments(imageFile, fileVector); // Checking the file for comments and deleting them
    pixelVector.clear();                    // Clearing the vector to make sure the last opened imnage is deleted
    store_pixel_values(fileVector);         // Copy the pixel values to local object vector

    imageFile.close(); // closing file

    return 0;
}

int Image::calculate_grayscale_values(int i, int j)
{
    return ((int)(pixelVector.at(i).at(j).get_red_pixel() * c_r) + (int)(pixelVector.at(i).at(j).get_green_pixel() * c_g) + (int)(pixelVector.at(i).at(j).get_blue_pixel() * c_b));
}

void Image::convert_to_greyscale(float r, float g, float b)
{
    set_coefficient_channels(r, g, b);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int grayPixelValue = calculate_grayscale_values(i, j);

            if (grayPixelValue > 255) // If the pixels are saturated
                pixelVector.at(i).at(j).set_pixel_values(255, 255, 255);

            else
                pixelVector.at(i).at(j).set_pixel_values(grayPixelValue, grayPixelValue, grayPixelValue);
        }
    }
}

void Image::save_as_file()
{
    // getting new filename from user
    string s;
    cin >> s;

    // If the entered filename doesnt have the file extension, add the extension
    int len = s.length();
    if (len < 4 || (s.substr(len - 4, 4) != ".ppm"))
        s += ".ppm";

    ofstream newImageFile(s);

    /* Storing header information into the new file */
    newImageFile << magicNumber << endl
                 << height << " "
                 << width << endl
                 << maxColorVal << endl;

    /* Copying the pixel values to the new file */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newImageFile << pixelVector.at(i).at(j).get_red_pixel() << endl
                         << pixelVector.at(i).at(j).get_green_pixel() << endl
                         << pixelVector.at(i).at(j).get_blue_pixel() << endl;
        }
    }

    newImageFile.close();
}

/********* IMAGE EDITTOR CLASS *********/
class ImageEditor
{ /* Class to run the image editor */
private:
    Image image;

    /* Member Functions */
    void display_save_image_menu();
    void display_scripts_menu();
    void display_open_image_menu();
    void display_convert_to_grayscale_menu();
    void display_main_menu();
    void get_coefficient_input(float &r, float &g, float &b);

public:
    void run();
};

void ImageEditor::get_coefficient_input(float &r, float &g, float &b)
{ /* Function to make sure the input for the coefficient values are valid float values */

    bool validInput = false; // flag for error-checking the users value inputs

    do // Loop for the user input of values
    {
        cin >> r >> g >> b;
        if (cin.fail()) // If the user enters an invalid character
        {
            cin.clear(); // clear buffer
            cin.ignore(10000, '\n');
            cerr << "Invalid input. Please try again." << endl;
        }

        else
            validInput = true;

    } while (!validInput);
}

void ImageEditor::display_convert_to_grayscale_menu()
{ /* Function to display grayscale menu */

    string choice_str;
    char choice = -1;
    while (choice)
    {
        cout << "CONVERT TO GRAYSCALE MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter Coefficients For RED GREEN and BLUE Channels." << endl;
        cin >> choice_str;

        if (choice_str.length() > 1)
        {
            cerr << "Invalid Input. please try again." << endl;
            continue;
        }

        choice = choice_str[0];

        switch (choice)
        {
        case '0': // If the user enters 0, exit the menu
            return;

        case '1':
        {
            float r, g, b; // red green blue coefficient values to be given by the user

            get_coefficient_input(r, g, b); // check the input to make sure its valid

            image.convert_to_greyscale(r, g, b);
            break;
        }

        default:
            cin.ignore(10000, '\n'); // Clearing the input buffer
            cerr << "Invalid input. Please try again." << endl;
            break;
        }
    }
}

void ImageEditor::display_open_image_menu()
{ /* Function to diplay open image menu */

    string filename;

    string choice_str;
    char choice = -1;
    while (choice)
    {
        cout << "OPEN AN IMAGE MENU: " << endl;
        cout << "0 - Up" << endl;
        cout << "1 - Enter the Name of the Image" << endl;
        cin >> choice_str;

        if (choice_str.length() > 1)
        {
            cerr << "Invalid Input. please try again." << endl;
            continue;
        }

        choice = choice_str[0];

        switch (choice)
        {
        case '0':
            return;

        case '1':
            getline(cin, filename);
            image.open_image_file();
            // Image temp(filename);
            // image = temp;
            break;

        default:
            cin.ignore(10000, '\n'); // Clearing the input buffer
            cerr << "Invalid input. Please try again." << endl;
            break;
        }
    }
}

void ImageEditor::display_scripts_menu()
{ /* Function to display scripts menu */

    string choice_str;
    char choice = -1;

    while (choice)
    {
        cout << "SCRIPTS MENU: " << endl;
        cout << "0 - Up" << endl;
        cout << "1 - Convert to Grayscale (D)" << endl;
        cin >> choice_str;

        if (choice_str.length() > 1)
        {
            cerr << "Invalid Input. please try again." << endl;
            continue;
        }

        choice = choice_str[0];

        switch (choice)
        {
        case '0':
            return;

        case '1':
            display_convert_to_grayscale_menu();
            break;

        default:
            cin.ignore(10000, '\n'); // Clearing the input buffer
            cerr << "Invalid input. Please try again." << endl;
            break;
        }
    }
}

void ImageEditor::display_save_image_menu()
{ /* Function to display save image menu */

    string filename;

    string choice_str;
    char choice = -1;
    while (choice)
    {
        cout << "SAVE IMAGE DATA MENU: " << endl;
        cout << "0 - Up" << endl;
        cout << "1 - Enter A Filename" << endl;
        cin >> choice_str;

        if (choice_str.length() > 1)
        {
            cerr << "Invalid Input. please try again." << endl;
            continue;
        }

        choice = choice_str[0];

        switch (choice)
        {
        case '0':
            return;

        case '1':
            getline(cin, filename);
            image.save_as_file();
            break;

        default:
            cin.ignore(10000, '\n'); // Clearing the input buffer
            cerr << "Invalid input. Please try again." << endl;
            break;
        }
    }
}

void ImageEditor::display_main_menu()
{ /* Function to display main menu */

    string choice_str;
    char choice = -1;
    while (choice)
    {
        cout << "MAIN MENU: " << endl;
        cout << "0 - Exit" << endl;
        cout << "1 - Open An Image(D)" << endl;
        cout << "2 - Save Image Data(D)" << endl;
        cout << "3 - Scripts(D)" << endl;
        cin >> choice_str;

        if (choice_str.length() > 1)
        {
            cerr << "Invalid input. Please try again." << endl;
            continue;
        }

        choice = choice_str[0];

        switch (choice)
        {
        case '0':
            cout << "Exiting program..." << endl;
            return;

        case '1':
            display_open_image_menu();
            break;

        case '2':
            if (image.get_filename() == "\0")
            {
                cerr << "There is no file to save. Please open a file first." << endl;
                break;
            }

            display_save_image_menu();
            break;

        case '3':
            if (image.get_filename() == "\0")
            {
                cerr << "There is no file to modify. Please open a file first." << endl;
                break;
            }
            display_scripts_menu();
            break;

        default:
            cin.ignore(10000, '\n'); // Clearing the input buffer
            cerr << "Invalid Input. Please try again." << endl;
            break;
        }
    }
}

void ImageEditor::run()
{ /* Function to run the image editor */
    display_main_menu();
}

int main()
{
    ImageEditor imageEditor;
    imageEditor.run();

    return 0;
}