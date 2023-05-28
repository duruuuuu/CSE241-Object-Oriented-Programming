#include "Book.h"

Book::Book()
{
    // Intentionally left empty
}

Book::Book(string line)
{
    vector<string> parsedItems;
    istringstream iss(line);
    string item;

    while (getline(iss, item, '\"'))
    {
        parsedItems.push_back(item);
    }

    title = parsedItems[1];
    authors = parsedItems[3];
    year = parsedItems[5];
    tags = parsedItems[7];
}

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

bool Book::search(string str, string field)
{
    if (field == "title")
        return search_substr(str, title, field);

    else if (field == "year")
        return search_substr(str, year, field);

    else if (field == "authors")
        return search_substr(str, authors, field);

    else if (field == "tags")
        return search_substr(str, tags, field);

    else
        return false;
}

std::function<bool(const Book &, const Book &)> Book::get_compare_func(const string &field) const
{
    if (field == "title")
        return &compare_by_title;

    else if (field == "authors")
        return &compare_by_author;

    else if (field == "year")
        return &compare_by_year;

    else if (field == "tags")
        return &compare_by_tags;

    // Exception is handled outside of the dunctoin, this else statement is used only to satisfy the return of the function
    else
        return &compare_by_title;
};
