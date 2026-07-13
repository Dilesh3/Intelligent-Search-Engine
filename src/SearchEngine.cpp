#include "../include/SearchEngine.h"

bool SearchEngine::loadDictionary(const std::string& filename) {
    return DictionaryLoader::loadDictionary(filename, trie);
}

bool SearchEngine::search(const std::string& word) {

    if (trie.search(word)) {
        trie.updateFrequency(word);
        return true;
    }

    return false;
}

std::vector<std::pair<std::string, int>>
SearchEngine::autocomplete(const std::string& prefix) const {
    return trie.autocomplete(prefix);
}
