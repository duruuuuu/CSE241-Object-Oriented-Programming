#include "Movie.h"
#include <string>

using std::string;

Movie::Movie()
{
    // Intentionally left blank
}

Movie::Movie(string ti, string d, string y, string g, string s)
    : title(ti), director(d), year(y), genre(g), starring(s)
{
    // Intentionally left blank
}

string Movie::get_title() const { return title; }

string Movie::get_year() const { return year; }

string Movie::get_director() const { return director; }

string Movie::get_genre() const { return genre; }

string Movie::get_starring() const { return starring; }

void Movie::set_title(string s) { title = s; }

void Movie::set_year(string s) { year = s; }

void Movie::set_director(string s) { director = s; }

void Movie::set_genre(string s) { genre = s; }

void Movie::set_starring(string s) { starring = s; }