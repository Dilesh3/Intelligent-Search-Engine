#include <cassert>
#include <iostream>

#include "../include/SpellCorrector.h"

int main() {

    SpellCorrector corrector;

    corrector.addWord("apple");
    corrector.addWord("application");
    corrector.addWord("banana");

    auto suggestions = corrector.getSuggestions("aple", 3);

    assert(!suggestions.empty());
    assert(suggestions[0].first == "apple");

    suggestions = corrector.getSuggestions("banan", 3);

    assert(!suggestions.empty());
    assert(suggestions[0].first == "banana");

    std::cout << "All SpellCorrector tests passed.\n";

    return 0;
}
