#ifndef _CATALOGHANDLER_H_
#define _CATALOGHANDLER_H_

#include <unordered_map>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <algorithm>
#include "Book.h"
#include "Music.h"
#include "Movie.h"

using namespace std;

/**
 * @class CatalogHandler CatalogHandler.h
 * @brief Manages a catalog based on ts type read from a file.
 * @tparam T Type of catalog
 */
template <typename T>
class CatalogHandler
{
public:
    CatalogHandler()
    {
        // Intentionally left empty
    }

    void set_catalog_type(string s) { catalogType = s; }

    string get_catalog_type() const { return catalogType; }

    /**
     *  @brief Stores catalog entries without duplicates and without errors
     */
    void catalog_read()
    {
        // Opening the file and making sure it is opened succesfully
        ifstream dataFile("data.txt");
        if (!dataFile)
        {
            cerr << "File Failed to Open" << endl;
            exit(1);
        }

        // Parsing the lines and storing them in the map
        string line, title;
        getline(dataFile, line);
        catalogType = line;
        while (getline(dataFile, line))
        {
            istringstream iss(line);
            getline(iss, title, '\"');
            getline(iss, title, '\"');

            // TODO IMPLEMENT DUPLICATE ENTRY EXCEPTION
            if (catalogList.count(title) > 0)
            {
                cout << "Duplicate entry detected: " << title << endl;
                continue;
            }
            catalogList[title] = T(line);
        }
        dataFile.close();
    }

    /**
     * @brief Excecutes commands from file and
     */
    void read_commands()
    {
        ifstream commandsFile("commands.txt");
        if (!commandsFile)
        {
            cerr << "File Failed to Open" << endl;
            exit(1);
        }

        string line, command;
        while (getline(commandsFile, line))
        {
            istringstream iss(line);
            iss >> command;

            if (command == "search")
            {
                // TODO UPDATE TO SUPPORT SEARCHING PHRASES NOT JUST WORDS!
                string searchString, trash, field;
                iss >> searchString >> trash >> field;

                for (auto it = catalogList.begin(); it != catalogList.end(); it++)
                {
                    bool check = it->second.search(searchString, field);
                    if (!check)
                    {
                        // TODO Write exception Command is Wrong
                        cout << "Exception: command is wrong" << endl;
                        cout << line << endl;
                        break;
                    }
                }
            }
            else if (command == "sort")
            {
                string field;
                iss >> field;
                // sort_by_field(field);
            }
        }
    }

private:
    string catalogType;                   // stores the type of catalog (Book, Movie, or Music)
    unordered_map<string, T> catalogList; // Map template to configure the list for whatever the catalog type is
};

#endif // _CATALOGHANDLER_H_