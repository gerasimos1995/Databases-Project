#ifndef TRIE_H
#define TRIE_H
#include "Node.h"
using namespace std;

class Trie
{
    public:
        Trie();
        ~Trie();
        void addWord(string s);
        bool searchWord(string s);

    private:
        Node* root;
};

#endif // TRIE_H
