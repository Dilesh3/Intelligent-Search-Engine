#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../include/Trie.h"

using namespace std;
using namespace std::chrono;

int main() {

    Trie trie;
    vector<string> dictionary;

    ifstream file("data/words_alpha.txt");

    if (!file.is_open()) {
        cout << "Failed to open dictionary.\n";
        return 1;
    }

    string word;

    while (file >> word) {
        trie.insert(word);
        dictionary.push_back(word);
    }

    file.close();

    cout << "=========================================\n";
    cout << "Dictionary Loaded Successfully\n";
    cout << "Words Loaded : " << dictionary.size() << "\n";
    cout << "=========================================\n\n";

    //--------------------------------------------------
    // Configuration
    //--------------------------------------------------

    constexpr int PREFIX_COUNT = 10000;
    constexpr int ROUNDS = 5;

    vector<int> K_VALUES = {5, 10, 20, 50};

    random_device rd;
    mt19937 gen(rd());

    //--------------------------------------------------
    // Generate Random Existing Prefixes
    //--------------------------------------------------

    vector<string> prefixes;
    prefixes.reserve(PREFIX_COUNT);

    uniform_int_distribution<int> wordDist(0, dictionary.size() - 1);

    for (int i = 0; i < PREFIX_COUNT; i++) {

        const string& w = dictionary[wordDist(gen)];

        if (w.length() == 1) {
            prefixes.push_back(w);
            continue;
        }

        uniform_int_distribution<int> prefixLength(1, w.length());

        prefixes.push_back(
            w.substr(0, prefixLength(gen))
        );
    }

    //--------------------------------------------------
    // Warm-up
    //--------------------------------------------------

    volatile int dummy = 0;

    for (const auto& prefix : prefixes) {
        dummy += trie.autocomplete(prefix, 5).size();
    }

    for (const auto& prefix : prefixes) {
        dummy += trie.autocompleteHeap(prefix, 5).size();
    }

    //--------------------------------------------------
    // Benchmark
    //--------------------------------------------------

    cout << left
         << setw(10) << "Top-K"
         << setw(20) << "DFS+Sort (us)"
         << setw(20) << "Heap (us)"
         << setw(15) << "Speedup"
         << "\n";

    cout << string(65, '-') << "\n";

    cout << fixed << setprecision(3);

    for (int k : K_VALUES) {

        long long sortTotal = 0;
        long long heapTotal = 0;

        //----------------------------
        // DFS + Sort
        //----------------------------

        for (int r = 0; r < ROUNDS; r++) {

            auto start = high_resolution_clock::now();

            for (const auto& prefix : prefixes)
                dummy += trie.autocomplete(prefix, k).size();

            auto stop = high_resolution_clock::now();

            sortTotal +=
                duration_cast<microseconds>(stop - start).count();
        }

        //----------------------------
        // Heap
        //----------------------------

        for (int r = 0; r < ROUNDS; r++) {

            auto start = high_resolution_clock::now();

            for (const auto& prefix : prefixes)
                dummy += trie.autocompleteHeap(prefix, k).size();

            auto stop = high_resolution_clock::now();

            heapTotal +=
                duration_cast<microseconds>(stop - start).count();
        }

        double avgSort =
            sortTotal / static_cast<double>(ROUNDS);

        double avgHeap =
            heapTotal / static_cast<double>(ROUNDS);

        cout << left
             << setw(10) << k
             << setw(20) << avgSort
             << setw(20) << avgHeap
             << setw(15) << avgSort / avgHeap
             << "\n";
    }

    cout << "\n(ignore " << dummy << ")\n";

    return 0;
}
