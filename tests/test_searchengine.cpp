#include <cassert>
#include <iostream>

#include "../include/SearchEngine.h"

int main() {

    SearchEngine engine;

    assert(engine.loadDictionary("data/sample_words.txt"));

    assert(engine.search("apple"));
    assert(!engine.search("xyzabc"));

    auto suggestions = engine.autocomplete("app", 3);

    assert(!suggestions.empty());

    auto spell = engine.spellCorrect("aple");

    assert(!spell.empty());

    std::cout << "All SearchEngine tests passed.\n";

    return 0;
}
