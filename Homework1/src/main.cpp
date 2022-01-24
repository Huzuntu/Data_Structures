#include <iostream> 
#include <stdlib.h>
#include <fstream>

#include "linkedList.h"

using namespace std;

int main(int argc, char* argv[]) {
	system("clear");// make this line as comment if you are compiling on Linux or Mac
	//system("cls"); // make this line as comment if you are compiling on Windows

    LinkedList* newLinkedList = new LinkedList();
    
    string file_path = argv[1];
    string line;
    ifstream inFile;
    inFile.open(file_path,ios::in);
    if (!inFile.is_open()) 
    {
        cerr << "File cannot be opened";
    }
    else{
        while(!inFile.eof()){
            while(getline(inFile, line)){
                newLinkedList->add_node(line[0]);    
            }
        }
    }
    cout<<"Readed letters in linked list: ";
    newLinkedList->printList();

    newLinkedList->reorderList(newLinkedList->get_head());
    cout<<"After reordering: ";
    newLinkedList->printList();

    newLinkedList->removeDublicates();
    cout<<"After removing dublicates: ";
    newLinkedList->printList();
    
    newLinkedList->reverseList();
    cout<<"Reversed list: ";
    newLinkedList->printList();


    return EXIT_SUCCESS;
}