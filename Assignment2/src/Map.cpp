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


#include "Map.h"

using namespace std;

Map::Map(Tree* friend1, Tree* friend2){
    this->friend1 = friend1;
    this->friend2 = friend2;
}

Map::~Map(){
    delete friend1;
    delete friend2;
}

void Map::Cities_into_deque1(Node* root, deque<Node*> &all_cities1){ // This pushes Friend1's cities recursively, takes the deque's address
    if(root == NULL)
        return; 
    all_cities1.push_back(root);
    Cities_into_deque1(root->get_left(), all_cities1);
    Cities_into_deque1(root->get_right(), all_cities1);
}

void Map::get_meeting_point(Tree* friend1, Tree* friend2){ // Gets the minimum total duration and prints it out
    
    deque<Node*> all_cities1; // queue to hold all the cities in friend1_map


    deque<Node*> last_deque; // Queue for total distance Nodes
    Cities_into_deque1(friend1->get_root(), all_cities1); // Pushes all cities in friend1

    while(!all_cities1.empty()){ // Loop until queue is empty
        Node* totalNode = new Node(); // A new node to hold the Total Distances between 2 friends
        totalNode->set_cityname(all_cities1.back()->get_cityname()); // sets the name of the new node
        Node* temp = friend2->search(friend2->get_root(), all_cities1.back()->get_cityname()); // temporary node to find the node in friend2's map. We have the all cities from friend1_map and this line is to get the friend2_map cities
        if(temp != NULL){ // If node is found in the friend2_map we get data from that node
            totalNode->set_total_distance(all_cities1.back()->get_distance_to_root() + temp->get_distance_to_root()); 
        }
        else{ // If node is not in the friend2_map we set it to 1000 which is equal to infinity in this case
            totalNode->set_total_distance(1000);
        }
        all_cities1.pop_back(); // Empty the queue
        last_deque.push_back(totalNode); // Push to the queue which holds total distance nodes
    }
    while(!last_deque.empty()){ // Loop until queue is empty
        if(last_deque.size() == 1){ // If single node is left 
            cout << "MEETING POINT: " << last_deque.front()->get_cityname() << endl; // We print necessary lines
            cout << "TOTAL DURATION COST: " << last_deque.front()->get_total_distance() << endl; // We print necessary lines
            last_deque.pop_back(); // Then we pop and clear the queue
            return;
        }
        else if(last_deque.front()->get_total_distance() > last_deque.back()->get_total_distance()){ //Checks front and back to find minimum total distance
            last_deque.pop_front();
        }
        else if(last_deque.front()->get_total_distance() < last_deque.back()->get_total_distance()){ //Checks front and back to find minimum total distance
            last_deque.pop_back();
        }
    }
    all_cities1.clear(); // Clears queue
}