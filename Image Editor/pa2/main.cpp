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
    /* Constructors */
    Pixel();                             // Default constructor
    Pixel(int red, int green, int blue); // Constructor which initializes the pixel colors

    /* Member Functions */
    // Setter functions
    void set_pixel_values(int red, int green, int blue);

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
    string filename;            // stores the name of the file
    static string tempFileName; // stores the name fo the temporary file ccreated for error checking and modification

    // Colour channel coefficients
    float c_r;
    float c_g;
    float c_b;

    // FILE HEADER INFORMATION
    string magicNumber; // Magic number aka image type
    int height;         // Row count
    int width;          // Coloumn count
    int maxColorVal;    // Max color value of the image pixels

    // vector of type Pixel to hold the pixel values of the image
    vector<vector<Pixel>> pixelVector;

    /* PRIVATE MEMBER FUNCTIONS */
    void store_pixel_values();                                         // For copying the pixel values from the file to the vector
    void set_image_filename(string s);                                 // Setter function to set the image's filename
    int calculate_grayscale_values(int i, int j);                      // For calculating the greyscale values according to the coefficient channels
    void set_coefficient_channels(float red, float green, float blue); // Setter function for the coefficient values
    void delete_comments_from_file(ifstream &imageFile);               // Function to delete any comments from the file
    void check_fileheader_errors(ifstream &tempFileIn);                // Function for chekcing the file for errors

public:
    // Constructors
    Image();                                // Default Constructor
    Image(string s);                        // Constructor which initializes the filename
    Image(int row, int col, int maxColour); // Initializes height, width, and max color value

    // Member Functions
    string get_filename();
    int open_image_file();
    void convert_to_greyscale(float r, float b, float c);
    void save_image();
};

string Image::tempFileName = "temp.ppm";

Image::Image()
{ // Default constructor sets filename to null for error checking when trying to modify a file
    filename = "\0";
}

Image::Image(string s)
{ // Constructor which initializes filenames

    filename = s;
}

Image::Image(int row, int col, int maxColour)
{ // Constructor which initializes header information
    height = row;
    width = col;
    maxColorVal = maxColour;
}

void Image::set_image_filename(string s) { filename = s; } // Setter function for filename

string Image::get_filename() { return filename; } // Getter function for filiename

void Image::set_coefficient_channels(float red, float green, float blue)
// setter funcion for coefficient values
{
    c_r = red;
    c_g = green;
    c_b = blue;
}

void Image::delete_comments_from_file(ifstream &imageFile)
{ /*
    Function takes in a new temporary file and stores the original file information while
    deleting any comments to be able to store the image information wihtout any errors
  */

    ofstream tempFileOut(tempFileName); // opening file as an output stream

    // Read the file line by line
    string line;
    while (getline(imageFile, line))
    {
        // Do not store the line if it starts with a # symbol (comment line)
        if (line[0] != '#')
            tempFileOut << line << endl;
    }

    // Opening the temporary file
    tempFileOut.close();
}

void Image::check_fileheader_errors(ifstream &tempFileIn)
{
    // ifstream tempFileIn(tempFileName);

    /* Read the PPM header and store the values */
    tempFileIn >> magicNumber >> height >> width >> maxColorVal;

    /* If the magic number is wrong */
    if (magicNumber != "P3")
    {
        cerr << "Invalid image format" << endl; // Display error message
        remove(tempFileName.c_str());           // Delete the temporary file
        return;
    }
}

void Image::store_pixel_values()
{ /* Function to copy the pixel values from the file and store them in the image object's vector*/

    ifstream tempFileIn(tempFileName); // opening temporary file as an niput stream

    check_fileheader_errors(tempFileIn); // Making sure there are no errors or invalid data in the header of the file

    /* Copying the pixel values to the object's vector */
    for (int i = 0; i < height; i++)
    {
        vector<Pixel> innerVector; // Creating a temporary vector for the 2nd dimension of the array
        innerVector.resize(width); // Re-sizing the vector according to the width count

        for (int j = 0; j < width; j++)
        {
            // Creating a temporary pixel object and assigning it to the inner vector
            int r, g, b;
            tempFileIn >> r >> g >> b;
            Pixel temp(r, g, b);
            innerVector[j] = temp;
        }

        // Pushing back the inner vector into the outer vector
        pixelVector.push_back(innerVector);
    }

    // Deleting temporary file
    remove(tempFileName.c_str());
}

int Image::open_image_file()
{
    string s;
    cin >> s;
    filename = s;
    // set_image_filename(s);

    ifstream imageFile(filename);
    if (!imageFile.is_open())
    {
        cerr << "Failed to open file." << endl;
        return 0;
    }

    delete_comments_from_file(imageFile); // Checking the file for comments and deleting them
    store_pixel_values();                 // Copy the pixel values to local object vector

    imageFile.close();
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
            int tempPixelValue = calculate_grayscale_values(i, j);
            pixelVector.at(i).at(j).set_pixel_values(tempPixelValue, tempPixelValue, tempPixelValue);
        }
    }
}

void Image::save_image()
{
    string s;
    cin >> s;

    /* If the entered filename doesnt have the file extension, add the extension */
    int len = s.length();
    if (len < 4 || (s.substr(len - 4, 4) != ".ppm"))
        s += ".ppm";

    ofstream newImageFile(s);

    /* Storing header information into the new file */
    newImageFile << magicNumber << endl
                 << height << endl
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

public:
    void run();
};

void ImageEditor::display_convert_to_grayscale_menu()
{ /* Function to display grayscale menu */

    char choice = -1;
    while (choice)
    {
        cout << "============================================" << endl;
        cout << "CONVERT TO GRAYSCALE MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter Coefficients For RED GREEN and BLUE Channels." << endl;
        cin >> choice;

        switch (choice)
        {
        case '0':
            return;

        case '1':
            /* TODO: Error checking for coeficient channels? */
            float r, g, b;
            cin >> r >> g >> b;
            image.convert_to_greyscale(r, g, b);
            break;

        default:
            cerr << "Invalid input. Please try again." << endl;
            break;
        }
    }
}

void ImageEditor::display_open_image_menu()
{ /* Function to diplay open image menu */

    string filename;
    char choice = '1';
    while (choice)
    {
        cout << "============================================" << endl;
        cout << "OPEN AN IMAGE MENU: " << endl;
        cout << "0 - Up" << endl;
        cout << "1 - Enter the Name of the Image" << endl;
        cin >> choice;

        switch (choice)
        {
        case '0':
            return;

        case '1':
            getline(cin, filename);
            image.open_image_file();
            break;

        default:
            cerr << "Invalid input. Please try again." << endl;
            break;
        }
    }
}

void ImageEditor::display_scripts_menu()
{ /* Function to display scripts menu */

    char choice = '1';
    while (choice)
    {
        cout << "============================================" << endl;
        cout << "SCRIPTS MENU: " << endl;
        cout << "0 - Up" << endl;
        cout << "1 - Convert to Grayscale (D)" << endl;
        cin >> choice;

        switch (choice)
        {
        case '0':
            return;

        case '1':
            display_convert_to_grayscale_menu();
            break;

        default:
            cerr << "Invalid input. Please try again." << endl;
            break;
        }
    }
}

void ImageEditor::display_save_image_menu()
{ /* Function to display save image menu */
    string filename;
    char choice = '1';
    while (choice)
    {
        cout << "============================================" << endl;
        cout << "SAVE IMAGE DATA MENU: " << endl;
        cout << "0 - Up" << endl;
        cout << "1 - Enter A Filename" << endl;
        cin >> choice;

        switch (choice)
        {
        case '0':
            return;

        case '1':
            getline(cin, filename);
            image.save_image();
            break;

        default:
            cerr << "Invalid input. Please try again." << endl;
            break;
        }
    }
}

void ImageEditor::display_main_menu()
{ /* Function to display main menu */

    char choice = '1';
    while (choice)
    {
        cout << "============================================" << endl;
        cout << "MAIN MENU: " << endl;
        cout << "0 - Exit" << endl;
        cout << "1 - Open An Image(D)" << endl;
        cout << "2 - Save Image Data(D)" << endl;
        cout << "3 - Scripts(D)" << endl;
        cin >> choice;

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