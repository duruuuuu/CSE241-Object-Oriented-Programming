#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <string>

using std::string;

class Music
{
public:
    Music();
    Music(string t, string a, string y, string g);

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

private:
    string title;
    string artists;
    string year;
    string genre;
};

#endif //_MUSIC_H_