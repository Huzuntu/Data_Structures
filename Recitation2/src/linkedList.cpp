#include <iostream>
#include <stdio.h>

#include "linkedList.h"

using namespace std;

LinkedList::LinkedList(){
    head = NULL;
}

LinkedList::~LinkedList(){
    if(head != NULL)
        delete head;
}


Node::Node(char letter){
    this->letter = letter;
}


Node::~Node(){
    if(this->next != NULL)
        delete this->next;
}

void Node::set_letter(char letter){
    this->letter = letter;
};

char Node::get_letter(){
    return this->letter;
};

void Node::set_next(Node* next){
    this->next = next;
};

Node* Node::get_next(){
    return this->next;
};

void LinkedList::add_node(char n){
    Node* new_node = new Node(n);
    if(head == NULL){
        head = new_node;
    }
    else{
        int i = 1;
        Node* temp = head;
        while(temp->get_next() != NULL){
            temp = temp->get_next();
            i++;
        }
        if(temp->get_next() == NULL){
            temp->set_next(new_node);
        }
    }
};

void LinkedList::reorderList(Node* head){
    int swapped;
    Node* cur_node;
    Node* temp_node = NULL;
    if(head == NULL){
        return;
    }
    do
    {
        swapped = 0;
        cur_node = this->head;    
        while(cur_node->get_next() != temp_node){
            if(cur_node->get_letter() > cur_node->get_next()->get_letter()){
                swap_func(cur_node, cur_node->get_next());
                swapped = 1;
            }
            cur_node = cur_node->get_next();
        }
        temp_node = cur_node;
    }
    while(swapped);
    
};

Node* LinkedList::get_head(){
    if(this->head != NULL)
        return this->head;
    else
        return NULL;
};

void LinkedList::swap_func(Node* a, Node* b){
    char temp = a->get_letter();
    a->set_letter(b->get_letter());
    b->set_letter(temp);
};

void LinkedList::removeDublicates(){
    Node* p = head;
    Node* next_node = p->get_next();
    while(next_node != NULL){
        if(p->get_letter() == next_node->get_letter()){
            p->set_next(next_node->get_next());
            //delete next_node;
            //next_node = NULL;
            next_node = p->get_next();
        }
        else{
            p = p->get_next();
            next_node = next_node->get_next();
        }
    }
    
    //FILL THIS FUNCTION ACCORDINGLY
};

void LinkedList::reverseList(){
    
    Node* cur = head;
    Node* next = NULL;
    Node* prev = NULL;

    while(cur != NULL){
        next = cur->get_next();
        cur->set_next(prev);
        prev = cur;
        cur = next;
    }

    head = prev; 
    //FILL THIS FUNCTION ACCORDINGLY  
};

void LinkedList::printList(){
    Node* temp = head;
    while(temp != NULL){
        cout<<temp->get_letter()<<" ";
        temp = temp->get_next();
        //temp->set_next(temp->get_next());
        //temp = temp->get_next();
        //temp = temp->set_next();
    }
    cout<<endl;
};