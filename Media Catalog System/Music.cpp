#include "Music.h"

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
    vector<string> parsedItems;
    istringstream iss(line);
    string item;

    while (getline(iss, item, '\"'))
        parsedItems.push_back(item);

    title = parsedItems[1];
    artists = parsedItems[3];
    year = parsedItems[5];
    genre = parsedItems[7];
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

    regex pattern(str);
    bool match = regex_search(field, pattern);

    if (match)
    {
        std::ofstream output("output.txt", std::ios::app);
        if (output.is_open())
        {
            output << "search \"" << str << "\" in \"" << fieldStr << "\"" << endl;
            output.close();
        }
        print_all();
    }
    return true;
}

bool Music::search(string str, string field)
{
    if (field == "title")
        return search_substr(str, title, field);

    else if (field == "year")
        return search_substr(str, year, field);

    else if (field == "artists")
        return search_substr(str, artists, field);

    else if (field == "genre")
        return search_substr(str, genre, field);

    // TODO HANDLE WRONG COMMAND EXCEPTION
    else
        return false;
}

std::function<bool(const Music &, const Music &)> Music::get_compare_func(const string &field) const
{
    if (field == "title")
        return &compare_by_title;

    else if (field == "artists")
        return &compare_by_artists;

    else if (field == "year")
        return &compare_by_year;

    else if (field == "genre")
        return &compare_by_genre;

    // Default comaprison function if field is not recognized
    else
        return &compare_by_title;
}