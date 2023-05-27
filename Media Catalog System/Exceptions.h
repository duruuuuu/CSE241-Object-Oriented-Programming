#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <string>
#include <iostream>
#include <fstream>

using std::exception;
using std::string;

class Exception
{
public:
    string what() const { return "base exception"; }
};

/**
 * @class MissingField
 * @brief If there is a field missingin the entry
 * @param s invalid line/entry
 */
class MissingField : public Exception
{
public:
    MissingField(string s) : line(s) {}

    /**
     * @brief Prints error message and invalid entry to file
     * @param out Reference to the files output stream
     */
    void what(std::ofstream &out) const
    {
        out << "Exception: missing field" << std::endl;
        out << line << std::endl;
    }

private:
    string line;
};

/**
 * @class DuplicateEntry
 * @brief If the entry already exists in the system
 * @param s invalid line/entry
 */
class DuplicateEntry : public Exception
{
public:
    DuplicateEntry(string s) : line(s) {}

    /**
     * @brief Prints error message and invalid entry to file
     * @param out Reference to the files output stream
     */
    void what(std::ofstream &out) const
    {
        out << "Exception: duplicate entry" << std::endl;
        out << line << std::endl;
    }

private:
    string line;
};

class WrongCommand : public Exception
{
public:
    string what() const { return "command is wrong"; }
};

#endif //_EXCEPTIONS_H_