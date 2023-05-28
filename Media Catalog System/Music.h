#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "Exceptions.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>

using namespace std;

class Music
{
public:
    Music();
    Music(string line);

    // Getter functions
    string get_title() const;
    string get_artists() const;
    string get_year() const;
    string get_genre() const;

    // Setter functions
    void set_title(string s);
    void set_artists(string s);
    void set_year(string s);
    void set_genre(string s);

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
     * @return returns the corresponding function that sorts according to the given field
     * @exception invalid command/field to be sorted
     */
    std::function<bool(const Music &, const Music &)> get_compare_func(const string &field) const;

    /**
     * @brief Prints all the information about the song
     */
    void print_all() const;

private:
    string title;
    string artists;
    string year;
    string genre;

    /**
     * @brief Looks for a substring in a string.
     * @tparam Field  Field that the substring is being searched in
     * @param &str reference to the subtring to be searched
     * @param &fieldStr field in string form (used to print the word)
     * @return true if the substring is found, false if not
     */
    template <typename Field>
    bool search_substr(string &str, Field field, string &fieldStr);

    static bool compare_by_title(const Music &Music1, const Music &Music2)
    {
        return Music1.title < Music2.title;
    }
    static bool compare_by_artists(const Music &Music1, const Music &Music2)
    {
        return Music1.artists < Music2.artists;
    }
    static bool compare_by_year(const Music &Music1, const Music &Music2)
    {
        return stoi(Music1.year) < stoi(Music2.year);
    }
    static bool compare_by_genre(const Music &Music1, const Music &Music2)
    {
        return Music1.genre < Music2.genre;
    }
};

#endif //_MUSIC_H_