#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

int numDigits(int n)
{ // Helper function for formatting output in the << operator
    int count = 0;
    while (n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

bool is_all_digit(string s)
{ // Helper function for the read_ppm function to make sure the file is valid
    for (char c : s)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

/********* IMAGE CLASS *********/
class ppmImage
{ /* Class to store the image and its file information */
public:
    // Pixel struct belonging to the class
    struct Pixel
    {
        int r, g, b;
    };

    // Constructors
    ppmImage();                                // Default Constructor
    ppmImage(string s);                        // Creates an object from filename
    ppmImage(int row, int col, int maxColour); // Initializes height, width, and max color value
    ppmImage(int row, int col);                // Creates an empty object with the given dimensions
                                               // ppmImage(const ppmImage &other);           // Copy constructor

    // Setter functions
    void set_red_pixel(int x, int y, int red); // Sets individual pixel channels by getting the index values
    void set_green_pixel(int x, int y, int green);
    void set_blue_pixel(int x, int y, int blue);
    void set_pixels(int row, int col, Pixel pixel);
    void set_pixel_values(int red, int green, int blue);
    void set_pixel_values(vector<vector<Pixel>> pixels); // For copying the pixel values from the file to the vector
    void set_pixel_values(const vector<string> &fileVector);
    void set_image_filename(string s); // Setter function to set the image's filename
    void set_magic_number(string s);
    void set_height(int h);
    void set_width(int w);
    void set_height_width(int h, int w);
    void set_header_info(int h, int w, string magicNo, int maxVal);
    void set_max_color_value(int maxColor);

    // Getter functions
    // Getter functions
    int get_red_pixel(int x, int y) const; // gets an individual pixel ccolo channel
    int get_green_pixel(int x, int y) const;
    int get_blue_pixel(int x, int y) const;
    string get_filename() const;
    string get_magic_number() const;
    int get_height() const;
    int get_width() const;
    int get_max_color_val() const;
    vector<vector<Pixel>> get_pixel_vector() const { return pixelVector; }
    int open_image_file();
    void save_as_file() const;

    ppmImage operator+(const ppmImage &other) const; // Adds two ppm Images' pixels
    ppmImage operator-(const ppmImage &other) const; // Subtracts two ppm Images' pixels
                                                     // ppmImage &operator=(const ppmImage &other);      // Assigns one ppmImage to another
    int &operator()(int row, int col, int channel);  // Function call operator returns specific color channel by the given parameters

    friend ostream &operator<<(ostream &os, const ppmImage &image); // Prints ppm Image pixel vector to stdout

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
    // const int magicNumberIndex = 0;
    // const int heightIndex = 1;
    // const int widthIndex = 2;
    // const int maxColorIndex = 3;
    // const int pixelStartIndex = 4;

    // vector of type Pixel to hold the pixel values of the image
    vector<vector<Pixel>> pixelVector;
};

ppmImage::ppmImage()
{ // Default constructor sets filename to null for error checking when trying to modify a file
    filename = "\0";
}

ppmImage::ppmImage(int row, int col)
{
    // Setting header information
    set_magic_number("P3");
    set_height_width(row, col);
    set_max_color_value(255);

    if (row < 0 || col < 0)
    {
        cerr << "Invalid paramters" << endl;
        exit(1);
    }

    pixelVector = vector<vector<Pixel>>(row, vector<Pixel>(col));
}

ppmImage::ppmImage(string s)
{ // Constructor which takes a filename and creates an object
    set_image_filename(s);

    // If the file could not be opened
    ifstream imageFile(filename);
    if (!imageFile.is_open())
    {
        cerr << "Failed to open file." << endl;
        exit(1);
    }
    vector<string> fileVector;                 // local string vector to store the file data without error or comments
    delete_comments(imageFile, fileVector);    // Checking the file for comments and deleting them, and putting the data in teh local vector
    bool check = check_fileheader(fileVector); // Check the file header to make sure there are no errors
    if (check == false)                        // Close the file and return if the file type is not valid
    {
        imageFile.close();
        return;
    }
    pixelVector.clear();
    set_pixel_values(fileVector); // Copy the pixel values to object member vector

    imageFile.close(); // closing file
}

ppmImage::ppmImage(int row, int col, int maxColour)
{ // Constructor which initializes header information
    height = row;
    width = col;
    maxColorVal = maxColour;

    // Resizing vector according to given parameters
    pixelVector = vector<vector<Pixel>>(row, vector<Pixel>(col));
}

/*ppmImage::ppmImage(const ppmImage &other)
{ // Copy constructor to create a copy of an object
    this->filename = other.filename;
    this->magicNumber = other.magicNumber;
    this->height = other.height;
    this->width = other.width;
    this->maxColorVal = other.maxColorVal;

    // Clear the pixelVector before copying
    this->pixelVector.clear();
    // Creating a copy of the vectro to avoid probelms with pointers and dynamic vectors
    for (int i = 0; i < other.height; i++)
    {
        vector<Pixel> innerVector;
        innerVector.resize(other.width);
        for (int j = 0; j < other.width; j++)
        {
            innerVector[j] = {other.pixelVector[i][j].r,
                              other.pixelVector[i][j].g,
                              other.pixelVector[i][j].b};
        }
        pixelVector.push_back(innerVector);
    }
}*/

/*ppmImage &ppmImage::operator=(const ppmImage &other)
{ // Assignment operator to assign one image object to another using a deep copy
  // To avoid any issues with copying teh vectors
    if (this != &other)
    {
        this->filename = other.filename;
        this->magicNumber = other.magicNumber;
        this->height = other.height;
        this->width = other.width;
        this->maxColorVal = other.maxColorVal;

        // Clear the pixelVector before copying
        this->pixelVector.clear();

        for (int i = 0; i < other.height; i++)
        {
            vector<Pixel> innerVector;
            innerVector.resize(other.width);
            for (int j = 0; j < other.width; j++)
            {
                innerVector[j] = {other.pixelVector[i][j].r,
                                  other.pixelVector[i][j].g,
                                  other.pixelVector[i][j].b};
            }
            pixelVector.push_back(innerVector);
        }
    }
    return *this;
}*/

void ppmImage::delete_comments(ifstream &imageFile, vector<string> &fileVector)
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

bool ppmImage::check_fileheader(const vector<string> &fileVector)
{ /* Function for error-checking the file header and making sure the file is of correct format */

    // Store header information in the object variables
    // magicNumber = fileVector[magicNumberIndex];
    // height = stoi(fileVector[heightIndex]);
    // width = stoi(fileVector[widthIndex]);
    // maxColorVal = stoi(fileVector[maxColorIndex]);

    /* If the magic number is wrong */
    if (magicNumber != "P3")
    {
        cerr << "Invalid image format. Closing file..." << endl; // Display error message
        set_image_filename("\0");
        return false;
    }

    return true;
}

void ppmImage::set_pixel_values(const vector<string> &fileVector)
{ /* Function to copy the pixel values from the file and store them in the image object's vector*/

    // int rIndex = pixelStartIndex, gIndex = pixelStartIndex + 1, bIndex = pixelStartIndex + 2;

    // Copying the pixel values to the object's vector
    for (int i = 0; i < height; i++)
    {
        vector<Pixel> innerVector; // Creating a temporary vector for the 2nd dimension of the array
        innerVector.resize(width); // Re-sizing the vector according to the width count

        for (int j = 0; j < width; j++)
        {
            // Creating a temporary pixel object and assigning it to the inner vector
            int r, g, b;
            // r = stoi(fileVector[rIndex]);
            // g = stoi(fileVector[gIndex]);
            // b = stoi(fileVector[bIndex]);

            // Setting pixels in the vector
            innerVector[j].r = r;
            innerVector[j].g = g;
            innerVector[j].b = b;

            // Incrementing pixel value indices
            // rIndex += 3;
            // gIndex += 3;
            // bIndex += 3;
        }
        pixelVector.push_back(innerVector);
    }
}

string ppmImage::get_magic_number() const { return magicNumber; } // Accesses magic number
int ppmImage::get_height() const { return height; }               // Accesses height
int ppmImage::get_width() const { return width; }                 // Accesses width
int ppmImage::get_max_color_val() const { return maxColorVal; }   // Accesses max color value
string ppmImage::get_filename() const { return filename; }        // Getter function for filiename
void ppmImage::set_image_filename(string s) { filename = s; }     // Setter function for filename
void ppmImage::set_magic_number(string s) { magicNumber = s; }    // Setter function for magic number
void ppmImage::set_height(int h)
{
    if (h < 0)
    {
        cerr << "Invalid Parameter." << endl;
        exit(1);
    }
    height = h;
} // Setter function for height
void ppmImage::set_width(int w)
{
    if (w < 0)
    {
        cerr << "Invalid Parameter." << endl;
        exit(1);
    }
    width = w;
} // Setter function for width
void ppmImage::set_red_pixel(int x, int y, int red)
{
    if (x >= height || x < 0 || y >= width || y < 0)
    { // Making sure the given ia nd j values are valid

        cerr << "Invalid parameters" << endl;
        exit(1);
    }
    pixelVector[x][y].r = red;
}
void ppmImage::set_green_pixel(int x, int y, int green)
{
    if (x >= height || x < 0 || y >= width || y < 0)
    { // Making sure the given ia nd j values are valid
        cerr << "Invalid parameters" << endl;
        exit(1);
    }

    pixelVector[x][y].g = green;
}
void ppmImage::set_blue_pixel(int x, int y, int blue)
{
    if (x >= height || x < 0 || y >= width || y < 0)
    {
        cerr << "Invalid parameters" << endl;
        exit(1);
    }

    pixelVector[x][y].b = blue;
}
int ppmImage::get_red_pixel(int x, int y) const
{
    if (x >= height || x < 0 || y >= width || y < 0)
    { // Making sure the given i and j values are valid

        cerr << "Invalid parameters" << endl;
        exit(1);
    }

    return pixelVector[x][y].r;
}
int ppmImage::get_green_pixel(int x, int y) const
{
    if (x >= height || x < 0 || y >= width || y < 0)
    { // Making sure the given ia nd j values are valid

        cerr << "Invalid parameters" << endl;
        exit(1);
    }
    return pixelVector[x][y].g;
}
int ppmImage::get_blue_pixel(int x, int y) const
{
    if (x >= height || x < 0 || y >= width || y < 0)
    { // Making sure the given ia nd j values are valid

        cerr << "Invalid parameters" << endl;
        exit(1);
    }

    return pixelVector[x][y].b;
}

void ppmImage::print_image_dimensions() const
{ // Function to print image dimensions to stdout
    cout << "IMAGE DIMENSIONS:" << endl;
    cout << "Height: " << height << " Width: " << width << endl;
}

void ppmImage::set_height_width(int h, int w)
{ // Function to set onlythe height and widht

    if (h < 0 || w < 0)
    {
        cerr << "Invalid Parameter." << endl;
        exit(1);
    }
    height = h;
    width = w;

    pixelVector = vector<vector<Pixel>>(height, vector<Pixel>(width));
}

void ppmImage::set_max_color_value(int maxColor) { maxColorVal = maxColor; }

void ppmImage::set_header_info(int h, int w, string magicNo, int maxVal)
{ // Function to set allt he header information

    if (h < 0 || w < 0)
    { // Making sure athe height and width information id= valid
        cerr << "Invalid Parameter." << endl;
        exit(1);
    }

    height = h;
    width = w;
    magicNumber = magicNo;
    maxColorVal = maxVal;

    pixelVector = vector<vector<Pixel>>(height, vector<Pixel>(width));
}

void ppmImage::set_pixel_values(vector<vector<Pixel>> pixels) { this->pixelVector = pixels; }

void ppmImage::set_pixels(int row, int col, Pixel pixel)
{ /*Function to set pixels in a specific index*/
    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        cerr << "Out of bounds" << endl;
        exit(1);
    }

    this->pixelVector[row][col] = pixel;
}

int ppmImage::open_image_file()
{ /*Function to open a file*/
    cout << "Enter the file you would like to open" << endl;
    string s;
    cin >> s;
    filename = s;
    set_image_filename(s);

    // If thes file could not be opened
    ifstream imageFile(filename);
    if (!imageFile.is_open())
    {
        cerr << "Failed to open file." << endl;
        set_image_filename("\0");
        return 0;
    }
    vector<string> fileVector;                 // string vector to store the file data without error or comments
    delete_comments(imageFile, fileVector);    // Checking the file for comments and deleting them
    bool check = check_fileheader(fileVector); // Check the file header to make sure htere are no errors
    if (check == false)                        // Close the file and return to the menu if the file type is not valid
    {
        imageFile.close();
        return 0;
    }

    pixelVector.clear();          // Clearing the vector to make sure the last opened imnage is deleted
    set_pixel_values(fileVector); // Copy the pixel values to local object vector

    imageFile.close(); // closing file

    return 1;
}
void ppmImage::save_as_file() const
{ // Funciton to save a file

    // getting new filename from user
    cout << "Enter filename to save file" << endl;
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
            newImageFile << pixelVector[i][j].r << " "
                         << pixelVector[i][j].g << " "
                         << pixelVector[i][j].b << endl;
        }
    }

    newImageFile.close();
}

ppmImage ppmImage::operator+(const ppmImage &other) const
{
    if (this->height != other.height || this->width != other.width)
    { // IF height or width of two images dont match
        ppmImage invalid(0, 0);
        invalid.filename = "INVALID";
        cout << "Invalid image dimensions" << endl;
        return invalid;
    }

    // Create a new image to be returnewd
    ppmImage returnVal(other.height, other.width, other.maxColorVal);
    returnVal.magicNumber = this->magicNumber;

    for (int i = 0; i < returnVal.height; i++)
    {
        for (int j = 0; j < returnVal.width; j++)
        {
            int r, g, b;

            // adding pixels
            r = this->pixelVector[i][j].r + other.pixelVector[i][j].r;
            g = this->pixelVector[i][j].g + other.pixelVector[i][j].g;
            b = this->pixelVector[i][j].b + other.pixelVector[i][j].b;

            // Making sure the pixels are not over or under saturated
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

            // PLacing new pixels into the vector
            returnVal.pixelVector[i][j] = {r, g, b};
        }
    }

    return returnVal;
}
ppmImage ppmImage::operator-(const ppmImage &other) const
{ // Subtractig images pixels

    if (this->height != other.height || this->width != other.width)
    { // Making sure the height and width of images match
        ppmImage invalid(0, 0);
        invalid.filename = "INVALID";
        cout << "Invalid image dimensions" << endl;
        return invalid;
    }

    // Creating a new image object to return
    ppmImage returnVal(other.height, other.width, other.maxColorVal);
    returnVal.magicNumber = this->magicNumber;

    for (int i = 0; i < returnVal.height; i++)
    {
        for (int j = 0; j < returnVal.width; j++)
        {
            int r, g, b;

            // adding pixels
            r = this->pixelVector[i][j].r - other.pixelVector[i][j].r;
            g = this->pixelVector[i][j].g - other.pixelVector[i][j].g;
            b = this->pixelVector[i][j].b - other.pixelVector[i][j].b;

            // Making sure the pixels arent under or over saturated
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

            // Putting the new pixels int eh vector
            returnVal.pixelVector[i][j] = {r, g, b};
        }
    }
    return returnVal;
}
int &ppmImage::operator()(int row, int col, int channel)
{ // Function call operator reutnrs the address of a specific color channlein a specific index

    if (row < 0 || row >= height || col < 0 || col >= width || channel < 1 || channel > 3)
    { // Making sure the indices are withing the bounds
        cerr << "Out of bounds error!" << endl;
        exit(1);
    }

    if (channel == 1)
        return pixelVector[row][col].r;

    else if (channel == 2)
        return pixelVector[row][col].g;

    else if (channel == 3)
        return pixelVector[row][col].b;

    else
    { // If the channel is wrong
        cerr << "Undefined error" << endl;
        exit(1);
    }
}
ostream &operator<<(ostream &os, const ppmImage &image)
{ // Prints the pixel vector to stdout
    cout << image.magicNumber << endl;
    cout << image.height << " " << image.width << endl;
    cout << image.maxColorVal << endl;
    const int maxDigit = 3;

    for (int i = 0; i < image.height; i++)
    {
        for (int j = 0; j < image.width; j++)
        {
            // Printing the pixels and calculatingt he number of digits in order to format the spaces and output to make it readable
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
int read_ppm(const string source_ppm_file_name, ppmImage &destination_object);
int write_ppm(const string destination_ppm_file_name, const ppmImage &source_object);
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);
int test_print(const string filename_image1);
int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice);
ppmImage single_color(const ppmImage &source, int color_choice);

int main(int argc, char **argv)
{
    // Check for command line arguments
    // the first argumetn is going to be choice number
    // the second argument is going to be a ppm_file_name_1
    // the third argument is going to be a ppm_file_name_2 (optional)

    if (argc < 2)
    {
        cerr << "Insufficient arguments" << endl;
        exit(1);
    }

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
    else if ((choice == "1" || choice == "2") && argc != 5)
    {
        cerr << "Invalid Arguments" << endl;
        exit(1);
    }

    // if choice number is 3
    if (choice == "3" && argc == 3)
    {
        string ppm_file_name1(argv[2]);
        ppmImage destination;

        int returnRead = read_ppm(ppm_file_name1, destination);
        if (returnRead == 0)
            exit(1);

        swap_channels(destination, 2);

        int returnWrite = write_ppm("ppm_file_name2", destination);
        if (returnWrite == 0)
            exit(1);
    }

    // If choice is number 4
    if (choice == "4" && argc == 3)
    {
        string ppm_file_name1(argv[2]);
        ppmImage destination;

        int returnVal = read_ppm(ppm_file_name1, destination);
        if (returnVal == 0)
            exit(1);

        swap_channels(destination, 3);

        int returnWrite = write_ppm("ppm_file_name2", destination);
        if (returnWrite == 0)
            exit(1);
    }

    // If choice is number 5
    if (choice == "5" && argc == 3)
    {
        string ppm_file_name1(argv[2]);
        ppmImage destination;
        int readCheck = read_ppm(ppm_file_name1, destination);
        if (readCheck == 0)
            exit(1);
        // Create a new object which only contains RED channel data of the file read
        ppmImage source = single_color(destination, 1);
        int writeCheck = write_ppm("ppm_file_name2", source);
        if (!writeCheck)
            exit(1);
    }

    // If choice is number 6
    if (choice == "6" && argc == 3)
    {
        string ppm_file_name1(argv[2]);
        ppmImage destination;
        int readCheck = read_ppm(ppm_file_name1, destination);
        if (readCheck == 0)
            exit(1);

        // Create a new object which only contains RED channel data of the file read
        ppmImage source = single_color(destination, 2);

        int writeCheck = write_ppm("ppm_file_name2", source);
        if (writeCheck == 0)
            exit(1);
    }

    // If choice is number 7
    if (choice == "7" && argc == 3)
    {
        string ppm_file_name1(argv[2]);
        ppmImage destination;
        int readCheck = read_ppm(ppm_file_name1, destination);
        if (readCheck == 0)
            exit(1);
        // Create a new object which only contains RED channel data of the file read
        ppmImage source = single_color(destination, 3);

        int writeCheck = write_ppm("ppm_file_name2", source);
        if (writeCheck == 0)
            exit(1);
    }

    else if ((choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7") && argc != 3)
    {
        cerr << "Invalid Arguments" << endl;
        exit(1);
    }

    else if ((choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7" && choice != "1" && choice != "2"))
    {
        cerr << "Invalid Arguments" << endl;
        exit(1);
    }

    /*
        // Opening and closing files using member functions
        ppmImage image;
        int checkFile = image.open_image_file();
        if (checkFile)
        {
            image.save_as_file();
        }

        // Testing print function
        string filename(argv[2]);
        test_print(filename);

        return 0;
    */
}

int test_addition(const string filename_image1, const string filename_image2, const string filename_image3)
{
    // Creating new objects from the provided filenames
    ppmImage image1(filename_image1), image2(filename_image2), image3;

    if (image1.get_max_color_val() != image2.get_max_color_val())
    {
        cerr << "Maximum Color Values of images do not match. Please enter valid images" << endl;
        return 0;
    }

    // Image 3 is set after the first two images are createed to make sure there are no errors
    image3.set_max_color_value(image1.get_max_color_val());
    image3.set_height_width(image1.get_height(), image1.get_width());
    image3.set_magic_number("P3");

    // Addition operation
    image3 = image1 + image2;

    write_ppm(filename_image3, image3);
    return 1;
}

int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3)
{
    // Creating new objects forom the procided filenames
    ppmImage image1(filename_image1), image2(filename_image2), image3;

    if (image1.get_max_color_val() != image2.get_max_color_val())
    { // Checkign if color values match
        cerr << "Maximum Color Values of images do not match. Please enter valid images" << endl;
        exit(1);
    }

    // filling iage 3 object after image 2 and 1 are successfully created to avoid errors
    image3.set_max_color_value(image1.get_max_color_val());
    image3.set_height_width(image1.get_height(), image1.get_width());
    image3.set_magic_number("P3");

    // Subtraction operation
    image3 = image1 - image2;

    write_ppm(filename_image3, image3);

    return 1;
}

int test_print(const string filename_image1)
{ // Function to test hte ouytput operator

    // Creating object from image file name
    ppmImage image(filename_image1);

    // Printing to stdout twice to demonstrate cascading ability of overloaded operator
    cout << image << endl
         << image;

    return 1;
}

int write_ppm(const string destination_ppm_file_name, const ppmImage &source_object)
{
    // If there is no such file, or if the addition was unsuccesful for any reason, do not create any file and end the program
    if (source_object.get_filename() == "INVALID")
        return 0;

    // creating output stream file for out destination file
    ofstream newImageFile(destination_ppm_file_name);

    /* Storing header information into the new file */
    newImageFile << source_object.get_magic_number() << endl
                 << source_object.get_height() << " "
                 << source_object.get_width() << endl
                 << source_object.get_max_color_val() << endl;

    /* Copying the pixel values to the new file */
    const int maxDigit = 3;
    for (int i = 0; i < source_object.get_height(); i++)
    {
        for (int j = 0; j < source_object.get_width(); j++)
        {
            // Printing the pixels and calculatingt he number of digits in order to format the spaces and output to make it readable
            newImageFile << source_object.get_red_pixel(i, j);
            for (int k = 0; k < maxDigit - numDigits(source_object.get_red_pixel(i, j)); k++)
                newImageFile << " ";

            newImageFile << " ";
            newImageFile << source_object.get_green_pixel(i, j);
            for (int k = 0; k < maxDigit - numDigits(source_object.get_green_pixel(i, j)); k++)
                newImageFile << " ";

            newImageFile << " ";
            newImageFile << source_object.get_blue_pixel(i, j);
            for (int k = 0; k < maxDigit - numDigits(source_object.get_blue_pixel(i, j)); k++)
                newImageFile << " ";

            newImageFile << "\t\t";
        }
        newImageFile << endl;
    }

    newImageFile.close();
    return 1;
}

int read_ppm(const string source_ppm_file_name, ppmImage &destination_object)
{
    // Opening and error-checking the file
    ifstream sourceFile(source_ppm_file_name);
    if (!sourceFile.is_open())
    {
        cerr << "Could not open file." << endl;

        return 0;
    }

    string magicNumber;
    string height, width, maxColorVal;

    sourceFile >> magicNumber >> width >> height >> maxColorVal;

    if ((!is_all_digit(height) || !is_all_digit(width) || !is_all_digit(maxColorVal)))
    { // MAking sure the file contents are valid
        cerr << "Invalid file contents." << endl;
        return 0;
    }

    if (magicNumber != "P3")
    { // Making sure image type is valid
        cerr << "Invalid File" << endl;
        return 0;
    }

    // Converting information strings to int
    int heightNum = stoi(height), widthNum = stoi(width), maxColorValNum = stoi(maxColorVal);

    // setting header informatrion for the image object
    destination_object.set_header_info(heightNum, widthNum, magicNumber, maxColorValNum);

    // Getting the pixels fromt he file and placingt hem int eh obe=jects vector
    for (int i = 0; i < heightNum; i++)
    {
        for (int j = 0; j < widthNum; j++)
        {
            int r, g, b;
            sourceFile >> r >> g >> b;
            destination_object.set_pixels(i, j, {r, g, b});
        }
    }

    sourceFile.close();
    return 1;
}

int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice)
{
    // Swap choice 1: red and green
    if (swap_choice == 1)
    {
        for (int i = 0; i < image_object_to_be_modified.get_height(); i++)
        {
            for (int j = 0; j < image_object_to_be_modified.get_width(); j++)
            {
                int temp = image_object_to_be_modified(i, j, 1);
                image_object_to_be_modified.set_red_pixel(i, j, image_object_to_be_modified.get_green_pixel(i, j));
                image_object_to_be_modified.set_green_pixel(i, j, temp);
            }
        }
    }

    // Swap choice 2: red and blue
    if (swap_choice == 2)
    {
        for (int i = 0; i < image_object_to_be_modified.get_height(); i++)
        {
            for (int j = 0; j < image_object_to_be_modified.get_width(); j++)
            {
                int temp = image_object_to_be_modified(i, j, 1);
                image_object_to_be_modified.set_red_pixel(i, j, image_object_to_be_modified.get_blue_pixel(i, j));
                image_object_to_be_modified.set_blue_pixel(i, j, temp);
            }
        }
    }

    // Swap choice 3: green and blue
    if (swap_choice == 3)
    {
        for (int i = 0; i < image_object_to_be_modified.get_height(); i++)
        {
            for (int j = 0; j < image_object_to_be_modified.get_width(); j++)
            {
                int temp = image_object_to_be_modified(i, j, 2);
                image_object_to_be_modified.set_green_pixel(i, j, image_object_to_be_modified.get_blue_pixel(i, j));
                image_object_to_be_modified.set_blue_pixel(i, j, temp);
            }
        }
    }

    return 1;
}

ppmImage single_color(const ppmImage &source, int color_choice)
{
    ppmImage retVal(source);

    if (color_choice == 1)
    {
        for (int i = 0; i < retVal.get_height(); i++)
        {
            for (int j = 0; j < retVal.get_width(); j++)
            {
                retVal.set_green_pixel(i, j, 0);
                retVal.set_blue_pixel(i, j, 0);
            }
        }
    }

    else if (color_choice == 2)
    {
        for (int i = 0; i < retVal.get_height(); i++)
        {
            for (int j = 0; j < retVal.get_width(); j++)
            {
                retVal.set_red_pixel(i, j, 0);
                retVal.set_blue_pixel(i, j, 0);
            }
        }
    }

    else if (color_choice == 3)
    {
        for (int i = 0; i < retVal.get_height(); i++)
        {
            for (int j = 0; j < retVal.get_width(); j++)
            {
                retVal.set_green_pixel(i, j, 0);
                retVal.set_red_pixel(i, j, 0);
            }
        }
    }

    return retVal;
}