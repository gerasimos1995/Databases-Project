#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>

using namespace std;

class Node
{
    public:
        Node();
        ~Node();
        char content();
        void setContent(char);
        bool wordMarker();
        void setWordMarker();
        Node* findChild(char c);
        void appendChild(Node*);
        vector<Node*> children();

    private:
        char mContent;
        bool mMarker;
        vector<Node*> mChildren;
};

#endif // NODE_H
