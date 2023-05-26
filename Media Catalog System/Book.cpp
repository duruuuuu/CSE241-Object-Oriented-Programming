#include "Book.h"
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

Book::Book()
{
    // Intentionally left empty
}

Book::Book(string ti, string a, string y, string ta)
    : title(ti), authors(a), year(y), tags(ta)
{
    // Intentionally left empty
}

Book::Book(string line)
{
    // Constructor that takes a line of data and parses it to create an entry
    vector<string> parsedItems;
    istringstream iss(line);
    string item;

    while (getline(iss, item, '\"'))
    {
        // cout << "ITEM: " << item << endl;
        parsedItems.push_back(item);
    }

    // TODO IMPLEMENT EXCEPTION MISSING FIELD
    if (parsedItems.size() < 7)
    {
        cerr << "Missing Field" << endl;
        cout << line << endl;
        return;
    }

    title = parsedItems[1];
    authors = parsedItems[3];
    year = parsedItems[5];
    tags = parsedItems[7];
}

string Book::get_title() const { return title; }

string Book::get_year() const { return year; }

string Book::get_authors() const { return authors; }

string Book::get_tags() const { return tags; }

void Book::set_title(string s) { title = s; }

void Book::set_year(string s) { year = s; }

void Book::set_authors(string s) { authors = s; }

void Book::set_tags(string s) { tags = s; }

void Book::print_all() const
{
    std::ofstream output("output.txt", std::ios::app);

    if (output.is_open())
    {
        output << "\"" << title << "\" "
               << "\"" << authors << "\" "
               << "\"" << year << "\" "
               << "\"" << tags << "\""
               << endl;

        output.close();
    }
}

template <typename Field>
bool Book::search_substr(string &str, Field field, string &fieldStr)
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

bool Book::search(string str, string field)
{
    if (field == "\"title\"")
        return search_substr(str, title, field);

    else if (field == "\"year\"")
        return search_substr(str, year, field);

    else if (field == "\"authors\"")
        return search_substr(str, authors, field);

    else if (field == "\"tags\"")
        return search_substr(str, tags, field);

    // TODO HANDLE WRONG COMMAND EXCEPTION
    else
        return false;
}

void Book::sort(string field)
{
    cout << "sorting...";
}