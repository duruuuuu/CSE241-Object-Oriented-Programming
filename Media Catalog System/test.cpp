#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

class Book
{
private:
    string title, author, year, tags, starring;

public:
    Book()
    {
        // intentionally left empty
    }
    Book(const string &line)
    {
        vector<string> parsedItems;
        istringstream iss(line);
        string item;

        while (getline(iss, item, '\"'))
        {
            parsedItems.push_back(item);
        }

        if (parsedItems.size() < 9)
        {
            cerr << "Missing Field" << endl;
            return;
        }

        title = parsedItems[1];
        author = parsedItems[3];
        year = parsedItems[5];
        tags = parsedItems[7];
        starring = parsedItems[9];
    }

    string get_author() const { return author; }
    string get_title() const { return title; }
    string get_tags() const { return tags; }
    string get_year() const { return year; }
    string get_star() const { return starring; }

    Book *get_book(bool b)
    {
        if (b == true)
            return this;

        else if (b == false)
            return nullptr;
    }
};

int main()
{
    vector<string> tempLines;

    tempLines.push_back("\"Hilbert Spaces With Applications\" \"Lokenath Debnathl, Piotr Mikusinski\" \"2005\" \"Mathematics, Set Theory\"");
    tempLines.push_back("\"The Neolithic Revolutions in the Near East: Transforming the Human Landscape\" \"Alan H. Simmons\" \"2011\" \"Social Science, Anthropology, Cultural, General, Archeology\" \"Me, Myself, I\"");
    tempLines.push_back("\"Graphic Gems V\" \"Alan W. Paeth\" \"1995\" \"\"");
    tempLines.push_back("\"The Neolithic Revolutions in the Near East: Transforming the Human Landscape\" \"Alan Simmons\" \"45678\" \"Social Science, Anthropology, Cultural, General, Archeology\"");

    unordered_map<string, Book> myMap;

    string title;
    for (const auto &line : tempLines)
    {
        istringstream iss(line);
        getline(iss, title, '\"');
        getline(iss, title, '\"');
        cout << "TITLE: " << title << endl;
        cout << "LINE: " << line << endl;

        if (myMap.count(title) > 0)
        {
            cout << "duplicate detected" << endl;
            continue;
        }
        myMap[title] = Book(line);
    }

    // cout << "Catalog Read: " << endl;
    // for (const auto &line : tempLines)
    //     cout << line << endl;

    Book temp = myMap["The Neolithic Revolutions in the Near East: Transforming the Human Landscape"];

    // cout << "\n===========TEST MAP:============" << endl;
    // cout << "TITLE: " << temp.get_title() << endl;
    // cout << "STARRING: " << temp.get_star() << endl;

    string cmndLine = "sort \"title\"";
    string line2, cmnd;
    istringstream iss(line2);
    getline(iss, cmnd, ' ');
    getline(iss, cmnd, ' ');
    cout << "COMMAND: " << cmnd << endl;

    Book *newB = temp.get_book(1);
    cout << "\nGET BOOK:" << endl;
    if (newB != nullptr)
        cout << "AUTHOR: " << newB->get_author() << endl;

    return 0;
}
