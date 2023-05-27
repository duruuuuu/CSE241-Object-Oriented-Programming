#include "Music.h"
#include "Exceptions.h"
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

Music::Music()
{
    // Intentionally left blank
}
Music::Music(string t, string a, string y, string g)
    : title(t), artists(a), year(y), genre(g)
{
    // Intentionally left blank
}

Music::Music(string line)
{
    try
    {
        vector<string> parsedItems;
        istringstream iss(line);
        string item;

        while (getline(iss, item, '\"'))
            parsedItems.push_back(item);

        if (parsedItems.size() < 7)
            throw MissingField(line);

        title = parsedItems[1];
        artists = parsedItems[3];
        year = parsedItems[5];
        genre = parsedItems[7];
    }
    catch (MissingField e)
    {
        std::ofstream output("output.txt", std::ios::app);

        e.what(output);

        output.close();

        return;
    }
}

string Music::get_title() const { return title; }

string Music::get_artists() const { return artists; }

string Music::get_year() const { return year; }

string Music::get_genre() const { return genre; }

void Music::set_title(string s) { title = s; }

void Music::set_artists(string s) { artists = s; }

void Music::set_year(string s) { year = s; }

void Music::set_genre(string s) { genre = s; }

void Music::print_all() const
{
    std::ofstream output("output.txt", std::ios::app);
    if (output.is_open())
    {
        cout << "\"" << title << "\" "
             << "\"" << artists << "\" "
             << "\"" << year << "\" "
             << "\"" << genre << "\""
             << endl;
        output.close();
    }
}

template <typename Field>
bool Music::search_substr(string &str, Field field, string &fieldStr)
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

bool Music::search(string str, string field)
{
    if (field == "\"title\"")
        return search_substr(str, title, field);

    else if (field == "\"year\"")
        return search_substr(str, year, field);

    else if (field == "\"artists\"")
        return search_substr(str, artists, field);

    else if (field == "\"genre\"")
        return search_substr(str, genre, field);

    // TODO HANDLE WRONG COMMAND EXCEPTION
    else
        return false;
}

void Music::sort(string field)
{
    cout << "sorting...";
}