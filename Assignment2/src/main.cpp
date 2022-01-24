#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <sstream>


#include "Map.h"

using namespace std;


int main(int argc, char* argv[]){

    Tree* friend1 = new Tree();
    Tree* friend2 = new Tree();

    string friend1_map = argv[1];
    string friend2_map = argv[2];

    friend1->tree_placer(friend1_map);
    friend2->tree_placer(friend2_map);

    cout << "FRIEND-1: ";
    friend1->printPreorder(friend1->get_root());
    cout << "\n";
    cout << "FRIEND-2: ";
    friend2->printPreorder(friend2->get_root());
    cout << "\n";

    Map* map = new Map(friend1, friend2);

    map->get_meeting_point(friend1, friend2);

    delete map;
    return EXIT_SUCCESS;
}
