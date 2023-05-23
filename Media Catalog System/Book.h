#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>

using std::string;

class Book
{
public:
    Book();
    Book(string ti, string a, string y, string ta);

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

private:
    string title;
    string authors;
    string year;
    string tags;
};

#endif //_BOOK_H_