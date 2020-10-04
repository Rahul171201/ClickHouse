#include<bits/stdc++.h>
using namespace std;  
class Queries { 
private: 
    static const int max = 100;                   //A simple Queries class with  basic Queries funtionalities //
    int arr[max]; 
    int top; 
  
public: 
    Queries() { top = -1; } 
    bool isEmpty(); 
    bool isFull(); 
    int pop(); 
    void push(int x); 
}; 
  
bool Queries::isEmpty()               //Checks whether the Queries is empty
{ 
    if (top == -1) 
        return true; 
    return false; 
} 
  

bool Queries::isFull()              //Checks whether the Queries is full
{ 
    if (top == max - 1) 
        return true; 
    return false; 
} 
  

int Queries::pop()                  //function to pop an element from Queries
{ 
    if (isEmpty()) { 
        cout << "Queries Underflow"; 
        abort(); 
    } 
    int x = arr[top]; 
    top--; 
    return x; 
} 
  

void Queries::push(int x)           //function to push an element into Queries
{ 
    if (isFull()) { 
        cout << "Queries Overflow"; 
        abort(); 
    } 
    top++; 
    arr[top] = x; 
} 
  

class TakeQuery : public Queries {            //Special Queries that returns the minimum of queries
    Queries min; 
  
public: 
    int pop(); 
    void push(int x); 
    int getMin(); 
}; 
  

void TakeQuery::push(int x) 
{ 
    if (isEmpty() == true) { 
        Queries::push(x); 
        min.push(x); 
    } 
    else { 
        Queries::push(x); 
        int y = min.pop(); 
        min.push(y); 
        if (x < y) 
            min.push(x); 
        else
            min.push(y); 
    } 
} 
  

int TakeQuery::pop() 
{ 
    int x = Queries::pop(); 
    min.pop(); 
    return x; 
} 
  

int TakeQuery::getMin() 
{ 
    int x = min.pop(); 
    min.push(x); 
    return x; 
} 
  

int main() 
{ 
    TakeQuery s; 
    s.push(100); 
    s.push(201); 
    s.push(300); 
    cout << s.getMin() << endl;           //showing the application of our code
    s.push(5); 
    cout << s.getMin(); 
    return 0; 
} 
