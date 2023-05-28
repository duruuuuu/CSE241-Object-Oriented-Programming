#ifndef _BOOK_H_
#define _BOOK_H_

#include "Exceptions.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>

using namespace std;

class Book
{
public:
    Book();
    Book(string line); // Constructor that takes a line of data and parses it to create an entry

    // Getter functions
    string get_title() const { return title; }
    string get_year() const { return year; }
    string get_authors() const { return authors; }
    string get_tags() const { return tags; }

    // Setter functions
    void set_title(string s) { title = s; }
    void set_year(string s) { year = s; }
    void set_authors(string s) { authors = s; }
    void set_tags(string s) { tags = s; }

    /**
     * @brief Search function to look for a keyword in a specific field
     * @param str the keyword being searched
     * @param field the field that the keyword is being searched in
     * @return true if the word is found, false if the field is invalid
     */
    bool search(string str, string field);

    /**
     * @brief finds the correct sorting function according tot he given field
     * @param field reference to a string that indicates the field
     * @return returns the corresponding function that sorts according to the given field
     * @exception invalid command/field to be sorted
     */
    std::function<bool(const Book &, const Book &)> get_compare_func(const string &field) const;

    /**
     * @brief Prints all the information about the book
     */
    void print_all() const;

private:
    string title;
    string authors;
    string year;
    string tags;

    /**
     * @brief Looks for a substring in a string.
     * @tparam Field  Field that the substring is being searched in
     * @param str reference to the subtring to be searched
     * @param fieldStr field in string form (used to print the word)
     * @return true if the substring is found, false if not
     */
    template <typename Field>
    bool search_substr(string &str, Field field, string &fieldStr);

    /* COMPARATOR FUNCTIONS */

    static bool compare_by_title(const Book &Book1, const Book &Book2)
    {
        return Book1.title < Book2.title;
    }
    static bool compare_by_author(const Book &Book1, const Book &Book2)
    {
        return Book1.authors < Book2.authors;
    }
    static bool compare_by_year(const Book &Book1, const Book &Book2)
    {
        return stoi(Book1.year) < stoi(Book2.year);
    }
    static bool compare_by_tags(const Book &Book1, const Book &Book2)
    {
        return Book1.tags < Book2.tags;
    }
};

#endif //_BOOK_H_