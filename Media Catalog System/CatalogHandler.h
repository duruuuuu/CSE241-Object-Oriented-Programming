#ifndef _CATALOGHANDLER_H_
#define _CATALOGHANDLER_H_

#include <unordered_map>
#include <algorithm>

using std::string;
using std::unordered_map;

template <typename T>
class CatalogHandler
{
public:
    string catalogType;                   // stores the type of catalog (Book, Movie, or Music)
    unordered_map<string, T> catalogList; // Map template to configure the list for whatever the catalog type is
};

#endif // _CATALOGHANDLER_H_