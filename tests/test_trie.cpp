#include <cassert>
#include <iostream>

#include "../include/Trie.h"

int main() {

    Trie trie;

    trie.insert("apple");
    trie.insert("application");
    trie.insert("banana");

    // Exact Search
    assert(trie.search("apple"));
    assert(trie.search("banana"));
    assert(!trie.search("cat"));

    // Prefix Search
    assert(trie.startsWith("app"));
    assert(trie.startsWith("ban"));
    assert(!trie.startsWith("dog"));

    // Frequency Update
    trie.updateFrequency("apple");
    trie.updateFrequency("apple");
    trie.updateFrequency("application");

    auto suggestions = trie.autocomplete("app", 2);

    assert(suggestions.size() == 2);
    assert(suggestions[0].first == "apple");
    assert(suggestions[0].second == 2);

    auto heapSuggestions = trie.autocompleteHeap("app", 2);

    assert(heapSuggestions.size() == 2);
    assert(heapSuggestions[0].first == "apple");

    std::cout << "All Trie tests passed.\n";

    return 0;
}
