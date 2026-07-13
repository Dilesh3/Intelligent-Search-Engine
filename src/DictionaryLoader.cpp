#include "../include/DictionaryLoader.h"

#include <fstream>

bool DictionaryLoader::loadDictionary(const std::string& filename, Trie& trie) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    std::string word;

    while (file >> word) {
        trie.insert(word);
    }

    file.close();

    return true;
}
