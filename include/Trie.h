#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEnd;

    TrieNode();
};

class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, string currentWord, vector<string>& suggestions);

public:
    Trie();

    void insert(const string& word);

    bool search(const string& word);

    bool startsWith(const string& prefix);

    vector<string> autocomplete(const string& prefix);
};

#endif
