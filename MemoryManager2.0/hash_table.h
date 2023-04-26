#pragma once
#include "libraries.h"
#include "memory_manager.h"
#include "logger.h"

using namespace std;

struct htable_element {
    int hash;
    string value;
};

template<typename T>
class htable {
    list<htable_element> elements;
    list<int> indexes;
    Logger logger;
    int size;

    int hash() {

    }

    int resolve_collision() {

    }

public:
    htable(int table_size) : logger(true, 1, "htableLog.txt") {
        elements = {};
        indexes = {};
        this->size = table_size;
    }

    void insert(T value) {

    }

    T operator[](T value) {

    }

    void remove(T value) {

    }
};