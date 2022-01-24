/* @Author
Student Name: Umut TÖLEK
Student ID : 150190724
Date: 06/11/2021 */


#ifndef _H
#define _H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class materialNode{
    public:
        materialNode(char, int);
        ~materialNode();
        char id; 
        int weight; 
        materialNode* next;
};

class wagonNode{
    public:
        int wagonId;
        materialNode* material;
        wagonNode* next;
        wagonNode();
        ~wagonNode();
        
};

class Train{  

    wagonNode* head;
    
    public:
        ~Train();
        void create();
        void add_wagon();
        void addMaterial(char,int);
        void deleteFromWagon(char, int); 
        void printWagon(); //Prints wagon info
        wagonNode* search_last_wagon();
        void reorder_char(wagonNode*);
        wagonNode* search_materials_lastWagon(char);
        wagonNode* prev_wagon(wagonNode*);
};

#endif