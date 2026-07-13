#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>
#include <utility>

#include "Trie.h"
#include "DictionaryLoader.h"

class SearchEngine {
private:
    // Core data structure that stores all indexed words
    // and provides efficient search and autocomplete operations.
    Trie trie;

public:
    // Constructs an empty search engine.
    // The Trie is automatically initialized.
    SearchEngine() = default;

    // Loads all words from the specified dictionary file
    // into the Trie. Returns true if successful.
    bool loadDictionary(const std::string& filename);

    // Performs an exact search for a word.
    // If the word exists, its search frequency is updated.
    bool search(const std::string& word);

    // Returns all words beginning with the given prefix,
    // ranked by their search frequencies.
    std::vector<std::pair<std::string, int>>
    autocomplete(const std::string& prefix) const;
};

#endif
