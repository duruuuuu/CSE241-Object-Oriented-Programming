#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <string>

using std::string;

class Movie
{
public:
    Movie();
    Movie(string ti, string d, string y, string g, string s);

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

private:
    string title;
    string director;
    string year;
    string genre;
    string starring;
};

#endif //_MOVIE_H_