#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>

using std::string;

class Book
{
public:
    template <typename U>
    friend class CatalogHandler;

    Book();
    Book(string line); // Constructor that takes a line of data and parses it to create an entry

    // Getter functions
    string get_title() const;
    string get_year() const;
    string get_authors() const;
    string get_tags() const;

    // Setter functions
    void set_title(string s);
    void set_year(string s);
    void set_authors(string s);
    void set_tags(string s);

    /**
     * @brief Search fundtion to look for a keyword in a specific field
     * @param str the keyword being searched
     * @param field the field that the keyword is being searched in
     */
    bool search(string str, string field);
    void sort(string field);

private:
    string title;
    string authors;
    string year;
    string tags;

    /**
     * @brief Prints all the information about the book
     */
    void print_all() const;

    /**
     * @brief Looks for a substring in a string.
     * @tparam Field  Field that the substring is being searched in
     * @param str reference to the subtring to be searched
     * @param fieldStr field in string form (used to print the word)
     * @return true if the substring is found, false if not
     */
    template <typename Field>
    bool search_substr(string &str, Field field, string &fieldStr);
};

#endif //_BOOK_H_