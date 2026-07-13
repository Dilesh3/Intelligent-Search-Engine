#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

#include "../include/Trie.h"

int main() {

    Trie trie;
    std::vector<std::string> dictionary;

    std::ifstream file("data/words_alpha.txt");

    if (!file.is_open()) {
        std::cout << "Failed to open dictionary.\n";
        return 1;
    }

    std::string word;

    while (file >> word) {
        dictionary.push_back(word);
        trie.insert(word);
    }

    file.close();

    std::cout << "Loaded " << dictionary.size()
              << " words.\n\n";

    // Randomize query order
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(dictionary.begin(), dictionary.end(), gen);

    const int ROUNDS = 10;

    long long trieTotal = 0;
    long long linearTotal = 0;

    volatile int dummy = 0;

    //---------------- Warm-up ----------------

    for (const auto& w : dictionary)
        dummy += trie.search(w);

    for (const auto& w : dictionary)
        dummy += (std::find(dictionary.begin(),
                            dictionary.end(),
                            w) != dictionary.end());

    //----------------------------------------

    for (int round = 0; round < ROUNDS; round++) {

        auto startTrie =
            std::chrono::high_resolution_clock::now();

        for (const auto& w : dictionary)
            dummy += trie.search(w);

        auto endTrie =
            std::chrono::high_resolution_clock::now();

        trieTotal +=
            std::chrono::duration_cast<
            std::chrono::microseconds>(
            endTrie - startTrie).count();


        auto startLinear =
            std::chrono::high_resolution_clock::now();

        for (const auto& w : dictionary)
            dummy += (std::find(dictionary.begin(),
                                dictionary.end(),
                                w)
                      != dictionary.end());

        auto endLinear =
            std::chrono::high_resolution_clock::now();

        linearTotal +=
            std::chrono::duration_cast<
            std::chrono::microseconds>(
            endLinear - startLinear).count();
    }

    double trieAverage =
        trieTotal / static_cast<double>(ROUNDS);

    double linearAverage =
        linearTotal / static_cast<double>(ROUNDS);

    std::cout << "Average Trie Search Time : "
              << trieAverage
              << " microseconds\n";

    std::cout << "Average Linear Search Time : "
              << linearAverage
              << " microseconds\n";

    std::cout << "Speedup : "
              << linearAverage / trieAverage
              << "x\n";

    std::cout << "\n(ignore " << dummy
              << ")\n";

    return 0;
}
