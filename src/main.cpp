#include <iostream>
#include "../include/SearchEngine.h"

int main() {
    SearchEngine engine;

    // Load dictionary
    if (!engine.loadDictionary("data/words.txt")) {
        std::cout << "Failed to load dictionary.\n";
        return 1;
    }

    std::cout << "Dictionary loaded successfully!\n\n";

    // Test exact search
    std::string word = "apple";

    if (engine.search(word))
        std::cout << "'" << word << "' found.\n";
    else
        std::cout << "'" << word << "' not found.\n";

    word = "xyz";

    if (engine.search(word))
        std::cout << "'" << word << "' found.\n";
    else
        std::cout << "'" << word << "' not found.\n";

    std::cout << "\n";

    // Test autocomplete
    std::string prefix = "app";

    auto suggestions = engine.autocomplete(prefix);

    std::cout << "Autocomplete suggestions for \"" << prefix << "\":\n";

    for (const auto& suggestion : suggestions) {
        std::cout << suggestion.first
                  << " (frequency = "
                  << suggestion.second
                  << ")\n";
    }

    return 0;
}
