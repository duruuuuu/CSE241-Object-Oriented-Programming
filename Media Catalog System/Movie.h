#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <string>

using std::string;

class Movie
{
public:
    template <typename U>
    friend class CatalogHandler;

    Movie();
    Movie(string ti, string d, string y, string g, string s);
    Movie(string line);

    // Getter functions
    string get_title() const;
    string get_year() const;
    string get_director() const;
    string get_genre() const;
    string get_starring() const;

    // Setter functions
    void set_title(string s);
    void set_year(string s);
    void set_director(string s);
    void set_genre(string s);
    void set_starring(string s);

    bool search(string str, string field);
    void sort(string field);

private:
    string title;
    string director;
    string year;
    string genre;
    string starring;

    /**
     * @brief Prints all the information about the movie
     */
    void print_all() const;

    /**
     * @brief Looks for a substring in a string.
     * @tparam Field  Field that the substring is being searched in
     * @param &str reference to the subtring to be searched
     * @param &fieldStr field in string form (used to print the word)
     * @return true if the substring is found, false if not
     */
    template <typename Field>
    bool search_substr(string &str, Field field, string &fieldStr);
};

#endif //_MOVIE_H_