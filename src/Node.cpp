#include "Node.h"

Node::Node()
{
    mContent = ' ';
    mMarker = false;
}

Node::~Node()
{
}

char Node::content(){
    return mContent;
}

void Node::setContent(char c){
    mContent = c;
}

bool Node::wordMarker(){
    return mMarker;
}

void Node::setWordMarker(){
    mMarker = true;
}

vector<Node*> Node::children(){
    return mChildren;
}

Node* Node::findChild(char c){
    for ( int i = 0; i < mChildren.size(); i++ ){
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c ){
            return tmp;
        }
    }

    return NULL;
}

void Node::appendChild(Node* child){
    mChildren.push_back(child);
}
