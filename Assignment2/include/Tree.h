#pragma once
#include "Node.h"
#include <string>
#include <stdbool.h>

using namespace std;

class Tree{
    private:
        Node* root;
        void delete_postorder_traversal(Node*); // deletes tree
                
    public:
        Tree();
        ~Tree();
        
        Node* get_root(); // returns the root of the tree

        void tree_placer(string); // This function does step 1 and step 2 at the same time

        bool contains(Node*, string); // This returns a node is in the tree or not

        Node* search(Node*, string); // Returns the node itself after searching in the tree

        Node* find_par1(Node*, Node*); // Finds and returns the left parent of node
        Node* find_par2(Node*, Node*); // Finds and returns the right parent of node 

        void printPreorder(Node*); // Prints tree in preorder 

};
