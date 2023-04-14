#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

int numDigits(int n)
{ // Helper function for output operator formatting
    int count = 0;
    while (n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}
/********* IMAGE CLASS *********/
class Image
{ /* Class to store the image and its file information */
public:
    // Pixel struct belonging to the class
    struct Pixel
    {
        int r, g, b;
    };

    // Constructors
    Image();                                // Default Constructor
    Image(string s);                        // Creates an object from filename
    Image(int row, int col, int maxColour); // Initializes height, width, and max color value
    Image(int row, int col);                // Creates an empty object with the given dimensions
    Image(const Image &other);              // Copy constructor

    // Setter functions
    void set_red_pixel(int red, int x, int y) { pixelVector[x][y].r = red; }
    void set_green_pixel(int green, int x, int y) { pixelVector[x][y].g = green; }
    void set_blue_pixel(int blue, int x, int y) { pixelVector[x][y].b = blue; }
    void set_pixel(int x, int y, int red, int green, int blue)
    {
        pixelVector[x][y].r = red;
        pixelVector[x][y].g = green;
        pixelVector[x][y].b = blue;
    }

    void set_pixel_values(int red, int green, int blue);
    void set_pixel_values(vector<vector<Pixel>> pixels); // For copying the pixel values from the file to the vector
    void set_pixel_values(const vector<string> &fileVector);
    void set_image_filename(string s);                                 // Setter function to set the image's filename
    void set_coefficient_channels(float red, float green, float blue); // Setter function for the coefficient values
    void set_magic_number(string s);
    void set_height(int h);
    void set_width(int w);
    void set_height_width(int h, int w);
    void set_header_info(int h, int w, string magicNo, int maxVal);
    void set_max_color_value(int maxColor);
    void set_pixel(int row, int col, Pixel pixel);

    // Getter functions
    // Getter functions
    int get_red_pixel(int x, int y) const { return pixelVector[x][y].r; }
    int get_green_pixel(int x, int y) const { return pixelVector[x][y].g; }
    int get_blue_pixel(int x, int y) const { return pixelVector[x][y].b; }
    // const int &get_red_pixel(int x, int y) const { return pixelVector[x][y].r; }
    // const int &get_green_pixel(int x, int y) const { return pixelVector[x][y].g; }
    // const int &get_blue_pixel(int x, int y) const { return pixelVector[x][y].b; }

    string get_filename() const;
    string get_magic_number() const;
    int get_height() const;
    int get_width() const;
    int get_max_color_val() const;
    vector<vector<Pixel>> get_pixel_vector() const { return pixelVector; }
    Image operator+(const Image &other) const;
    Image operator-(const Image &other) const;
    Image &operator=(const Image &other);
    int &operator()(int row, int col, int channel);

    friend ostream &operator<<(ostream &os, const Image &image);

private:
    // stores the name of the file
    string filename;

    // FILE HEADER INFORMATION
    string magicNumber; // Magic number aka image type
    int height;         // Row count
    int width;          // Coloumn count
    int maxColorVal;    // Max color value of the image pixels

    void print_image_dimensions() const; // Function that prints the dimensions of the image

    void delete_comments(ifstream &imageFile, vector<string> &fileVector); // Function to delete any comments from the file
    bool check_fileheader(const vector<string> &fileVector);               // Function for chekcing the file for errors

    // Constant values of the indices for the header information that will be stored in a string vector
    const int magicNumberIndex = 0;
    const int heightIndex = 1;
    const int widthIndex = 2;
    const int maxColorIndex = 3;
    const int pixelStartIndex = 4;

    // vector of type Pixel to hold the pixel values of the image
    vector<vector<Pixel>> pixelVector;
};

Image::Image()
{ // Default constructor sets filename to null for error checking when trying to modify a file
    filename = "\0";
}

Image::Image(int row, int col)
{
    // Setting header information
    set_magic_number("P3");
    set_height_width(row, col);
    set_max_color_value(255);

    // Clearing the vector in case there is already an existing object

    pixelVector = vector<vector<Pixel>>(row, vector<Pixel>(col));
}

Image::Image(string s)
{ // Constructor which takes a filename and creates an object
    set_image_filename(s);

    // If the file could not be opened
    ifstream imageFile(filename);
    if (!imageFile.is_open())
    {
        cerr << "Failed to open file." << endl;
        return;
    }

    vector<string> fileVector;                 // local string vector to store the file data without error or comments
    delete_comments(imageFile, fileVector);    // Checking the file for comments and deleting them, and putting the data in teh local vector
    bool check = check_fileheader(fileVector); // Check the file header to make sure there are no errors
    if (check == false)                        // Close the file and return if the file type is not valid
    {
        imageFile.close();
        return;
    }
    pixelVector = vector<vector<Pixel>>(height, vector<Pixel>(width));
    set_pixel_values(fileVector); // Copy the pixel values to object member vector

    imageFile.close(); // closing file
}

Image::Image(int row, int col, int maxColour)
{ // Constructor which initializes header information
    height = row;
    width = col;
    maxColorVal = maxColour;

    pixelVector = vector<vector<Pixel>>(row, vector<Pixel>(col));
}

Image::Image(const Image &other)
{
    this->filename = other.filename;
    this->magicNumber = other.magicNumber;
    this->height = other.height;
    this->width = other.width;
    this->maxColorVal = other.maxColorVal;
    this->pixelVector = other.pixelVector;
}

Image &Image::operator=(const Image &other)
{
    if (this != &other)
    {
        this->filename = other.filename;
        this->magicNumber = other.magicNumber;
        this->height = other.height;
        this->width = other.width;
        this->maxColorVal = other.maxColorVal;
        this->pixelVector = other.pixelVector;
    }
    return *this;
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

bool Image::check_fileheader(const vector<string> &fileVector)
{ /* Function for error-checking the file header and making sure the file is of correct format */

    // Store header information in the object variables
    magicNumber = fileVector[magicNumberIndex];
    height = stoi(fileVector[heightIndex]);
    width = stoi(fileVector[widthIndex]);
    maxColorVal = stoi(fileVector[maxColorIndex]);

    /* If the magic number is wrong */
    if (magicNumber != "P3")
    {
        cerr << "Invalid image format. Closing file..." << endl; // Display error message
        set_image_filename("\0");
        return false;
    }

    return true;
}

void Image::set_pixel_values(const vector<string> &fileVector)
{ /* Function to copy the pixel values from the file and store them in the image object's vector*/

    int rIndex = pixelStartIndex, gIndex = pixelStartIndex + 1, bIndex = pixelStartIndex + 2;

    // Copying the pixel values to the object's vector
    for (int i = 0; i < height; i++)
    {
        // vector<Pixel> innerVector; // Creating a temporary vector for the 2nd dimension of the array
        // innerVector.resize(width); // Re-sizing the vector according to the width count

        for (int j = 0; j < width; j++)
        {
            // Creating a temporary pixel object and assigning it to the inner vector
            int r, g, b;
            r = stoi(fileVector[rIndex]);
            g = stoi(fileVector[gIndex]);
            b = stoi(fileVector[bIndex]);

            // Pixel temp(r, g, b);
            // innerVector[j] = temp;

            pixelVector[i][j].r = r;
            pixelVector[i][j].g = g;
            pixelVector[i][j].b = b;

            // Incrementing pixel value indices
            rIndex += 3;
            gIndex += 3;
            bIndex += 3;
        }

        // pixelVector.push_back(innerVector);
    }
}

string Image::get_magic_number() const { return magicNumber; } // Accesses magic number
int Image::get_height() const { return height; }               // Accesses height
int Image::get_width() const { return width; }                 // Accesses width
int Image::get_max_color_val() const { return maxColorVal; }   // Accesses max color value
string Image::get_filename() const { return filename; }        // Getter function for filiename
void Image::set_image_filename(string s) { filename = s; }     // Setter function for filename
void Image::set_magic_number(string s) { magicNumber = s; }    // Setter function for magic number
void Image::set_height(int h) { height = h; }                  // Setter function for height
void Image::set_width(int w) { width = w; }                    // Setter function for width

void Image::print_image_dimensions() const
{
    cout << "IMAGE DIMENSIONS:" << endl;
    cout << "Height: " << height << " Width: " << width << endl;
}

void Image::set_height_width(int h, int w)
{
    height = h;
    width = w;

    pixelVector = vector<vector<Pixel>>(height, vector<Pixel>(width));
}

void Image::set_max_color_value(int maxColor) { maxColorVal = maxColor; }

void Image::set_header_info(int h, int w, string magicNo, int maxVal)
{
    height = h;
    width = w;
    magicNumber = magicNo;
    maxColorVal = maxVal;

    pixelVector = vector<vector<Pixel>>(height, vector<Pixel>(width));
}

void Image::set_pixel_values(vector<vector<Pixel>> pixels) { this->pixelVector = pixels; }

void Image::set_pixel(int row, int col, Pixel pixel) { this->pixelVector[row][col] = pixel; }

Image Image::operator+(const Image &other) const
{
    if (this->height != other.height || this->width != other.width)
    {
        Image invalid(0, 0);
        invalid.filename = "INVALID";
        return invalid;
    }

    Image returnVal(other.height, other.width, other.maxColorVal);
    returnVal.magicNumber = this->magicNumber;

    for (int i = 0; i < returnVal.height; i++)
    {
        for (int j = 0; j < returnVal.width; j++)
        {
            int r, g, b;

            // adding red pixel
            r = this->pixelVector[i][j].r + other.pixelVector[i][j].r;
            g = this->pixelVector[i][j].g + other.pixelVector[i][j].g;
            b = this->pixelVector[i][j].b + other.pixelVector[i][j].b;

            if (r < 0)
                r = 0;
            if (g < 0)
                g = 0;
            if (b < 0)
                b = 0;
            if (r > returnVal.maxColorVal)
                r = returnVal.maxColorVal;
            if (g > returnVal.maxColorVal)
                g = returnVal.maxColorVal;
            if (b > returnVal.maxColorVal)
                b = returnVal.maxColorVal;

            returnVal.pixelVector[i][j] = {r, g, b};
        }
    }
    return returnVal;
}
Image Image::operator-(const Image &other) const
{
    if (this->height != other.height || this->width != other.width)
    {
        Image invalid(0, 0);
        invalid.filename = "INVALID";
        return invalid;
    }

    Image returnVal(other.height, other.width, other.maxColorVal);
    returnVal.magicNumber = this->magicNumber;

    for (int i = 0; i < returnVal.height; i++)
    {
        for (int j = 0; j < returnVal.width; j++)
        {
            int r, g, b;

            // adding red pixel
            r = this->pixelVector[i][j].r - other.pixelVector[i][j].r;
            g = this->pixelVector[i][j].g - other.pixelVector[i][j].g;
            b = this->pixelVector[i][j].b - other.pixelVector[i][j].b;

            if (r < 0)
                r = 0;
            if (g < 0)
                g = 0;
            if (b < 0)
                b = 0;
            if (r > returnVal.maxColorVal)
                r = returnVal.maxColorVal;
            if (g > returnVal.maxColorVal)
                g = returnVal.maxColorVal;
            if (b > returnVal.maxColorVal)
                b = returnVal.maxColorVal;

            returnVal.pixelVector[i][j] = {r, g, b};
        }
    }
    return returnVal;
}
int &Image::operator()(int row, int col, int channel)
{
    if (row < 0 || row >= height || col < 0 || col >= width || channel < 1 || channel > 3)
    {
        cerr << "Out of bounds error!" << endl;
        exit(1);
    }
    if (channel == 1)
    {
        cout << "fxn: r: " << pixelVector[row][col].r << " "
             << "fxn: g: " << pixelVector[row][col].g << " "
             << "fxn: b: " << pixelVector[row][col].b << " " << endl;
        return pixelVector[row][col].r;
    }

    else if (channel == 2)
        return pixelVector[row][col].g;

    else if (channel == 3)
        return pixelVector[row][col].b;

    else
    {
        cerr << "Undefined error" << endl;
        exit(1);
    }
}
ostream &operator<<(ostream &os, const Image &image)
{
    cout << image.magicNumber << endl;
    cout << image.height << " " << image.width << endl;
    cout << image.maxColorVal << endl;

    /*for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            cout << image.pixelVector[i][j].r
                 << "    " << image.pixelVector[i][j].g
                 << "    " << image.pixelVector[i][j].b << "\t\t";
        }
        cout << endl;
    }

    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            cout << image.pixelVector[i][j].r
                 << setw(4) << image.pixelVector[i][j].g
                 << setw(4) << image.pixelVector[i][j].b << "\t";
        }
        cout << endl;
    }*/

    const int maxDigit = 3;

    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            cout << image.pixelVector[i][j].r;
            for (int k = 0; k < maxDigit - numDigits(image.pixelVector[i][j].r); k++)
                cout << " ";

            cout << " ";
            cout << image.pixelVector[i][j].g;
            for (int k = 0; k < maxDigit - numDigits(image.pixelVector[i][j].g); k++)
                cout << " ";

            cout << " ";
            cout << image.pixelVector[i][j].b;
            for (int k = 0; k < maxDigit - numDigits(image.pixelVector[i][j].b); k++)
                cout << " ";

            cout << "\t";
        }
        cout << endl;
    }
    return os;
}

/* Standalone Functions */
int read_ppm(const string source_ppm_file_name, Image &destination_object);
int write_ppm(const string destination_ppm_file_name, const Image &source_object);
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);
int test_print(const string filname_image1);
int swap_channels(Image &image_object_to_be_modified, int swap_choice);
Image single_color(const Image &source, int color_choice);

int main(int argc, char **argv)
{
    // Check for command line arguments
    // the first argumetn is going to be choice number
    // the second argument is going to be a ppm_file_name_1
    // the third argument is goingto be a ppm_file_name_2 (optional)
    // the third argument is goingto be a ppm_file_name_3 (optional)

    cout << "Number of arguments: " << argc << std::endl;
    for (int i = 0; i < argc; ++i)
        cout << "Argument " << i << ": " << argv[i] << endl;

    // Converting the choice provided in thecommand line into a string
    const string choice(argv[1]);

    // If choice number is 1, test addition.
    if (choice == "1" && argc == 5)
    {
        string ppm_file_name1(argv[2]), ppm_file_name2(argv[3]), ppm_file_name3(argv[4]);
        test_addition(ppm_file_name1, ppm_file_name2, ppm_file_name3);
    }
    // if choice number is 2
    else if (choice == "2" && argc == 5)
    {
        string ppm_file_name1(argv[2]), ppm_file_name2(argv[3]), ppm_file_name3(argv[4]);
        test_subtraction(ppm_file_name1, ppm_file_name2, ppm_file_name3);
    }

    // Check the existence of optional arguments, if they are not given, exit
    else if ((choice == "1" || choice == "2") && argc < 5)
    {
        cerr << "Not enough arguments" << endl;
        exit(1);
    }

    // if choice number is 3
    // read ppm_file_name1 using function read_ppm
    if (choice == "3" && argc == 3)
    {
        string ppm_file_name1(argv[2]);
        Image destination;

        int returnVal = read_ppm(ppm_file_name1, destination);
        cout << destination << endl
             << destination << endl;
        if (returnVal == 0)
        {
            cerr << "Error. Program terminating..." << endl;
            exit(1);
        }

        // swap_channels(destination, 2);

        write_ppm("ppm_file_name2", destination);
    }

    // If choice is number 4
    if (choice == "4" && argc == 3)
    {
        string ppm_file_name1(argv[2]);
        Image destination;

        int returnVal = read_ppm(ppm_file_name1, destination);
        if (returnVal == 0)
        {
            cerr << "Error. Program terminating..." << endl;
            exit(1);
        }

        // swap_channels(GREEN, BLUE);

        write_ppm("ppm_file_name2", destination);
    }
    /*
    // If choice is number 5
    read_ppm(ppm_file_name1);
    // Create a new object which only contains RED channel data of the file read
    single_color();
    write_ppm("ppm_file_name2");

    // If choice is number 6
    read_ppm(ppm_file_name1);
    // Create a new object which only contains GREEN channel data of the file read
    single_color();
    write_ppm("ppm_file_name2");

    // If choice is number 7
    read_ppm(ppm_file_name1);
    // Create a new object which only contains BLUE channel data of the file read
    single_color();
    write_ppm("ppm_file_name2");

    */

    return 0;
}

int test_addition(const string filename_image1, const string filename_image2, const string filename_image3)
{
    Image image1(filename_image1), image2(filename_image2), image3;

    if (image1.get_max_color_val() != image2.get_max_color_val())
    {
        cerr << "Maximum Color Values of images do not match. Please enter valid images" << endl;
        exit(1);
    }

    image3.set_max_color_value(image1.get_max_color_val());
    image3.set_height_width(image1.get_height(), image1.get_width());
    image3.set_magic_number("P3");

    image3 = image1 + image2;

    write_ppm(filename_image3, image3);
    return 1;
}

int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3)
{
    Image image1(filename_image1), image2(filename_image2), image3;

    if (image1.get_max_color_val() != image2.get_max_color_val())
    {
        cerr << "Maximum Color Values of images do not match. Please enter valid images" << endl;
        exit(1);
    }

    image3.set_max_color_value(image1.get_max_color_val());
    image3.set_height_width(image1.get_height(), image1.get_width());
    image3.set_magic_number("P3");

    image3 = image1 - image2;

    write_ppm(filename_image3, image3);

    return 1;
}

int write_ppm(const string destination_ppm_file_name, const Image &source_object)
{
    // If there is no such file, or if the addition was unsuccesful for any reason, do not create any file and end the program
    if (source_object.get_filename() == "INVALID")
        return 0;

    ofstream newImageFile(destination_ppm_file_name);

    /* Storing header information into the new file */
    newImageFile << source_object.get_magic_number() << endl
                 << source_object.get_height() << " "
                 << source_object.get_width() << endl
                 << source_object.get_max_color_val() << endl;

    // Creating a temporary vector that references source object's pixel vector for easier readability int he next code block
    // const vector<vector<Pixel>> &temp = source_object.get_pixel_value();

    /* Copying the pixel values to the new file */
    for (int i = 0; i < source_object.get_height(); i++)
    {
        for (int j = 0; j < source_object.get_width(); j++)
        {
            newImageFile << source_object.get_red_pixel(i, j) << " "
                         << source_object.get_green_pixel(i, j) << " "
                         << source_object.get_blue_pixel(i, j) << endl;
        }
    }

    newImageFile.close();
    return 1;
}

int read_ppm(const string source_ppm_file_name, Image &destination_object)
{
    // Opening and error-checking the file
    ifstream sourceFile(source_ppm_file_name);
    if (!sourceFile.is_open())
    {
        cerr << "Could not open file." << endl;
        return 0;
    }

    string magicNumber;
    int height, width, maxColorVal;
    sourceFile >> magicNumber >> width >> height >> maxColorVal;

    destination_object.set_header_info(height, width, magicNumber, maxColorVal);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r, g, b;
            sourceFile >> r >> g >> b;
            destination_object.set_pixel(i, j, {r, g, b});
        }
    }

    sourceFile.close();
    return 1;
}

int swap_channels(Image &image_object_to_be_modified, int swap_choice)
{
    // Swap choice 1: red and green
    // Swap choice 2: red and blue
    // Swap choice 3: green and blue

    for (int i = 0; i < image_object_to_be_modified.get_height(); i++)
    {
        for (int j = 0; j < image_object_to_be_modified.get_width(); j++)
        {
            cout << image_object_to_be_modified.get_red_pixel(i, j) << " "
                 << image_object_to_be_modified.get_green_pixel(i, j)
                 << " " << image_object_to_be_modified.get_blue_pixel(i, j) << endl;
        }
    }

    if (swap_choice == 2)
    {
        for (int i = 0; i < image_object_to_be_modified.get_height(); i++)
        {
            for (int j = 0; j < image_object_to_be_modified.get_width(); j++)
            {
                int temp = image_object_to_be_modified(i, j, 1);
                cout << "i" << i << "j" << j << " ," << temp << endl;
                image_object_to_be_modified.set_red_pixel(i, j, image_object_to_be_modified.get_blue_pixel(i, j));
                image_object_to_be_modified.set_blue_pixel(i, j, temp);
            }
        }
    }
    return 1;
}
