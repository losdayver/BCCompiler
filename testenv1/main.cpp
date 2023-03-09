#include <iostream>
#include "structures.h"

using namespace std;


int main() {
    stack<int> Stack(100);

    Stack.push(23);
    Stack.push(42);
    Stack.push(18);
  
    Stack.pop();

    Stack.info();


    queue<double> Queue(100);

    Queue.push(12.1);
    Queue.push(14.123);
    Queue.push(0);

    Queue.pop();

    Queue.info();


    dequeue<const char*> Dequeue(200); 

    Dequeue.push_front("1");
    Dequeue.push_front("2");
    Dequeue.push_back("3");

    Dequeue.info();

    Dequeue.pop_front();
    Dequeue.pop_back();
    Dequeue.pop_back();
    Dequeue.pop_front();

    Dequeue.info();
   

    return 0;
}