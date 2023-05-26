#include "Movie.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>

using std::cerr;
using std::cout;
using std::endl;
using std::getline;
using std::istringstream;
using std::regex;
using std::regex_search;
using std::string;
using std::vector;

Movie::Movie()
{
    // Intentionally left blank
}

Movie::Movie(string ti, string d, string y, string g, string s)
    : title(ti), director(d), year(y), genre(g), starring(s)
{
    // Intentionally left blank
}

Movie::Movie(string line)
{
    vector<string> parsedItems;
    istringstream iss(line);
    string item;

    while (getline(iss, item, '\"'))
        parsedItems.push_back(item);

    // TODO IMPLEMENT EXCEPTION MISSING FIELD
    if (parsedItems.size() < 9)
    {
        cerr << "Missing Field" << endl;
        cout << line << endl;
        return;
    }

    title = parsedItems[1];
    director = parsedItems[3];
    year = parsedItems[5];
    genre = parsedItems[7];
    starring = parsedItems[9];
}

string Movie::get_title() const { return title; }

string Movie::get_year() const { return year; }

string Movie::get_director() const { return director; }

string Movie::get_genre() const { return genre; }

string Movie::get_starring() const { return starring; }

void Movie::set_title(string s) { title = s; }

void Movie::set_year(string s) { year = s; }

void Movie::set_director(string s) { director = s; }

void Movie::set_genre(string s) { genre = s; }

void Movie::set_starring(string s) { starring = s; }

void Movie::print_all() const
{
    std::ofstream output("output.txt", std::ios::app);

    if (output.is_open())
    {
        output << "\"" << title << "\" "
               << "\"" << director << "\" "
               << "\"" << year << "\" "
               << "\"" << genre << "\" "
               << "\"" << starring << "\""
               << endl;

        output.close();
    }
}

template <typename Field>
bool Movie::search_substr(string &str, Field field, string &fieldStr)
{
    // Erasing the double quotes from the search keyword
    str.erase(str.begin());
    str.erase(str.end() - 1);

    regex pattern(str);
    bool match = regex_search(field, pattern);

    if (match)
    {
        std::ofstream output("output.txt", std::ios::app);
        if (output.is_open())
        {
            output << "search \"" << str << "\" in " << fieldStr << endl;
            output.close();
        }
        print_all();
    }
    return true;
}

bool Movie::search(string str, string field)
{
    if (field == "\"title\"")
        return search_substr(str, title, field);

    else if (field == "\"year\"")
        return search_substr(str, year, field);

    else if (field == "\"director\"")
        return search_substr(str, director, field);

    else if (field == "\"genre\"")
        return search_substr(str, genre, field);

    else if (field == "\"starring\"")
        return search_substr(str, starring, field);

    // TODO HANDLE WRONG COMMAND EXCEPTION
    else
        return false;
}

void Movie::sort(string field)
{
    cout << "sorting...";
}