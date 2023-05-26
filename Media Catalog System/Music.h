#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <string>

using std::string;

class Music
{
public:
    template <typename U>
    friend class CatalogHandler;

    Music();
    Music(string t, string a, string y, string g);
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

    bool search(string str, string field);
    void sort(string field);

private:
    string title;
    string artists;
    string year;
    string genre;

    /**
     * @brief Prints all the information about the song
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

#endif //_MUSIC_H_