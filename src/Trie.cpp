#include "../include/Trie.h"
#include<algorithm>


TrieNode::TrieNode() {
    isEndOfWord = false;
    for(int i=0;i<26;i++)
        children[i]=nullptr;
    frequency = 0;
}

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    deleteTrie(root);
}


void Trie::deleteTrie(TrieNode* node) {
    if(node == nullptr) return;
    for(int i = 0; i < 26; i++) {
        deleteTrie(node->children[i]);
    }
    delete node;
}


void Trie::insert(const std::string& word) {
    TrieNode* current = root;

    for (char ch : word) {
        int index = ch - 'a';

        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
        }

        current = current->children[index];
    }

        if (!current->isEndOfWord) {
            current->isEndOfWord = true;
            current->frequency = 0;
        }
}


TrieNode* Trie::getNode(const std::string &prefix) const{
    TrieNode* current = root;
    for(char ch : prefix) {
        int index = ch - 'a';

        if(current->children[index] == nullptr) {
            return nullptr;
        }
        current = current->children[index];
    }
    return current;
}


bool Trie::search(const std::string& word) const{
    TrieNode* node = getNode(word);
    if(node == nullptr) return false;
    return node->isEndOfWord;
}


bool Trie::startsWith(const std::string& prefix) const{
    TrieNode* node = getNode(prefix);
    if(node != nullptr) return true;
    return false;
}


void Trie::dfs(TrieNode* node, std::string& currentWord,
               std::vector<std::pair<std::string, int>>& suggestions) const {

    if (node == nullptr)  return;

    if (node->isEndOfWord) {
        suggestions.emplace_back(currentWord, node->frequency);
    }

    for (int i = 0; i < 26; i++) {

        if (node->children[i] != nullptr) {

            currentWord.push_back('a' + i);

            dfs(node->children[i], currentWord, suggestions);

            currentWord.pop_back();
        }
    }
}


std::vector<std::pair<std::string, int>> Trie::autocomplete(const std::string& prefix) const {
    std::vector<std::pair<std::string, int>> suggestions;

    TrieNode* node = getNode(prefix);

    if (node == nullptr)  return suggestions;

    std::string currentWord = prefix;

    dfs(node, currentWord, suggestions);

    std::sort(suggestions.begin(), suggestions.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    return suggestions;
}

void Trie::updateFrequency(const std::string& word) {
    TrieNode* node = getNode(word);

    if (node != nullptr && node->isEndOfWord) {
        node->frequency++;
    }
}
