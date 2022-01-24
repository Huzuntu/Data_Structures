#pragma once
#include <string>

using namespace std;

class Node{
    private:
        int left_distance; // Distance to the left child of the node
        int right_distance; // Distance to the Right child of the node
        int distance_to_root; // This is for the node's distance to root in the tree
        int total_distance; // This is for the last part of the problem which wants us to find the total distance
        Node* left;
        Node* right;
        std::string city; // City name
    public:
        Node();
        
        void set_left(Node*);
        void set_right(Node*);


        void set_distance_to_root(int);
        int get_distance_to_root();

        void set_total_distance(int);
        int get_total_distance();

        void set_cityname(std::string);
        string get_cityname();
        Node* get_right();
        Node* get_left();

        void set_left_distance(int);
        void set_right_distance(int);

        int get_left_distance();
        int get_right_distance();

};