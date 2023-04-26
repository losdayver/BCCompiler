#include <iostream>
#include "structures.h"
#include "memory_manager.h"
#include "hash_table.h"

using namespace std;

// Показ работы MemoryManager
void Demo1() {
    MemoryManager mm(13);

    int a = mm.Allocate<int>(100);
    int b = mm.Allocate<int>(200);
    int c = mm.Allocate<int>(300);
    int d = mm.Allocate<int>(400);

    mm.Info();

    bool isRemoved = mm.Remove(a);

    mm.Info();

    d = mm.Allocate<int>(400);

    mm.Info();

    cout << mm.Get<int>(b) << " " << mm.Get<int>(c) << " " << mm.Get<int>(d) << endl;

}

// Показ работы структур данных
void Demo2() {

    MemoryManager mm(35);

    stack<int> Stack;

    Stack.push(mm, 23);
    Stack.push(mm, 42);
    Stack.push(mm, 18);

    Stack.pop(mm);

    Stack.info(mm);


    queue<const char*> Queue;

    Queue.push(mm, "avaava");
    Queue.push(mm, "pplplpl");

    mm.Info();
    Queue.push(mm, "kkkkkkk");
    mm.Info();

    Queue.pop(mm);

    Queue.info(mm);


    dequeue<double> Dequeue;

    mm.Info();

    Dequeue.push_front(mm, 1.25);

    mm.Info();
    Dequeue.push_front(mm, 3.23);
    Dequeue.push_back(mm, 4.32);

    Dequeue.info(mm);

    Dequeue.pop_front(mm);
    Dequeue.pop_back(mm);
    Dequeue.pop_back(mm);
    Dequeue.pop_front(mm);

    Dequeue.info(mm);


    mm.Info();

}

// Показ работы хеш таблицы
void Demo3() {
    htable<string> table(37);
    table.insert("food1", "ананас");
    table.insert("food2", "петрушка");
    table.insert("food3", "банан");
    table.insert("food4", "персик");

    table.insert("foo4d", "яблоко");

    table.info();
}

int main() {

    Demo3();

    return 0;
}