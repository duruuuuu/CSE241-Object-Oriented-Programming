#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/********* PIXEL CLASS *********/
class Pixel
{ /* Class to store pixel values */
private:
    int r, g, b;

public:
    /* Constructors */
    Pixel();                             // Default constructor
    Pixel(int red, int green, int blue); // Constructor which initializes the pixel colors
    int get_red_pixel();
    int get_green_pixel();
    int get_blue_pixel();

    /* Member Functions */
    void set_pixel_values(int red, int green, int blue);
};

Pixel::Pixel()
{ // Default constructor
    r = 0;
    g = 0;
    b = 0;
}

Pixel::Pixel(int red, int green, int blue)
{ // Constructor which initializes the pixel colors
    r = red;
    g = green;
    b = blue;
}

int Pixel::get_red_pixel() { return r; }

int Pixel::get_green_pixel() { return g; }

int Pixel::get_blue_pixel() { return b; }

void Pixel::set_pixel_values(int red, int green, int blue)
{
    r = red;
    g = green;
    b = blue;
}

/********* IMAGE CLASS *********/
class Image
{ /* Class to store image values */
private:
    string filename;

    // Colour channel coefficients
    float c_r;
    float c_g;
    float c_b;

    string magicNumber;

    // max colour value stated in the image file
    int maxColorVal;

    // Number of rows and coloumns of pixels in the image
    int height; // Row count
    int width;  // Coloumn count

    // vector to hold the pixel values of the image
    vector<vector<Pixel>> pixelVector;

    void store_pixel_values(ifstream &imageFile);
    void set_image_filename(string s);

    int calculate_grayscale_values(int i, int j);

public:
    // Constructors
    Image();                                // Default Constructor
    Image(string s);                        // Constructor which initializes the filename
    Image(int row, int col, int maxColour); // Initializes height, width, and max color value

    // Member Functions
    void set_coefficient_channels(float red, float green, float blue);
    string get_filename();
    int open_image_file();
    void save_image();
    void convert_to_greyscale();
};

Image::Image(){};

Image::Image(string s) { filename = s; }

Image::Image(int row, int col, int maxColour)
{
    height = row;
    width = col;
    maxColorVal = maxColour;
}

void Image::set_image_filename(string s) { filename = s; }

string Image::get_filename() { return filename; }

void Image::set_coefficient_channels(float red, float green, float blue)
{
    c_r = red;
    c_g = green;
    c_b = blue;
}

void Image::store_pixel_values(ifstream &imageFile)
{
    /* Check for comments in the file and delete them if any */
    string tempFileName = "temp.ppm";
    ofstream tempFileOut(tempFileName);

    // Read the file line by lin
    string line;
    while (getline(imageFile, line))
    {
        // Check if the line starts with a # symbol
        if (line[0] != '#')
            tempFileOut << line << endl;
    }

    // Opening the temporary file
    tempFileOut.close();

    ifstream tempFileIn(tempFileName);
    /* Read the PPM header and delete any comments, if there are any*/
    tempFileIn >> magicNumber >> height >> width >> maxColorVal;

    /* If the magic numnber is wrong */
    if (magicNumber != "P3")
    {
        cerr << "Invalid image format" << endl;
        return;
    }

    for (int i = 0; i < height; i++)
    {
        // Creating a temporary vector for the 2nd dimension of the array
        vector<Pixel> innerVector;
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

    // Deleting temp file
    remove(tempFileName.c_str());
}

int Image::open_image_file()
{
    string s;
    cin >> s;
    set_image_filename(s);

    ifstream imageFile(filename);
    if (!imageFile.is_open())
    {
        cerr << "Failed to open file." << endl;
        return 0;
    }

    store_pixel_values(imageFile);

    imageFile.close();
    return 0;
}

int Image::calculate_grayscale_values(int i, int j)
{
    return ((int)(pixelVector.at(i).at(j).get_red_pixel() * c_r) + (int)(pixelVector.at(i).at(j).get_green_pixel() * c_g) + (int)(pixelVector.at(i).at(j).get_blue_pixel() * c_b));
}

void Image::convert_to_greyscale()
{
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

    /* Checking if the filename entered is valid */
    int len = s.length();
    if (len < 4 || (s.substr(len - 4, 4) != ".ppm"))
    {
        cerr << "Please enter a valid ppm filename. (make sure the extension of the file is correct)" << endl;
        return;
    }

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
    int save_image_menu();
    int scripts_menu();
    int open_image_menu();
    int convert_to_grayscale_menu();
    int display_menu();

public:
    void run();
};

int ImageEditor::convert_to_grayscale_menu()
{ /* Functio to display grayscale menu */
    int input = 1;
    while (input)
    {
        cout << "============================================" << endl;
        cout << "CONVERT TO GRAYSCALE MENU" << endl;
        cout << "0 - UP" << endl;
        cout << "1 - Enter Coefficients For RED GREEN and BLUE Channels." << endl;

        cin >> input;

        if (input == 1)
        {
            float red = 0.0, blue = 0.0, green = 0.0;
            cin >> red >> green >> blue;

            image.set_coefficient_channels(red, green, blue);

            image.convert_to_greyscale();
        }
    }
    return 0;
}

int ImageEditor::open_image_menu()
{ /* Function to diplay open image menu */
    cout << "============================================" << endl;
    cout << "OPEN AN IMAGE MENU: " << endl;
    cout << "0 - Up" << endl;
    cout << "1 - Enter the Name of the Image" << endl;

    int n;
    cin >> n;
    return n;
}

int ImageEditor::scripts_menu()
{ /* Function to display scripts menu */
    cout << "============================================" << endl;
    cout << "SCRIPTS MENU: " << endl;
    cout << "0 - Up" << endl;
    cout << "1 - Convert to Grayscale (D)" << endl;

    int n;
    cin >> n;
    return n;
}

int ImageEditor::save_image_menu()
{ /* Function to display save image menu */
    cout << "============================================" << endl;
    cout << "SAVE IMAGE DATA MENU: " << endl;
    cout << "0 - Up" << endl;
    cout << "1 - Enter A Filename" << endl;

    int n;
    cin >> n;
    return n;
}

int ImageEditor::display_menu()
{ /* Function to display main menu */
    cout << "============================================" << endl;
    cout << "MAIN MENU: " << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Open An Image(D)" << endl;
    cout << "2 - Save Image Data(D)" << endl;
    cout << "3 - Scripts(D)" << endl;

    int n;
    cin >> n;
    return n;
}

void ImageEditor::run()
{ /* Function to run the image editor */
    int input = display_menu();

    /* Loop to display hte main menu and sub-menus*/
    while (input)
    {
        int input2 = 1;
        if (input == 1)
        {
            while (input2)
            {
                int input3 = 1;
                input2 = open_image_menu();

                if (input2 == 1)
                {
                    while (input3)
                    {
                        input3 = image.open_image_file();
                    }
                }
            }
        }

        else if (input == 2)
        {
            while (input2)
            {
                input2 = save_image_menu();

                if (input2 == 1)
                    image.save_image();
            }
        }

        else if (input == 3)
        {
            while (input2)
            {
                int input3 = 1;
                input2 = scripts_menu();

                if (input2 == 1)
                    while (input3)
                        input3 = convert_to_grayscale_menu();
            }
        }

        input = display_menu();
    }

    cout << "============================================\nExiting Program..." << endl;
}

int main()
{
    ImageEditor imageEditor;
    imageEditor.run();

    return 0;
}