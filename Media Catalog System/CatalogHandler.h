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
        // Opening the file and making sure it is opened succesfully
        ifstream dataFile("data.txt");
        if (!dataFile)
        {
            cerr << "File Failed to Open" << endl;
            exit(1);
        }

        // Parsing the lines and storing them in the map
        string line;
        getline(dataFile, line);
        catalogType = line;
        while (getline(dataFile, line))
            store_line(line);

        ofstream output("output.txt", std::ios::app);
        output << catalogList.size() - 1 << " unique entries" << endl;
        output.close();
        dataFile.close();
    }

    /**
     * @
     * @brief Excecutes commands from file and writes results to output file
     */
    void read_commands()
    {
        // TODO create exception for fiel not opening
        ifstream commandsFile("commands.txt");
        if (!commandsFile)
        {
            cerr << "File Failed to Open" << endl;
            exit(1);
        }

        string line, command;
        while (getline(commandsFile, line))
            run_command(line);
    }

private:
    string catalogType;                   // stores the type of catalog (Book, Movie, or Music)
    unordered_map<string, T> catalogList; // Map template to configure the list for whatever the catalog type is

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

            string title;
            istringstream iss(line);
            getline(iss, title, '\"');
            getline(iss, title, '\"');
            if (catalogList.count(title) > 0)
                throw DuplicateEntry(line);

            catalogList[title] = T(line);
        }
        catch (DuplicateEntry e)
        {
            ofstream output("output.txt", std::ios::app);
            e.what(output);
            output.close();
        }
        catch (MissingField e)
        {
            ofstream output("output.txt", std::ios::app);
            e.what(output);
            output.close();
        }
    }

    /**
     * @brief Implementing the commands read from file
     * @param line Reference to the line of command read from the file
     * @exception Invalid field type
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

                sort_by_field(field);

                for (const auto &item : catalogList)
                    item.second.print_all();
            }
        }

        catch (WrongCommand e)
        {
            ofstream output("output.txt", std::ios::app);
            e.what(output);
            output.close();
        }
    }

    void sort_by_field(const string &field)
    {
        ofstream output("output.txt", std::ios::app);
        output << "sort by \"" << field << "\"" << endl;
        output.close();

        auto compareFunc = [field](const T &item1, const T &item2)
        {
            return item1.get_compare_func(field)(item1, item2);
        };

        // Iterate over the map and copy the values to the array
        std::vector<T> tempVec;
        for (const auto &pair : catalogList)
            tempVec.push_back(pair.second);
        tempVec.erase(tempVec.begin());

        sort(tempVec.begin(), tempVec.end(), compareFunc);

        catalogList.clear();
        for (const auto &item : tempVec)
            catalogList[item.title] = item;
    }
};

#endif // _CATALOGHANDLER_H_