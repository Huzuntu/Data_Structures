#include <fstream>
#include <iostream>
#include <string>

#include "StudentsTrie.h"

using namespace std;
TrieNode::TrieNode (const char& digit){
   this->digit = digit;
   for(int i=0; i<MAX_CHILDREN; children[i++] = NULL); 
};
string Student_Id; 

// Construct a StudentsTrie using the records in 'file_name' 
StudentsTrie::StudentsTrie ( const string& file_name  ) { 
    ifstream student_ids_file ( file_name );   // ifstream object for input file
    string current_student_id;

    root = new TrieNode('r');

    if( student_ids_file.is_open() ) {
        for(int i=1; student_ids_file >> current_student_id; i++ ) {
           insert_id(current_student_id); 
        }
        student_ids_file.close();
    }
    else {
        cout << "File: " << file_name << " could NOT be opened!!";
        exit(1);
    }

    student_ids_file.close();
};


void StudentsTrie::insert_id ( const string& student_id ) {

   TrieNode* current = this->root;

   for(int i = 0; i < student_id.length(); i++){
      char c = student_id[i];
      if(current->children[c - '0'] == NULL){ // (c - '0') is 5. c's ascii value is 53 and '0' is 48.
         current->children[c - '0'] = new TrieNode(c); // Put new Node into the children of the node
         current = current->children[c - '0']; 
      }
      else if(current->children[c - '0']->digit == c){
         current = current->children[c - '0'];
      }
   }
   current->isEndOfStudentNumber = true;
}; 


void StudentsTrie::PrintTrie_Traversely(TrieNode* root, char* OUT, int index){
   if(root->isEndOfStudentNumber){
      if(OUT[9] != 32){ // Put space if it isn't there
         OUT[9] = 32;
      }
      for(int j = 0; j < MAX_CHILDREN; j++){
         Student_Id += OUT[j];
      }
   }
   if(root != NULL){
      for(int i = 0; i < MAX_CHILDREN; i++){
         if(root->children[i] != NULL){
            OUT[index] = '0' + i; 
            PrintTrie_Traversely(root->children[i], OUT, index+1);
         }
      }
      if(root->isEndOfStudentNumber){
         OUT[index] = 32; // Put space if it isn't there
      }
   } 
   
   
};

void StudentsTrie::print_trie(){
   char OUT[MAX_CHILDREN];
   PrintTrie_Traversely(this->root, OUT, 0);
   std::cout << Student_Id;
}


StudentsTrie::~StudentsTrie() {
   for (int i=0; i < MAX_CHILDREN; i++){
      if( root->children[i] ) delete root->children[i];
   };
};

