#include "../include/SpellCorrector.h"

#include <fstream>
#include <algorithm>
#include <numeric>

bool SpellCorrector::loadDictionary(const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open())
        return false;

    dictionary.clear();

    std::string word;

    while (file >> word)
        dictionary.push_back(word);

    return true;
}

int SpellCorrector::levenshteinDistance(
    const std::string& s1,
    const std::string& s2) const {

    const std::string& a = (s1.size() < s2.size()) ? s1 : s2;
    const std::string& b = (s1.size() < s2.size()) ? s2 : s1;

    int n = a.size();
    int m = b.size();

    std::vector<int> prev(n + 1);
    std::vector<int> curr(n + 1);

    std::iota(prev.begin(), prev.end(), 0);

    for (int i = 1; i <= m; i++) {

        curr[0] = i;

        for (int j = 1; j <= n; j++) {

            if (b[i - 1] == a[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = 1 + std::min({
                    prev[j],
                    curr[j - 1],
                    prev[j - 1]
                });
        }

        prev.swap(curr);
    }

    return prev[n];
}

std::vector<std::pair<std::string,int>>
SpellCorrector::suggest(
    const std::string& word,
    int maxSuggestions) const {

    std::vector<std::pair<std::string,int>> candidates;

    for (const auto& dictWord : dictionary) {

        if (std::abs((int)dictWord.size() - (int)word.size()) > 2)
            continue;

        if (!dictWord.empty() && !word.empty()
            && dictWord[0] != word[0])
            continue;

        int distance = levenshteinDistance(word, dictWord);

        candidates.emplace_back(dictWord, distance);
    }

    if (candidates.empty())
        return candidates;

    int k = std::min(maxSuggestions, (int)candidates.size());

    std::partial_sort(
        candidates.begin(),
        candidates.begin() + k,
        candidates.end(),
        [](const auto& a, const auto& b) {

            if (a.second != b.second)
                return a.second < b.second;

            return a.first < b.first;
        });

    candidates.resize(k);

    return candidates;
}
