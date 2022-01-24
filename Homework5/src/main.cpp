#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <queue>

using namespace std;

string file_path;


bool perform_operation(char);
void print_menu();
void listProducts();
void listDay();

int main(int argc, char* argv[])
{
    bool end = false;
    char choice;
    ifstream inFile;

    file_path = argv[1];

    inFile.open(file_path,ios::in);
    if (!inFile.is_open()) 
    {
        cerr << "File cannot be opened";
        return EXIT_FAILURE;
    }

    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }
    
    inFile.close();
    return EXIT_SUCCESS;


}


void print_menu()
{
    std::cout << "Choose an operation" << endl;
    std::cout << "L: List 5 products with the highest revenue for total" << endl;
    std::cout << "D: List 5 products with the highest revenue for each day" << endl;
    std::cout << "E: Exit" << endl;
    std::cout << "Enter a choice {L, D, E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listProducts();
        break;
    case 'D':
    case 'd':
        listDay();
        break;
    case 'E':
    case 'e':
            terminate = true;
        break;
    default:
        std::cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listProducts()
{
    map<string, double> product_map;
    ifstream file_obj;
    file_obj.open(file_path, ifstream::in);

    if(!file_obj.is_open()){
        file_obj.open(file_path, ifstream::in);
        if(!file_obj.is_open()){
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }

    string line;
    string orders;
    while(!file_obj.eof()){
        getline(file_obj, line);
        while(getline(file_obj, line)){
            deque<string> products;
            istringstream iss(line);

            while(iss >> orders){
                products.push_back(orders);
            }
            double d_product_price = stod(products.at(1));
            double d_quantity = stod(products.at(2));
            
            double revenue = d_product_price * d_quantity;

            product_map[products.at(0)] += revenue;
        }
    }

    multimap<double, string> store_products;

    for(auto kv : product_map){
        auto& key = kv.first;
        auto& value = kv.second;
        store_products.insert(make_pair(value, key));
    } 
    std::cout << "5 products with the highest revenue for total are:"<<endl;
    multimap<double,string>::reverse_iterator order_it;
    int count;
    for (order_it=store_products.rbegin(),count = 0; count<5 ;order_it++,count++)
        std::cout<<(*order_it).second<<" " << fixed << setprecision(2) <<(*order_it).first<<endl;  
}



void listDay()
{
    ifstream file_objj;
    file_objj.open(file_path, ifstream::in);

    if(!file_objj.is_open()){
        file_objj.open(file_path, ifstream::in);
        if(!file_objj.is_open()){
            cerr << "Could not open the file" << endl;
            exit(1);
        }
    }

    string line;
    string orders;

    map<string, double> Monday_map;
    map<string, double> Tuesday_map;
    map<string, double> Wednesday_map;
    map<string, double> Thursday_map;
    map<string, double> Friday_map;
    map<string, double> Saturday_map;
    map<string, double> Sunday_map;
    vector<map<string,double>> days_queue;
    days_queue.resize(7);

    while(!file_objj.eof()){
        getline(file_objj, line);
        while(getline(file_objj, line)){
            deque<string> products;
            istringstream iss(line);
            while(iss >> orders){
                products.push_back(orders);
            }
            
            double d_product_price = stod(products.at(1));
            double d_quantity = stod(products.at(2));
            double revenue = d_product_price * d_quantity;
            
            if(products.at(3) == "Tuesday"){
                Monday_map[products.at(0)] += revenue;
                days_queue[2] = Monday_map;
            }
            else if(products.at(3) == "Sunday"){
                Sunday_map[products.at(0)] += revenue;
                days_queue[1] = Sunday_map;
            }
            else if(products.at(3) == "Monday"){
                Tuesday_map[products.at(0)] += revenue;
                days_queue[0] = Tuesday_map;
            }
            else if(products.at(3) == "Wednesday"){
                Wednesday_map[products.at(0)] += revenue;
                days_queue[3] = Wednesday_map;
            }
            else if(products.at(3) == "Thursday"){
                Thursday_map[products.at(0)] += revenue;
                days_queue[4] = Thursday_map;
            }
            else if(products.at(3) == "Friday"){
                Friday_map[products.at(0)] += revenue;
                days_queue[5] = Friday_map;
            }
            else if(products.at(3) == "Saturday"){               
                Saturday_map[products.at(0)] += revenue;
                days_queue[6] = Saturday_map;
            }       
        }
    }
    string days[7] = { "Monday", "Sunday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    for(int m = 0; m < 7; m++){
        map<string, double> temp_map;
        
        temp_map = days_queue[m];
        multimap<double, string> store_products;
        for(auto kv : temp_map){
            auto& key = kv.first;
            auto& value = kv.second;
            store_products.insert(make_pair(value, key));
        }
        std::cout << "5 products with the highest revenue for " << days[m] << " are:" << endl;
        
        multimap<double,string>::reverse_iterator order_it;
        
        int count;
        for (order_it=store_products.rbegin(),count = 0; count<5 ;order_it++,count++){
            std::cout<<(*order_it).second<<" " << fixed << setprecision(2) <<(*order_it).first<<endl;  
        }    
        while (!store_products.empty()){    
            store_products.erase(store_products.begin());  
        }         
    }
}