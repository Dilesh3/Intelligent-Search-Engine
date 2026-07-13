#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>
#include <utility>

#include "Trie.h"
#include "DictionaryLoader.h"
#include "SpellCorrector.h"

class SearchEngine {
private:

    // Trie used for indexing and autocomplete.
    Trie trie;

    // Handles fuzzy search and spelling suggestions.
    SpellCorrector spellCorrector;

public:

    SearchEngine() = default;

    // Loads both Trie and SpellCorrector.
    bool loadDictionary(const std::string& filename);

    // Performs exact search and updates frequency.
    bool search(const std::string& word);

    // Returns autocomplete suggestions.
    std::vector<std::pair<std::string,int>>
    autocomplete(const std::string& prefix) const;

    // Returns spelling suggestions.
    std::vector<std::pair<std::string,int>>
    spellCorrect(const std::string& word,
                 int maxSuggestions = 5) const;
};

#endif
