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
    // Benchmark Configuration
    //--------------------------------------------------

    vector<int> benchmarkSizes = {100, 1000, 5000, 10000, 20000};
    constexpr int ROUNDS = 5;

    random_device rd;
    mt19937 gen(rd());

    cout << fixed << setprecision(3);

    cout << left
         << setw(12) << "Queries"
         << setw(20) << "Trie (us)"
         << setw(20) << "Linear (us)"
         << setw(15) << "Speedup"
         << "\n";

    cout << string(67, '-') << "\n";

    volatile int dummy = 0;

    for (int totalQueries : benchmarkSizes) {

        int existingQueries = totalQueries / 2;
        int nonExistingQueries = totalQueries / 2;

        //--------------------------------------------------
        // Generate Queries
        //--------------------------------------------------

        vector<string> queries;
        queries.reserve(totalQueries);

        vector<int> indices(dictionary.size());

        for (int i = 0; i < (int)dictionary.size(); i++)
            indices[i] = i;

        shuffle(indices.begin(), indices.end(), gen);

        // Existing queries
        for (int i = 0; i < existingQueries; i++)
            queries.push_back(dictionary[indices[i]]);

        // Non-existing queries
        for (int i = 0; i < nonExistingQueries; i++)
            queries.push_back(dictionary[indices[i]] + "zzz");

        shuffle(queries.begin(), queries.end(), gen);

        //--------------------------------------------------
        // Warm-up
        //--------------------------------------------------

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
        // Linear Benchmark
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

        cout << left
             << setw(12) << totalQueries
             << setw(20) << avgTrie
             << setw(20) << avgLinear
             << setw(15) << avgLinear / avgTrie
             << "\n";
    }

    cout << "\n(ignore " << dummy << ")\n";

    return 0;
}
