#include "../include/DictionaryLoader.h"

#include <fstream>
#include <algorithm>
#include <cctype>


// Converts a word to lowercase and validates that it
// contains only alphabetic characters.
// Returns an empty string if the word is invalid.
static std::string sanitizeWord(std::string word) {

    for (char& ch : word) {
        ch = std::tolower(static_cast<unsigned char>(ch));
    }

    for (char ch : word) {
        if (!std::isalpha(static_cast<unsigned char>(ch))) {
            return "";
        }
    }

    return word;
}


bool DictionaryLoader::loadDictionary(const std::string& filename, Trie& trie) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    std::string word;

    while (file >> word) {

    word = sanitizeWord(word);

    if (word.empty())
        continue;

    trie.insert(word);
    words.push_back(word);
}

    file.close();

    return true;
}
