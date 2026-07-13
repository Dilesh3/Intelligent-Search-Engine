#include <algorithm>
#include <chrono>
#include <fstream>
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
    // Benchmark Configuration
    //--------------------------------------------------

    constexpr int EXISTING_QUERIES = 5000;
    constexpr int NON_EXISTING_QUERIES = 5000;
    constexpr int ROUNDS = 5;

    random_device rd;
    mt19937 gen(rd());

    //--------------------------------------------------
    // Generate Existing Queries
    //--------------------------------------------------

    vector<string> queries;
    queries.reserve(EXISTING_QUERIES + NON_EXISTING_QUERIES);

    vector<int> indices(dictionary.size());

    for (int i = 0; i < (int)dictionary.size(); i++)
        indices[i] = i;

    shuffle(indices.begin(), indices.end(), gen);

    for (int i = 0; i < EXISTING_QUERIES; i++) {
        queries.push_back(dictionary[indices[i]]);
    }

    //--------------------------------------------------
    // Generate Non-existing Queries
    //--------------------------------------------------

    for (int i = 0; i < NON_EXISTING_QUERIES; i++) {
        queries.push_back(dictionary[indices[i]] + "zzz");
    }

    shuffle(queries.begin(), queries.end(), gen);

    cout << "Benchmark Queries : " << queries.size() << "\n";
    cout << "Rounds            : " << ROUNDS << "\n\n";

    //--------------------------------------------------
    // Warm-up
    //--------------------------------------------------

    volatile int dummy = 0;

    for (const auto &q : queries)
        dummy += trie.search(q);

    for (const auto &q : queries)
        dummy += (find(dictionary.begin(),
                       dictionary.end(),
                       q) != dictionary.end());

    //--------------------------------------------------
    // Trie Benchmark
    //--------------------------------------------------

    long long trieTotal = 0;

    for (int r = 0; r < ROUNDS; r++) {

        auto start = high_resolution_clock::now();

        for (const auto &q : queries)
            dummy += trie.search(q);

        auto stop = high_resolution_clock::now();

        trieTotal +=
            duration_cast<microseconds>(stop - start).count();
    }

    //--------------------------------------------------
    // Linear Search Benchmark
    //--------------------------------------------------

    long long linearTotal = 0;

    for (int r = 0; r < ROUNDS; r++) {

        auto start = high_resolution_clock::now();

        for (const auto &q : queries)
            dummy += (find(dictionary.begin(),
                           dictionary.end(),
                           q) != dictionary.end());

        auto stop = high_resolution_clock::now();

        linearTotal +=
            duration_cast<microseconds>(stop - start).count();
    }

    //--------------------------------------------------
    // Results
    //--------------------------------------------------

    double avgTrie = trieTotal / static_cast<double>(ROUNDS);
    double avgLinear = linearTotal / static_cast<double>(ROUNDS);

    cout << fixed;
    cout.precision(3);

    cout << "============== RESULTS ==============\n\n";

    cout << "Trie Search\n";
    cout << "Average Time      : "
         << avgTrie
         << " microseconds\n";

    cout << "Average Per Query : "
         << avgTrie / queries.size()
         << " microseconds\n\n";

    cout << "Linear Search\n";
    cout << "Average Time      : "
         << avgLinear
         << " microseconds\n";

    cout << "Average Per Query : "
         << avgLinear / queries.size()
         << " microseconds\n\n";

    cout << "Speedup (Linear/Trie) : "
         << avgLinear / avgTrie
         << "x\n";

    cout << "\n(ignore " << dummy << ")\n";

    return 0;
}
