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
    // Generate Benchmark Queries
    //--------------------------------------------------

    vector<string> queries;

    queries.reserve(dictionary.size() * 2);

    for (const auto &w : dictionary) {

        // Existing query
        queries.push_back(w);

        // Non-existing query
        queries.push_back(w + "zzz");
    }

    random_device rd;
    mt19937 gen(rd());

    shuffle(queries.begin(), queries.end(), gen);

    cout << "Total Queries : " << queries.size() << "\n\n";

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
    // Benchmark Settings
    //--------------------------------------------------

    const int ROUNDS = 5;

    long long trieTotal = 0;
    long long linearTotal = 0;

    //--------------------------------------------------
    // Trie Benchmark
    //--------------------------------------------------

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

    double triePerQuery = avgTrie / queries.size();
    double linearPerQuery = avgLinear / queries.size();

    cout << fixed;
    cout.precision(3);

    cout << "============== RESULTS ==============\n\n";

    cout << "Trie Search\n";
    cout << "Average Time          : "
         << avgTrie
         << " microseconds\n";

    cout << "Average Per Query     : "
         << triePerQuery
         << " microseconds\n\n";

    cout << "Linear Search\n";
    cout << "Average Time          : "
         << avgLinear
         << " microseconds\n";

    cout << "Average Per Query     : "
         << linearPerQuery
         << " microseconds\n\n";

    cout << "Speedup (Linear/Trie) : "
         << avgLinear / avgTrie
         << "x\n";

    cout << "\n(ignore " << dummy << ")\n";

    return 0;
}
