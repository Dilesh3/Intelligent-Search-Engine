#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "Trie.h"

class SearchEngine {

private:

    Trie trie;

public:

    SearchEngine();

    void buildIndex();

    void search();

};

#endif
