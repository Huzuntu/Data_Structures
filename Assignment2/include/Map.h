#pragma once
#include "Tree.h"
#include <queue>
using namespace std;

class Map{ // This kinda merges the 2 maps
    private:
        Tree* friend1;
        Tree* friend2;
    public:
        Map(Tree*, Tree*);
        ~Map();
        void get_meeting_point(Tree*, Tree*); // Gets the minimum total duration and prints it out
        void Cities_into_deque1(Node*, deque<Node*>&); // This pushes Friend1's cities 
};