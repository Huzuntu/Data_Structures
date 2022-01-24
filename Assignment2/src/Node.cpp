#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "Node.h"

using namespace std;

Node::Node(){
    this->left = NULL;
    this->right = NULL;
    this->distance_to_root = 0;
    this->total_distance = 0;
    this->left_distance = 0;
    this->right_distance = 0;
}

void Node::set_total_distance(int total_distance){
    this->total_distance = total_distance;
}

int Node::get_total_distance(){
    return this->total_distance;
}

void Node::set_distance_to_root(int distance_to_root){
    this->distance_to_root = distance_to_root;
}

int Node::get_distance_to_root(){
    return this->distance_to_root;
}

void Node::set_cityname(string city){
    this->city = city;
}

string Node::get_cityname(){
    return this->city;
}

void Node::set_left(Node* left){
    this->left = left;
}
void Node::set_right(Node* right){
    this->right = right;
}

Node* Node::get_right(){
    return this->right;
}

Node* Node::get_left(){
    return this->left;
}

void Node::set_left_distance(int left_distance){
    this->left_distance = left_distance;
}

void Node::set_right_distance(int right_distance){
    this->right_distance = right_distance;
}

int Node::get_left_distance(){
    return this->left_distance;
}

int Node::get_right_distance(){
    return this->right_distance;
}