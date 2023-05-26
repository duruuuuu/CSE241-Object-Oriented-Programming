#include "CatalogHandler.h"
#include "Book.h"
#include "Movie.h"
#include "Music.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{

    // Opening the file, getting the category type nad closingt he file for now.
    ifstream inputFile("data.txt");
    if (!inputFile)
    {
        cerr << "Failed to open file" << endl;
        exit(1);
    }
    string catalogType;
    inputFile >> catalogType;
    inputFile.close();

    ofstream output("output.txt");
    if (output.is_open())
    {
        // Writing the catalog type to the output file
        output << "Catalog read: " << catalogType << endl;
        output.close();
    }

    // Deciding which type the category handler needs to be created as.
    if (catalogType == "book" || catalogType == "Book" || catalogType == "BOOK")
    {
        CatalogHandler<Book> catalogHandler;

        // TODO Create a function for this part
        catalogHandler.catalog_read();
        catalogHandler.read_commands();
    }

    else if (catalogType == "movie" || catalogType == "Movie" || catalogType == "MOVIE")
    {
        CatalogHandler<Movie> catalogHandler;
        catalogHandler.catalog_read();
        catalogHandler.read_commands();
    }

    if (catalogType == "music" || catalogType == "Music" || catalogType == "MUSIC")
    {
        CatalogHandler<Music> catalogHandler;
        catalogHandler.catalog_read();
        catalogHandler.read_commands();
    }
}