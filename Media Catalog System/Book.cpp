#include "Book.h"
#include <string>

using std::string;

Book::Book()
{
    // Intentionally left empty
}

Book::Book(string ti, string a, string y, string ta)
    : title(ti), authors(a), year(y), tags(ta)
{
    // Intentionally left empty
}

string Book::get_title() const { return title; }

string Book::get_year() const { return year; }

string Book::get_authors() const { return authors; }

string Book::get_tags() const { return tags; }

void Book::set_title(string s) { title = s; }

void Book::set_year(string s) { year = s; }

void Book::set_authors(string s) { authors = s; }

void Book::set_tags(string s) { tags = s; }