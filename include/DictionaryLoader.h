#ifndef DICTIONARY_LOADER_H
#define DICTIONARY_LOADER_H

#include <string>
#include "Trie.h"

//Returns true if file is loaded successfully, else returns false
class DictionaryLoader {
public:
    static bool loadDictionary(const std::string& filename, Trie& trie);
};

#endif
