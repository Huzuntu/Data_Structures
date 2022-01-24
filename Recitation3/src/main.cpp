/* @Author
Student Name: Umut TÖLEK
Student ID : 150190724
Date: 08.11.2021 */


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <iomanip>
#include <ctype.h> // for isdigit


using namespace std;

void infix_to_postfix(string,string&);
bool higher_priority(char,char);
double eval_postfix(string);
double evaluate(double,double,char);



int main(){
    string infix;
    string postfix;
    bool is_exit = false;


    while(!is_exit)
    {
        cout<<"Input the expression in infix: ";
        cin>>infix;

        if (infix == "E" || infix == "e") 
            is_exit = true;

        else
        {
            infix_to_postfix(infix, postfix);
            cout<<postfix<<endl;
            cout<<setprecision(2)<<fixed<<eval_postfix(postfix)<<endl;
        }
        
        cin.clear();
        cin.ignore();
        infix.clear();
        postfix.clear();

    }
    return EXIT_SUCCESS;
}

void infix_to_postfix(string infix,string& postfix)
{
    stack<char> s;

    for(unsigned int i = 0; i < infix.length(); i++){
        if(isdigit(infix[i])){
            postfix += infix[i];
            if(i + 1 == infix.length()){
                while(s.empty() == false){
                    postfix += s.top();
                    s.pop();
                }
            }
        }
        else if(isdigit(infix[i]) == 0 && s.empty()){
            s.push(infix[i]);
        }
        else{
            if(higher_priority(infix[i], s.top())){
                if(s.top() == '*' || s.top() == '/'){
                    postfix += s.top();
                    s.pop();
                }
                s.push(infix[i]);
            }
            else{
                if(s.size() == 1){
                    while(s.empty() == false){
                        postfix += s.top();
                        s.pop();
                    }
                    postfix += infix[i];    
                }else{
                    while(s.empty() == false){
                        postfix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]); 
                }

            }
        }

    }    
}

bool higher_priority(char first,char second){
    if(first=='*' || first=='/')
        return true;
    else if(second=='+' || second=='-')
        return true;
    else return false;
}




double eval_postfix(string expr){
    stack<double> s;
    double first, second;
    
    for(unsigned int j = 0; j < expr.length(); j++){
        if(isdigit(expr[j])){
            string pusher = "";
            pusher += expr[j];
            double pushing = stod(pusher);
            s.push(pushing);
            if(j + 1 == expr.length()){
                return s.top();
            }
        }
        
        else{
            second = s.top();
            s.pop();
            first = s.top();
            s.pop();
            s.push(evaluate(first, second, expr[j]));
            if(j + 1 == expr.length()){
                return s.top();
            }
        }
    }


    return s.top();
}

double evaluate(double first,double second,char c){
    switch(c){
        case '*':
            return first*second;
        case '+':
            return first+second;
        case '-':
            return first-second;
        case '/':
            return first/second;
        default:
            return 0;
    }
}
