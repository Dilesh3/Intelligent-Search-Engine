#ifndef SPELL_CORRECTOR_H
#define SPELL_CORRECTOR_H

#include <string>
#include <vector>
#include <utility>

class SpellCorrector {
private:

    // Stores all dictionary words for spell correction.
    std::vector<std::string> dictionary;

    // Computes the Levenshtein edit distance between two words.
    int levenshteinDistance(const std::string& s1,
                            const std::string& s2) const;

public:

    // Loads all words from the dictionary file.
    bool loadDictionary(const std::string& filename);

    // Returns the top spelling suggestions.
    std::vector<std::pair<std::string,int>>
    suggest(const std::string& word,
            int maxSuggestions = 5) const;
};

#endif
