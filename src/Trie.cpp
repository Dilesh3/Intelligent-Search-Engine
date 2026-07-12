#include "../include/Trie.h"

TrieNode::TrieNode() {
    isEnd = false;
    for(int i=0;i<26;i++)
        children[i]=nullptr;
}

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const string& word) {

}

bool Trie::search(const string& word) {
    return false;
}

bool Trie::startsWith(const string& prefix) {
    return false;
}

void Trie::dfs(TrieNode* node,
               string currentWord,
               vector<string>& suggestions) {

}

vector<string> Trie::autocomplete(const string& prefix) {
    vector<string> result;
    return result;
}
