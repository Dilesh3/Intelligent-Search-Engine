#include "../include/SearchEngine.h"

bool SearchEngine::loadDictionary(const std::string& filename) {

    bool trieLoaded =
        DictionaryLoader::loadDictionary(filename, trie);

    bool spellLoaded =
        spellCorrector.loadDictionary(filename);

    return trieLoaded && spellLoaded;
}

bool SearchEngine::search(const std::string& word) {

    if (trie.search(word)) {

        trie.updateFrequency(word);

        return true;
    }

    return false;
}

std::vector<std::pair<std::string,int>>
SearchEngine::autocomplete(const std::string& prefix, int k) const {

    return trie.autocompleteHeap(prefix, k);
}

std::vector<std::pair<std::string,int>>
SearchEngine::spellCorrect(
    const std::string& word,
    int maxSuggestions) const {

    return spellCorrector.suggest(word, maxSuggestions);
}
