/* @Author
Student Name: Umut TÖLEK
Student ID : 150190724
Date: 06/11/2021 */

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "linkedList.h"

using namespace std;

materialNode::materialNode(char id, int weight){
    this->id = id;
    this->weight = weight;
    this->next = NULL;
};

materialNode::~materialNode(){
    if(this->weight == 0 && this->id == '\0'){
        delete this->next;
    }
    
};

wagonNode::wagonNode(){
    this->wagonId = 0;
    this->material = NULL;
    this->next = NULL;
};

wagonNode::~wagonNode(){
    materialNode* current_material = this->material;
    materialNode* next_material = NULL;
    while(current_material != NULL){
        next_material = current_material->next;
        delete current_material;
        current_material = next_material;
    }
}

Train::~Train(){
    wagonNode* current_wagon = head;
    wagonNode* next_wagon = NULL;
    while(current_wagon != NULL){
        next_wagon = current_wagon->next;
        delete current_wagon;
        current_wagon = next_wagon;
    }
}

void Train::create(){
    head = NULL;
}; 


void Train::add_wagon(){ // ADDS WAGON
    wagonNode* p = new wagonNode();
    int i = 1;
    if(head == NULL){  // IF train is empty then adds to the head
        p->wagonId = i;
        head = p;
    }
    else{
        wagonNode* last = this->search_last_wagon(); // If train is not empty and there are some wagons adds to the end of the wagon and links
        i = last->wagonId + 1;
        p->wagonId = i;
        last->next = p;
    }
};



wagonNode* Train::search_materials_lastWagon(char mat_id){ // This function helps to find the materials last location in terms of wagon when removing
    wagonNode* p = this->head; 
    materialNode* first = p->material;
    while(p != NULL){
        if(first == NULL){
            wagonNode* prevWagon = this->prev_wagon(p);
            return prevWagon;
        }
        if(first->id == mat_id){
            if(p->next != NULL){
                p = p->next;
                first = p->material;    
            }
            else{
                break;
            }
        }
        else{
            first = first->next;
        }    
    }
    return p;
};

wagonNode* Train::prev_wagon(wagonNode* current){ // Since we must use single linked lists // This function returns the previous wagon
    wagonNode* p = this->head;

    while(p->next != NULL){ // If there is no wagon it doesn't go into this loop and returns head
        if(current->wagonId == 1){
            return this->head;
        }else{
            if(p->next->wagonId == current->wagonId){
                return p;
            }
            p = p->next;
        }
    }
    return p;
};

wagonNode* Train::search_last_wagon(){ // This starts the search from head to the end of the train and returns the last wagon on the train
    wagonNode* p = this->head;
    if(p == NULL){
        return p;
    }
    else{
        while(p->next != NULL){
            p = p->next;
        }
        return p;
    }
    
};


void Train::reorder_char(wagonNode* p){ // Didn't know materials had priorities so I added this function to reorder into ABCD 
    materialNode* first_mat = p->material;
    for(int k = 0; k < 11; k++){ // DCBA --> ABCD max
        if(first_mat->next != NULL){ 
            if(first_mat->id > first_mat->next->id){
                materialNode* temp = new materialNode(first_mat->id, first_mat->weight);
                first_mat->id = first_mat->next->id;
                first_mat->next->id = temp->id;
                first_mat->weight = first_mat->next->weight;
                first_mat->next->weight = temp->weight;                
            }
            else{
                first_mat = first_mat->next;
            }
        }
        else{
            first_mat = p->material;
        }
    }
};


void Train::addMaterial(char material, int weight){
    int weightt = weight;
    char mat_id = material;
    wagonNode* p = this->head;

    while(weightt != 0){
        if(head == NULL){ // adding if there is nothing
            add_wagon();
            wagonNode* last = this->search_last_wagon();
            p = last;
            if(weightt <= 2000){ 
                materialNode* added_mat = new materialNode(mat_id, weightt);
                last->material = added_mat;
                weightt = 0;
            }else{
                materialNode* new_mat = new materialNode(mat_id, 2000);
                last->material = new_mat;
                weightt -= 2000;
            }
        }
        else{ // There are some materials already loaded
            materialNode* first = p->material; 
            if(first == NULL){ // This is for weight > 2000 
                if(weightt <= 2000){ // We loaded 2000 for the first wagon and this is for the rest of the materials
                    materialNode* new_mat = new materialNode(mat_id, weightt);
                    p->material = new_mat; 
                    weightt = 0;
                }
                else{ // If there are still more than 2000 materials to be loaded we load them and add new wagon
                    materialNode* new_mat = new materialNode(mat_id, 2000);
                    p->material = new_mat;
                    weightt -= 2000;
                    if(weightt > 0)
                        add_wagon();
                }            
            }
            else{
                while(first != NULL){ // This searches through materials in the wagon
                    if(first->id == mat_id){ // If founds and rest is < 2000 loads the rest
                        if(weightt + first->weight <= 2000){
                            first->weight = weightt + first->weight;
                            weightt = 0;
                            break;
                        }else{
                            weightt -= (2000 - first->weight); // If there are still more 2000 materials weightt is updated and adds new wagon
                            first->weight = 2000;
                            if(p->next == NULL && weightt > 0)
                                add_wagon();
                            break;
                        }
                        first = first->next;
                    }
                    else if(first->next == NULL){ // This is for the end of the wagon // Search is ended and if we are at the end of the wagon
                        if(weightt <= 2000){ // This adds the materials to the end
                            materialNode* new_mat = new materialNode(mat_id, weightt);
                            first->next = new_mat; 
                            weightt = 0;
                            break;
                        }
                        else{ // If there are more than 2000 materials adds 2000 and adds a new wagon
                            materialNode* new_mat = new materialNode(mat_id, 2000);
                            first->next = new_mat;
                            weightt -= 2000;
                            if(p->next == NULL && weightt > 0)
                                add_wagon();
                        }   
                    }
                    else{
                        first = first->next;
                    }
                }
            }
            reorder_char(p); // This reorders the wagon before going to the next wagon
            p = p->next;  
        }
    }
}; 

void Train::deleteFromWagon(char material, int weight){
    int weightt = weight;
    char mat_id = material;
    
    while(weightt != 0){
        wagonNode* p = this->search_materials_lastWagon(mat_id);
        materialNode* first = p->material;
        while(first != NULL){   // This searches through the last wagon where the material is located
            if(first->id == mat_id){ 
                if(weightt < first->weight){ // If amount wants to be removed is < there is in the materialNode
                    first->weight -= weightt;
                    weightt = 0;
                    break;
                }
                else{
                    weightt -= first->weight; // If not
                    first->weight = 0;
                    materialNode* prev_mat = p->material; // We need the previous material to link after removing the current materialNode

                    while(prev_mat->next != NULL){ //This searches through for the previous materialNode
                        if(prev_mat == first){ // When founds the prev
                            p->material = first->next; //First links the next then
                            delete first; // Deletes the materialNode wanted to be removed
                            break;
                        }
                        else if(prev_mat->next == first){ // If we are at the end of the wagon
                            prev_mat->next = first->next;
                            delete first;
                            break;
                        }
                        else{
                            prev_mat = prev_mat->next;
                        }
                    }
                
                    if(p->material == first){ // If there is one materialNode left 
                        p->material = NULL;
                        first->id = '\0'; // This is for the destructor
                        delete first;
                        wagonNode* prevWagon = prev_wagon(p); // Finds previous wagon if there is one and links it to NULL because we removed the last wagon
                        prevWagon->next = NULL;
                        if(p == this->head){ // This is for the Train destructor
                            head = NULL;
                        }
                        delete p; // Deletes the current wagon
                    }
                    break;
                }
            }else{
                first = first->next;
            }
        }
    }
};

void Train::printWagon(){
    wagonNode* tempWagon = head;

    if(tempWagon == NULL){
            cout<<"Train is empty!!!"<<endl;
            return;
    }

    while(tempWagon != NULL){
        materialNode* tempMat = tempWagon->material;
        cout<<tempWagon->wagonId<<". Wagon:"<<endl; 
        while (tempMat != NULL){
            cout<<tempMat->id<<": "<<tempMat->weight<<"KG, "; 
            tempMat = tempMat->next;  
        }
        cout<<endl; 
        tempWagon = tempWagon->next;
    }
    cout<<endl;
}; 

