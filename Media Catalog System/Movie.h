#ifndef _MOVIE_H_
#define _MOVIE_H_

#include "Exceptions.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>

using namespace std;

class Movie
{
public:
    // Constructors
    Movie();
    Movie(string line);

    // Getter functions
    string get_title() const { return title; }
    string get_year() const { return year; }
    string get_director() const { return director; }
    string get_genre() const { return genre; }
    string get_starring() const { return starring; }

    // Setter functions
    void set_title(string s) { title = s; }
    void set_year(string s) { year = s; }
    void set_director(string s) { director = s; }
    void set_genre(string s) { genre = s; }
    void set_starring(string s) { starring = s; }

    /**
     * @brief Searches for a keyword in the list
     * @param str keyword to be searched
     * @param field field to search the keyword in
     * @return true if the word is found, false if the field is not found
     */
    bool search(string str, string field);

    /**
     * @brief finds the correct sorting function according tot he given field
     * @param field reference to a string that indicates the field
     * @return corresponding function that sorts according to the given field
     * @exception invalid command/field to be sorted
     */
    std::function<bool(const Movie &, const Movie &)> get_compare_func(const string &field) const;

    /**
     * @brief Prints all the information about the movie
     */
    void print_all() const;

private:
    string title;
    string director;
    string year;
    string genre;
    string starring;

    /**
     * @brief Looks for a substring in a string.
     * @tparam Field  Field that the substring is being searched in
     * @param &str reference to the subtring to be searched
     * @param &fieldStr field in string form (used to print the word)
     * @return true if the substring is found, false if not
     */
    template <typename Field>
    bool search_substr(string &str, Field field, string &fieldStr);

    static bool compare_by_title(const Movie &movie1, const Movie &movie2)
    {
        return movie1.title < movie2.title;
    }
    static bool compare_by_director(const Movie &movie1, const Movie &movie2)
    {
        return movie1.director < movie2.director;
    }
    static bool compare_by_year(const Movie &movie1, const Movie &movie2)
    {
        return stoi(movie1.year) < stoi(movie2.year);
    }
    static bool compare_by_genre(const Movie &movie1, const Movie &movie2)
    {
        return movie1.genre < movie2.genre;
    }
    static bool compare_by_starring(const Movie &movie1, const Movie &movie2)
    {
        return movie1.starring < movie2.starring;
    }
};

#endif //_MOVIE_H_