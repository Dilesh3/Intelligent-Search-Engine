#include "../include/SpellCorrector.h"

#include <fstream>
#include <algorithm>

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

    int n = s1.size();
    int m = s2.size();

    std::vector<std::vector<int>> dp(
        n + 1,
        std::vector<int>(m + 1));

    for (int i = 0; i <= n; i++)
        dp[i][0] = i;

    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    for (int i = 1; i <= n; i++) {

        for (int j = 1; j <= m; j++) {

            if (s1[i - 1] == s2[j - 1]) {

                dp[i][j] = dp[i - 1][j - 1];

            } else {

                dp[i][j] = 1 + std::min({
                    dp[i - 1][j],
                    dp[i][j - 1],
                    dp[i - 1][j - 1]
                });

            }
        }
    }

    return dp[n][m];
}

std::vector<std::pair<std::string,int>>
SpellCorrector::suggest(
    const std::string& word,
    int maxSuggestions) const {

    std::vector<std::pair<std::string,int>> suggestions;

    for (const auto& dictWord : dictionary) {

        int distance = levenshteinDistance(word, dictWord);

        suggestions.emplace_back(dictWord, distance);
    }

    std::sort(
        suggestions.begin(),
        suggestions.end(),
        [](const auto& a, const auto& b) {

            if (a.second != b.second)
                return a.second < b.second;

            return a.first < b.first;
        });

    if (suggestions.size() > maxSuggestions)
        suggestions.resize(maxSuggestions);

    return suggestions;
}
