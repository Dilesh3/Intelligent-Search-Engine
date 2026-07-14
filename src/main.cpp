#include <iostream>
#include <vector>
#include "../include/SearchEngine.h"

int main() {

    SearchEngine engine;

    // Load dictionary
    if (!engine.loadDictionary("data/words_alpha.txt")) {
        std::cout << "Failed to load dictionary.\n";
        return 1;
    }

    std::cout << "Dictionary loaded successfully!\n";

    int choice;

    do {

        std::cout << "\n========== Intelligent Search Engine ==========\n";
        std::cout << "1. Search Word\n";
        std::cout << "2. Autocomplete\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }
        
        switch (choice) {

        case 1: {

            std::string word;

            std::cout << "Enter search term: ";
            std::cin >> word;

            if (engine.search(word)) {

                std::cout << "'" << word << "' found.\n";

            } else {

                std::cout << "'" << word << "' not found.\n\n";

                auto suggestions = engine.spellCorrect(word);

                if (!suggestions.empty()) {

                    std::cout << "Did you mean:\n";

                    for (size_t i = 0; i < suggestions.size(); i++) {
                        std::cout << i + 1 << ". "
                                  << suggestions[i].first
                                  << " (Edit Distance = "
                                  << suggestions[i].second
                                  << ")\n";
                    }

                } else {

                    std::cout << "No spelling suggestions found.\n";

                }
            }

            break;
        }

        case 2: {

            std::string prefix;

            std::cout << "Enter prefix: ";
            std::cin >> prefix;

            //auto suggestions = engine.autocomplete(prefix);
            int k;
            std::cout << "Number of suggestions: ";
            if (!(std::cin >> k)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input.\n";
                break;
            }

            if (k <= 0) {
                std::cout << "Number of suggestions must be positive.\n";
                break;
            }


            auto suggestions = engine.autocomplete(prefix, k);
            if (suggestions.empty()) {
                
                std::cout << "No suggestions found.\n";
                
            } else {

                std::cout << "\nAutocomplete Suggestions:\n";

                for (const auto& suggestion : suggestions) {

                    std::cout << suggestion.first
                              << " (Frequency = "
                              << suggestion.second
                              << ")\n";
                }
            }

            break;
        }

        case 3:

            std::cout << "Exiting...\n";
            break;

        default:

            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}
