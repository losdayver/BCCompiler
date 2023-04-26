#pragma once
#include "libraries.h"
#include "memory_manager.h"
#include "logger.h"

using namespace std;

template<typename T>
class htable {
    vector<vector<int>> keys_indexes;
    vector<vector<int>> values_indexes;
    Logger logger;
    int size;

    unsigned long hash(const char * key) {
        unsigned long h = 86969;
        while (*key) {
            h = (h * 54059) ^ (key[0] * 76963);
            key++;
        }

        return h % size;
    }


public:
    htable(long table_size) : logger(true, 1, "htableLog.txt") {
        this->size = table_size;
        for (int i = 0; i < size; i++) {
            keys_indexes.push_back(vector<int> {});
            values_indexes.push_back(vector<int> {});
        }
    }

    void insert(MemoryManager& mm, const char* key, T value) {
        unsigned long h = hash(key);

        //for (int i = 0; i < keys_indexes[h].size(); i++) {
         //   if (mm.Get<const char*>(keys_indexes[h][i]) == key) {
         //       return;
        //    }
       // }
        
        int i1 = mm.Allocate<T>(value);
        if (i1 >= 0) {
            int i2 = mm.Allocate<const char*>(key);
            if (i2 >= 0) {
                keys_indexes[h].push_back(i2);
                values_indexes[h].push_back(i1);
            }
            else {
                mm.Remove(i1);
            }
        }
    }

    T get(MemoryManager& mm, const char* key) {
        unsigned long h = hash(key);
        for (size_t i = 0; i < keys_indexes[h].size(); i++) {
            if (mm.Get<const char*>(keys_indexes[h][i]) == key) {
                return mm.Get<T>(values_indexes[h][i]);
            }
        }

        return NULL;
    }

    void remove(MemoryManager& mm, const char* key) {
        unsigned long h = hash(key);
        for (int i = 0; i < keys_indexes[h].size(); i++) {
            if (mm.Get<const char*>(keys_indexes[h][i]) == key) {
                mm.Remove(keys_indexes[h][i]);
                mm.Remove(values_indexes[h][i]);
                keys_indexes[h].erase(keys_indexes[h].begin() + i);
                values_indexes[h].erase(values_indexes[h].begin() + i);
                break;
            }
        }
    }

    void info(MemoryManager& mm) {
        string message = "";
        message += "Hash table info:\n";
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < keys_indexes[i].size(); j++) {
                cout << i << " " << j << endl;
                ostringstream oss;
                oss << mm.Get<T>(values_indexes[i][j]);
                const char* key = mm.Get<const char*>(keys_indexes[i][j]);
                message += string(key) + " : " + oss.str() + "\n";
            }
        }
        message += "\n";
        logger.Log(message);
    }


};