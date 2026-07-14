#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <queue>
#include <functional>
/*
 * Represents a single node in the Trie.
 * Each node stores pointer to its children,
 * a flag which marks if it is the end of a valid word,
 * and the frequency associated with that word.
 */
class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;
    int frequency;

    TrieNode();
};

/*
 * Trie data structure supporting
 * - Word insertion
 * - Exact search
 * - Prefix search
 * - Autocomplete
 * - Dynamic frequency updates
 */
class Trie {
private:
    TrieNode* root;
// Alias representing an autocomplete suggestion
// as (word, frequency).
using Suggestion = std::pair<std::string, int>;

// Comparator for maintaining a min-heap
// based on word frequency.
struct CompareFrequency {
    bool operator()(const Suggestion& a,
                    const Suggestion& b) const;
};

// Performs DFS while maintaining only the
// top-k highest frequency suggestions using a min-heap.
void dfsHeap(
    TrieNode* node,
    std::string& currentWord,
    std::priority_queue<
        Suggestion,
        std::vector<Suggestion>,
        CompareFrequency>& heap,
    int k
) const;
    // Returns the node corresponding to the given prefix.
    // Returns nullptr if the prefix does not exist.
    TrieNode* getNode(const std::string& prefix) const;

    // Performs DFS from the given node to collect words (will be useful for autocomplete).
    void dfs(TrieNode* node, std::string& currentWord,
             std::vector<std::pair<std::string, int>>& suggestions) const;

    // Frees all dynamically allocated nodes.
    void deleteTrie(TrieNode* node);

public:
    Trie();
    ~Trie();

    // Inserts a word into the Trie.
    void insert(const std::string& word);

    // Returns true if the exact word exists.
    bool search(const std::string& word) const;

    // Returns true if at least one word starts with the prefix.
    bool startsWith(const std::string& prefix) const;

    // Returns autocomplete suggestions along with frequencies.
    std::vector<std::pair<std::string,int>>
    autocomplete(
    const std::string& prefix,
    int k = 5
    ) const;

// Returns the top-k autocomplete suggestions
// using a heap-based optimization.
    std::vector<Suggestion>
    autocompleteHeap(const std::string& prefix, int k) const;
    // Updates the frequency of the word.
    void updateFrequency(const std::string& word);
};

#endif
