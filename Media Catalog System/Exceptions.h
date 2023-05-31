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
 * @param s line of invalid entry
 */
class MissingField : public Exception
{
public:
    MissingField(string s) : entry(s) {}

    /**
     * @brief Prints error message and invalid entry to file
     * @param out Reference to the files output stream
     */
    void what() const
    {
        std::ofstream out("output.txt", std::ios::app);
        out << "Exception: missing field" << std::endl;
        out << entry << std::endl;
        out.close();
    }

private:
    string entry;
};

/**
 * @class DuplicateEntry
 * @brief If the entry already exists in the system
 * @param s line of invalid entry
 */
class DuplicateEntry : public Exception
{
public:
    DuplicateEntry(string s) : entry(s) {}

    /**
     * @brief Prints error message and invalid entry to file
     * @param out Reference to the files output stream
     */
    void what() const
    {
        std::ofstream out("output.txt", std::ios::app);

        out << "Exception: duplicate entry" << std::endl;
        out << entry << std::endl;
        out.close();
    }

private:
    string entry;
};

/**
 * @class WrongCommand
 * @brief If the command given is invalid
 * @param s line of invalid entry
 */
class WrongCommand : public Exception
{
public:
    WrongCommand(string s) : entry(s) {}
    WrongCommand() {}

    /**
     * @brief Prints error message and invalid entry to file
     */
    void what() const
    {
        std::ofstream out("output.txt", std::ios::app);
        out << "Exception: command is wrong" << std::endl;
        out << entry << std::endl;
        out.close();
    }

    void what(const string &field) const
    {
        std::ofstream out("output.txt", std::ios::app);
        out << "Exception: command is wrong" << std::endl;
        out << "sort \"" << field << "\"" << std::endl;
        out.close();
    }

private:
    string entry;
};

/**
 * @class FileFail
 * @brief file could not be opened successfully
 */
class FileFail : public Exception
{
public:
    void what() { return; }
};

#endif //_EXCEPTIONS_H_