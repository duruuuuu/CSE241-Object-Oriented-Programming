#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <string>

using std::string;

class Exception
{
public:
    string exception() const { return "base exception"; }
};

class MissingField : public Exception
{
public:
    MissingField(string s, Catalog c)
        : Exception
    {
    }
    string exception(string n) const { return "Missing Field"; }

private:
};

class DuplicateEntry : public Exception
{
public:
    string exception() const { return "Duplicate Entry"; }
};

class WrongCommand : public Exception
{
public:
    string exception() const { return "Command is Wrong"; }
};

#endif //_EXCEPTIONS_H_