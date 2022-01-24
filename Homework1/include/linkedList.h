#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>

using namespace std;

class Node{
    private:
        char letter;
        Node* next;
    public:
        Node(char);
        ~Node();
        void set_letter(char);
        char get_letter();
        void set_next(Node*);
        Node* get_next();
};


class LinkedList{

    private:
        Node* head; 
    public:
        Node* get_head();
        void swap_func(Node*, Node*);
        LinkedList();
        ~LinkedList();
        void add_node(char);
        void reorderList(Node*);
        void removeDublicates();
        void reverseList();
        void printList();
};

#endif