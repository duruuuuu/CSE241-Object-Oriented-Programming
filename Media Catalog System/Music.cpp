#include "Music.h"
#include <string>

using std::string;

Music::Music()
{
    // Intentionally left blank
}
Music::Music(string t, string a, string y, string g)
    : title(t), artists(a), year(y), genre(g)
{
    // Intentionally left blank
}

string Music::get_title() const { return title; }

string Music::get_artists() const { return artists; }

string Music::get_year() const { return year; }

string Music::get_genre() const { return genre; }

void Music::set_title(string s) { title = s; }

void Music::set_artists(string s) { artists = s; }

void Music::set_year(string s) { year = s; }

void Music::set_genre(string s) { genre = s; }