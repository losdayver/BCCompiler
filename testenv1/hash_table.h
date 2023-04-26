#pragma once
#include "libraries.h"
#include "memory_manager.h"
#include "logger.h"

using namespace std;

template<typename T>
class htable {
    struct htable_element {
        string key;
        T value;
    };

    vector<vector<htable_element>> elements;
    vector<int> indexes;
    Logger logger;
    int size;



    unsigned long hash(string key) {
        const char* str = key.c_str();
        unsigned long h = 86969;
        while (*str) {
            h = (h * 54059) ^ (str[0] * 76963);
            str++;
        }

        return h % size;
    }


public:
    htable(long table_size) : logger(true, 1, "htableLog.txt") {
        this->size = table_size;
        for (int i = 0; i < size; i++) {
            elements.push_back(vector<htable_element> {});
            indexes.push_back(-1);
        }
    }

    void insert(string key, T value) {
        unsigned long h = hash(key);
        if (elements[h].size() == 0) {
            elements[h].push_back({ key, value });
        }
        else {
            for (size_t i = 0; i < elements[h].size(); i++) {
                if (elements[h][i].key == key) {
                    elements[h][i].value = value;
                    return;
                }
            }
            elements[h].push_back({ key, value });
        }

    }

    T get(string key) {
        unsigned long h = hash(key);
        for (size_t i = 0; i < elements[h].size(); i++) {
            if (elements[h][i].key == key) {
                return elements[h][i].value;
            }
        }

        return NULL;
    }

    void remove(string key) {
        unsigned long h = hash(key);
        for (size_t i = 0; i < elements[h].size(); i++) {
            if (elements[h][i].key == key) {
                elements[h].erase(i);
                break;
            }
        }
    }

    void info() {
        string message = "";
        message += "Hash table info:\n";
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < elements[i].size(); j++) {
                ostringstream oss;
                cout << i << endl;
                oss << elements[i][j].value;
                message += elements[i][j].key + " : " + oss.str() + "\n";
            }
        }
        message += "\n";
        logger.Log(message);
    }


};