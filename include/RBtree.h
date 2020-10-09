#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
#include "Hotel.h"

using namespace std;

struct node
{
       int key;//hotel_id
       string hotel_name;
       int hotel_stars;
       int hotel_rooms;
       node *parent;
       char color;
       node *left;
       node *right;
};
class RBtree
{
   private:
      node *root;
      node *q;
   public :
      RBtree();
      ~RBtree();
      void insert(Hotel *);
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      //void del();
      node* successor(node *);
      //void delfix(node *);
      //void disp();
      //void display( node *);
      void search(int);
};

#endif // RBTREE_H
