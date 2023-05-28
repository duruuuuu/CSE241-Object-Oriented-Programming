#include "Movie.h"

Movie::Movie()
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

    title = parsedItems[1];
    director = parsedItems[3];
    year = parsedItems[5];
    genre = parsedItems[7];
    starring = parsedItems[9];
}

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

bool Movie::search(string str, string field)
{
    if (field == "title")
        return search_substr(str, title, field);

    else if (field == "year")
        return search_substr(str, year, field);

    else if (field == "director")
        return search_substr(str, director, field);

    else if (field == "genre")
        return search_substr(str, genre, field);

    else if (field == "starring")
        return search_substr(str, starring, field);

    else
        return false;
}

std::function<bool(const Movie &, const Movie &)> Movie::get_compare_func(const string &field) const
{
    if (field == "title")
        return &compare_by_title;

    else if (field == "director")
        return &compare_by_director;

    else if (field == "year")
        return &compare_by_year;

    else if (field == "genre")
        return &compare_by_genre;

    else if (field == "starring")
        return &compare_by_starring;

    // Exception is handled outside of the dunctoin, this else statement is used only to satisfy the return of the function
    else
        return &compare_by_title;
}