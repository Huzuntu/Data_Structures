#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <queue>


#include "Tree.h"

using namespace std;

Tree::Tree(){
    this->root = NULL;
}

Tree::~Tree(){
    delete_postorder_traversal(this->root);
    this->root = NULL;
    }

void Tree::delete_postorder_traversal(Node* root){ // Deletes tree nodes postorder LY
    if(root!=NULL) 
    {
        delete_postorder_traversal(root->get_left());
        delete_postorder_traversal(root->get_right());
        delete root;
        root = NULL;
    }
}

Node* Tree::get_root(){
    return this->root;
}

bool Tree::contains(Node* top, string cities){ // Recursive function to check whether a tree has a node in that city name
    if (top == NULL)
        return false;
 
    if (top->get_cityname() == cities)
        return true;
 
    bool res1 = contains(top->get_left(), cities);
    if(res1) return true;
 
    bool res2 = contains(top->get_right(), cities);
    return res2;
}

Node* Tree::search(Node* top, string cities){ // Recursive function to search and return a node in that name
    if(top != NULL){
        if(top->get_cityname() == cities){
           return top;
        } else {
            Node* Noded = search(top->get_left(), cities);
            if(Noded == NULL) {
                Noded = search(top->get_right(), cities);
            }
            return Noded;
         }
    } else {
        return NULL;
    }
}


void Tree::printPreorder(Node* root){ // Recursive function that prints the tree preorder LY
    if (root == NULL)
        return;
    cout << root->get_cityname() << " ";
    printPreorder(root->get_left());
    printPreorder(root->get_right());
}


Node* Tree::find_par1(Node* head, Node* node){ // Recursive function to find the left parent of a node
    if(head != NULL){
        if(head->get_left() == node){
            return head;
        }
        else{
            Node* Noded = find_par1(head->get_left(), node);
            if(Noded == NULL){
                Noded = find_par1(head->get_right(), node);
            }
            return Noded;
        }
    }
    else{
        return NULL;
    }
}


Node* Tree::find_par2(Node* head, Node* node){ // Recursive function to find the right parent of a node
    if(head != NULL){
        if(head->get_left() == node){
            return head;
        }
        else{
            Node* Noded = find_par2(head->get_right(), node);
            if(Noded == NULL){
                Noded = find_par2(head->get_left(), node);
            }
            return Noded;
        }
    }
    else{
        return NULL;
    }
}

void Tree::tree_placer(string friend_map){
    
    ifstream file_obj; //Object to read file
    file_obj.open(friend_map, ifstream::in);
    
    if (!file_obj.is_open()){ // Checks whether the file opened or not
        file_obj.open(friend_map, ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    string line;
    string sub;
    while(!file_obj.eof()){ // Reads the file to the end of it

        while(getline(file_obj, line)){ // Line by line
    
            int j = 0;
            string cities[3] = {}; // Every line consist of 3 elements
            istringstream iss(line); // To separate 3 elements


            while(iss >> sub){ // After separating pushing the data into the cities[3] array
                cities[j] = sub;
                j++;
            }
            
            Node* n = new Node();
            if(this->root == NULL){ // This is only for the start of the tree
                n->set_cityname(cities[0]);
                root = n; 
            }
            if(this->contains(this->root, cities[0])){ // Checks for the cities[0] which is always true after setting the root of the tree
                Node* temp = new Node();

                n = this->search(this->root, cities[0]); // Finds the node of that name

                if(n->get_left() == NULL){ // If the left is NULL we start by setting the left of the node
                    if(this->contains(this->root, cities[1])){ // Checks if a node is already in a tree
                        temp = this->search(this->root, cities[1]);
                    }
                    else{ // If not we set the name of the new node
                        temp->set_cityname(cities[1]);
                    }
                    n->set_left(temp); // Then we set left of the node
                    const char *a = cities[2].c_str(); // This is for converting string to integer 
                    int i = atoi(a);
                    n->set_left_distance(i);
                    if(temp == root->get_left()){ // Only for root's left
                        temp->set_distance_to_root(i);
                    }
                    else{
                        if(n->get_left_distance() > 0){ 
                            if(temp->get_distance_to_root() > 0){ // This checks if a node is already added and has a distance to the root
                                if(temp->get_distance_to_root() < (i + (n->get_distance_to_root()))) // If new distance is higher than the before
                                {
                                    n->set_left_distance(0);
                                    n->set_left(NULL);
                                }
                                else // If new distance is lower
                                {
                                    Node* temp_par = find_par1(this->root, temp); // Finds the left parent
                                    Node* temp_par2 = find_par2(this->root, temp); // Finds the right parent
                                    if(temp_par->get_distance_to_root() > temp_par2->get_distance_to_root()) // If left parents distance to the root is higher
                                    {
                                        temp_par->set_left(NULL); // We prune the left parent side
                                        temp_par->set_left_distance(0);
                                    }
                                    else if(temp_par->get_distance_to_root() < temp_par2->get_distance_to_root()) // If right parents distance to the root is higher
                                    {
                                        temp_par2->set_left(NULL); // We prune the right parent side
                                        temp_par2->set_left_distance(0);
                                    }
                                    temp->set_distance_to_root((i + n->get_distance_to_root())); // After pruning we set distance to the root
                                }
                            }
                            else // If node doesn't have a distance to the root we set it
                            {
                                temp->set_distance_to_root((i + n->get_distance_to_root()));
                            }
                            
                        }  
                    }
                }
                else if(n->get_right() == NULL){ // After setting the left if right is NULL we set right of the node
                    if(this->contains(this->root, cities[1])){ // Checks if a node is already in a tree
                        temp = this->search(this->root, cities[1]);
                    }
                    else{ // If not we set the name of the new node
                        temp->set_cityname(cities[1]);
                    }
                    n->set_right(temp); // Then we set right of the node
                    const char *a = cities[2].c_str(); // This is for converting string to integer 
                    int i = atoi(a);
                    n->set_right_distance(i);
                    if(temp == root->get_right()){ // Only for root's right
                        temp->set_distance_to_root(i);
                    }
                    else{
                        if(n->get_right_distance() > 0){ 
                            if(temp->get_distance_to_root() > 0){ // This checks if a node is already added and has a distance to the root
                                if(temp->get_distance_to_root() < (i + (n->get_distance_to_root()))) // If new distance is higher than the before
                                {
                                    n->set_right_distance(0);
                                    n->set_right(NULL);
                                }
                                else // If new distance is lower
                                {
                                    Node* temp_par = find_par1(this->root, temp); // Finds the left parent
                                    Node* temp_par2 = find_par2(this->root, temp); // Finds the right parent
                                    if(temp_par->get_distance_to_root() > temp_par2->get_distance_to_root()){ // If left parents distance to the root is higher
                                        temp_par->set_right(NULL); // We prune the left parent side
                                        temp_par->set_right_distance(0);
                                    }
                                    else if(temp_par->get_distance_to_root() < temp_par2->get_distance_to_root()){
                                        temp_par2->set_right(NULL); // We prune the right parent side
                                        temp_par2->set_right_distance(0);
                                    }
                                    temp->set_distance_to_root((i + n->get_distance_to_root())); // After pruning we set distance to the root      
                                }
                            }
                            else{ // If node doesn't have a distance to the root we set it
                                temp->set_distance_to_root((i + n->get_distance_to_root()));
                            }
                        }
                    }
                }
            }
        }
    }
}
