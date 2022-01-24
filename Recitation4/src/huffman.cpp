#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include <cmath>
#include "huffman.h"

using namespace std;

Node::Node(){
    this->prev = NULL;
    this->next = NULL;
    this->left = NULL;
    this->right = NULL;
}

int Huffman::findindex(Token *arr,string elem){
    for(int i = 0; i < token_count; i++){
        if(arr[i].symbol == elem){
            return i;
        }
    }
    return -1;
}

void Huffman::find_frequencies()
{
    ifstream file_obj; //object to read file
    file_obj.open("../input.txt",ifstream::in);
    char symbol = 0;
    if (!file_obj.is_open()) {
        file_obj.open("input.txt",ifstream::in);
        if (!file_obj.is_open()) {
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }
    while (file_obj.get(symbol)) 
    {
        string s;
        s.push_back(symbol);

        bool already_in = false;

        for(int i = 0; i < token_count; i++){
            if(token_array[i].symbol[0] == symbol){
                token_array[i].count++;
                already_in = true;
            }
        }
        if(already_in == false){
            Token tokenA;
            tokenA.symbol = symbol;
            tokenA.count += 1;
            token_array[token_count] = tokenA;
            token_count++;
        }    
    }
    file_obj.close();
}



PriorityQueue::PriorityQueue()
{
    head = NULL;
    token_count = 0;
    tail = NULL;
}


void PriorityQueue::push(Node *newnode)
{   
    if(this->tail == NULL){
        head = newnode;
        head->prev = NULL;
        tail = newnode;
        token_count++;
    }
    else if(head->token.count > newnode->token.count){
        token_count++;
        head->next = newnode;
        newnode->prev = head;
        head = newnode;
    }
    else{
        Node* temp = new Node();
        temp = head;
        if(temp->prev != NULL){
            while(newnode->token.count >= temp->token.count){
                if(temp->prev == NULL){                   
                    token_count++;
                    newnode->next = tail;
                    tail->prev = newnode;
                    tail = newnode;
                    newnode->prev = NULL;
                    break;
                }
                else if(temp->prev->token.count >= newnode->token.count){
                    
                    token_count++;
                    temp->prev->next = newnode;
                    newnode->prev = temp->prev;
                    temp->prev = newnode;
                    newnode->next = temp;
                    break;
                }
                else{
                    temp = temp->prev;
                }
            }
        }
        else{
            token_count++;
            newnode->next = tail;
            tail->prev = newnode;
            tail = newnode;
            newnode->prev = NULL;
        }
        
    }
}


Node* PriorityQueue::pop()
{
    Node *temp;
 
    if(token_count == 1){
        temp = this->head;
        head = NULL;
        tail = NULL;
        token_count--;
    }
    else{
        temp = this->head;
        head = head->prev;
        head->next = NULL;
        temp->prev = NULL;
        token_count--;
        
    }
    return temp;
}

void Huffman::get_priority_queue()
{   
    for(int i = 0; i < token_count; i++){
        Node* NodeA = new Node();
        Token TempA;
        TempA = token_array[i];
        NodeA->token.symbol = TempA.symbol;
        NodeA->token.code = TempA.code;
        NodeA->token.count = TempA.count;
        
        priority_queue.push(NodeA);
    }   

}

HuffmanBinaryTree::HuffmanBinaryTree()
{
    root = NULL;
}

Node * HuffmanBinaryTree::merge(Node *node1, Node *node2)
{
    Node* parr = new Node();
    if(node1->token.count <= node2->token.count){
        parr->left = node1;
        parr->right = node2;
        parr->token.count = node1->token.count + node2->token.count;
        string str = node1->token.symbol + node2->token.symbol;
        parr->token.symbol = str;    
    }
    else{
        parr->left = node2;
        parr->right = node1;
        parr->token.count = node2->token.count + node1->token.count;
        parr->token.symbol = node2->token.symbol + node1->token.symbol;
    }
    return parr;
}

void HuffmanBinaryTree::delete_postorder_traversal(Node *traversal)
{
    if(traversal!=NULL) 
    {
        delete_postorder_traversal(traversal->left);
        delete_postorder_traversal(traversal->right);
        delete traversal;
    }
}

HuffmanBinaryTree::~HuffmanBinaryTree()
{
    delete_postorder_traversal(root);
    cout<<"Code with no memory leak ;)"<<endl;
    root = NULL;
}

void Huffman::get_huffman_tree()
{
    
    while(priority_queue.token_count != 1){
        Node* Node1;
        Node* Node2;
        Node* par_mer;
        Node1 = priority_queue.pop();
        Node2 = priority_queue.pop();
        par_mer = huffman_binary_tree.merge(Node1, Node2);
        priority_queue.push(par_mer);
        if(priority_queue.token_count == 1){
            Node* NodeRoot;
            NodeRoot = priority_queue.pop();
            huffman_binary_tree.root = NodeRoot;
            break;
        }
    }
}

bool Huffman::isLeaf(Node* node) {
    if (node == NULL)
        return false;    
    if (node->right == NULL && node->left == NULL)
        return true;
    return false; 
}

void Huffman::get_codes(Node *traversal,string codepart)
{    
    if(traversal->left)
    {
        get_codes(traversal->left,codepart + "0");
    }
    else
    {
        int index=findindex(token_array,traversal->token.symbol);
        token_array[index].code = codepart;
    }    
    if(traversal->right)
    {
        get_codes(traversal->right,codepart + "1");
    }
    else 
    {        
        int index=findindex(token_array,traversal->token.symbol);
        token_array[index].code = codepart; 
    }
}

string Huffman::return_code(string target)
{
    int index = findindex(token_array,target);
    return token_array[index].code;
}

double Huffman::calculate_compression_ratio()
{
    double bit_required_before = 0;
    for(int i=0;i<token_count;i++)
        bit_required_before += token_array[i].count * 8;
    double bit_required_after = 0;
    for(int i=0;i<token_count;i++)
        bit_required_after += token_array[i].count * token_array[i].code.length();
    return bit_required_before / bit_required_after;
}
