#pragma once
#include "libraries.h"
#include "memory_manager.h"
#include "logger.h"

using namespace std;

template<typename T>
class stack {
    list<int> indexes;
    Logger logger;

public:
    stack() : logger(true, 1, "stackLog.txt") {
        indexes = {};
    }

    void push(MemoryManager& mm, T element) {
        int index = mm.Allocate<T>(element);
        if (index >= 0) {
            indexes.push_front(index);
        }
    }

    void pop(MemoryManager& mm) {
        if (indexes.size() == 0) {
            return;
        }
        bool isRemoved = mm.Remove(indexes.front());
        if (isRemoved) {
            indexes.pop_front();
        }
    }

    void info(MemoryManager& mm) {
        string message = "";
        message += "Stack info:\n";
        int i = 1;
        for (auto index : indexes) {
            ostringstream oss;
            oss << mm.Get<T>(index);
            message += "Element #" + to_string(i) + ": " + oss.str() + "\n";
            i++;
        }
        message += "\n";
        logger.Log(message);
    }
};

template<typename T>
class queue {
    list<int> indexes;
    Logger logger;

public:
    queue() : logger(true, 1, "queueLog.txt") {
        indexes = {};
    }

    void push(MemoryManager& mm, T element) {
        int index = mm.Allocate<T>(element);
        if (index >= 0) {
            indexes.push_back(index);
        }
    }

    void pop(MemoryManager& mm) {
        if (indexes.size() == 0) {
            return;
        }
        bool isRemoved = mm.Remove(indexes.front());
        if (isRemoved) {
            indexes.pop_front();
        }
    }

    void info(MemoryManager& mm) {
        string message = "";
        message += "Queue info:\n";
        int i = 1;
        for (auto index : indexes) {
            ostringstream oss;
            oss << mm.Get<T>(index);
            message += "Element #" + to_string(i) + ": " + oss.str() + "\n";
            i++;
        }
        message += "\n";
        logger.Log(message);
    }
};

template<typename T>
class dequeue {
    list<int> indexes;
    Logger logger;

public:
    dequeue() : logger(true, 1, "dequeueLog.txt") {
        indexes = {};
    }

    void push_back(MemoryManager& mm, T element) {
        int index = mm.Allocate<T>(element);
        if (index >= 0) {
            indexes.push_back(index);
        }
    }

    void push_front(MemoryManager& mm, T element) {
        int index = mm.Allocate<T>(element);
        if (index >= 0) {
            indexes.push_front(index);
        }
    }

    void pop_back(MemoryManager& mm) {
        if (indexes.size() == 0) {
            return;
        }
        bool isRemoved = mm.Remove(indexes.back());
        if (isRemoved) {
            indexes.pop_back();
        }
    }

    void pop_front(MemoryManager& mm) {
        if (indexes.size() == 0) {
            return;
        }
        bool isRemoved = mm.Remove(indexes.front());
        if (isRemoved) {
            indexes.pop_front();
        }
    }

    void info(MemoryManager& mm) {
        string message = "";
        message += "Dequeue info:\n";
        int i = 1;
        for (auto index : indexes) {
            ostringstream oss;
            oss << mm.Get<T>(index);
            message += "Element #" + to_string(i) + ": " + oss.str() + "\n";
            i++;
        }
        message += "\n";
        logger.Log(message);
    }
};