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
#include "Exceptions.h"

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
        try
        {
            // Opening the file and making sure it is opened succesfully
            ifstream dataFile("data.txt");
            if (!dataFile)
            {
                cerr << "File Failed to Open" << endl;
                throw FileFail();
            }

            // Parsing the lines
            string line;
            getline(dataFile, line);
            catalogType = line;
            // Storing data line-by-line
            while (getline(dataFile, line))
                store_line(line);

            // Printing the number of unique entries to the output file
            ofstream output("output.txt", std::ios::app);
            output << catalogList.size() << " unique entries" << endl;
            output.close();
            dataFile.close();
        }
        catch (FileFail e)
        {
            e.what();
        }
    }

    /**
     * @brief Excecutes commands from file and writes results to output file
     */
    void read_commands()
    {
        try
        {
            ifstream commandsFile("commands.txt");
            if (!commandsFile)
            {
                cerr << "File Failed to Open" << endl;
                throw FileFail();
            }

            // If the file is opened successfully, run the commands line-by-line
            string line, command;
            while (getline(commandsFile, line))
                run_command(line);
        }
        catch (FileFail e)
        {
            e.what();
        }
    }

private:
    string catalogType;                   // stores the type of catalog (Book, Movie, or Music)
    unordered_map<string, T> catalogList; // Map template to configure the list for whatever the catalog type is

    /**
     * @brief Function to count the number of fields in an entry
     * @param line Reference to the string line of entry
     * @return true if the field count is right for its categroy, false if not
     */
    bool count_fields(const string &line)
    {
        char target = '\"';
        int oCount = count(line.begin(), line.end(), target);

        if (catalogType == "book" || catalogType == "music")
        {
            if (oCount == 8)
                return true;
            else
                return false;
        }

        else if (catalogType == "movie")
        {
            if (oCount == 10)
                return true;
            else
                return false;
        }

        else
            return false;
    }

    /**
     * @brief Stores the catalog entry in the CatalogHandler's system
     * @param line Reference to the entry line read from the file
     * @exception Duplicate entry or missing fields in entry
     */
    void store_line(const string &line)
    {
        try
        {
            bool fieldCount = count_fields(line);
            if (!fieldCount)
                throw MissingField(line);

            // Extracting the title of the entry adn cehcking if there are any duplicates
            string title;
            istringstream iss(line);
            getline(iss, title, '\"');
            getline(iss, title, '\"');
            if (catalogList.count(title) > 0)
                throw DuplicateEntry(line);

            // Placing entry to the map
            catalogList[title] = T(line);
        }
        catch (DuplicateEntry e)
        {
            e.what();
        }
        catch (MissingField e)
        {
            e.what();
        }
    }

    bool check_field(const string &field)
    {
        if (field != "title" && field != "year" && field != "authors" &&
            field != "director" && field != "artists" && field != "starring" &&
            field != "genre" && field != "tags")
            return false;

        else
            return true;
    }
    /**
     * @brief Implementing the commands read from file
     * @param line Reference to the line of command read from the file
     * @exception Invalid field types
     */
    void run_command(const string &line)
    {
        try
        {
            istringstream iss(line);
            string command;
            iss >> command;

            if (command == "search")
            {
                string searchStr, searchField;
                // Getting the string to be searched
                getline(iss, searchStr, '\"');
                getline(iss, searchStr, '\"');
                // Getting field to be searched in
                getline(iss, searchField, '\"');
                getline(iss, searchField, '\"');

                for (auto it = catalogList.begin(); it != catalogList.end(); it++)
                {
                    bool check = it->second.search(searchStr, searchField);
                    if (!check)
                        throw WrongCommand(line);
                }
            }

            else if (command == "sort")
            {
                // extracting the field that will be sorted
                string field;
                getline(iss, field, '\"');
                getline(iss, field, '\"');

                bool check = check_field(field);
                if (!check)
                    throw WrongCommand(line);

                sort_by_field(field);
            }
        }

        catch (WrongCommand e)
        {
            e.what();
        }
    }

    /**
     * @brief function to sort the map
     * @param field string reference of the field to be sorted by
     */
    void sort_by_field(const string &field)
    {
        // lambda function using field we got from the file
        auto compareFunc = [field](const T &item1, const T &item2)
        {
            return item1.get_compare_func(field)(item1, item2);
        };

        // Iterate over the map and copy the values to a temnporary storage
        std::vector<T> tempVec;
        for (const auto &pair : catalogList)
            tempVec.push_back(pair.second);

        // Srting the temporrary vector using out lamba function
        sort(tempVec.begin(), tempVec.end(), compareFunc);

        // Printing the command to the output file
        ofstream output("output.txt", std::ios::app);
        output << "sort by \"" << field << "\"" << endl;
        output.close();

        for (const auto &item : tempVec)
            item.print_all();
    }
};

#endif // _CATALOGHANDLER_H_