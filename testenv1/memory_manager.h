#pragma once
#include "libraries.h"
#include "logger.h"

using namespace std;

class MemoryManager {
private:
    void* ptr;
    int size;
    vector<void*> blocks;
    vector<void*> vars;
    vector<int> blocksSizes;
    int shift = 0;
    int memoryAvailable;
    Logger logger;
    
public:
    MemoryManager(int numBytes, string logName="memManagerLog.txt") : logger(true, 1, logName) {
        size = numBytes;
        memoryAvailable = size;
        ptr = malloc(numBytes);
    }

    ~MemoryManager() {
        free(ptr);
    }

    void Info()
    {
        for (int i = 0; i < blocksSizes.size(); i++)
        {
            const void* address = static_cast<const void*>(blocks[i]);
            stringstream ss;
            ss << address;
            string stringAddress = ss.str();
            logger.Log("block #" + to_string(i) + ' ' + stringAddress + ' ' + "with size " + to_string(blocksSizes[i]) + '\n');
        }
    }

    template<typename T>
    bool Allocate(T* var, T value) {
        int valueSize = sizeof(value);
        if ((size - shift < valueSize) && (memoryAvailable >= valueSize)) {
            Defragment();
        }
        
        if (size - shift >= valueSize) {
            void* newPtr = static_cast<char*>(ptr) + shift;
            shift += valueSize;
            memoryAvailable -= valueSize;
            *(T*)newPtr = value;
            blocks.push_back(newPtr);
            blocksSizes.push_back(valueSize);
            vars.push_back(var);

            string logMsg = "allocated " + to_string(valueSize)
                + " bytes for "
                + typeid(value).name();
            logger.LogTime(logMsg);
            *var =  *(T*)blocks.back();
            return true;
        }
        else {
            string logMsg = "error occured allocating "
                + to_string(valueSize) + " bytes for "
                + typeid(value).name();
            logger.LogTime(logMsg);

            return false;
        }
    }

    bool Remove(void* pointer) {
        for (int i = 0; i < vars.size(); i++) {
            if (pointer == vars[i]) {
                pointer = NULL;
                blocks.erase(blocks.begin() + i);
                vars.erase(vars.begin() + i);
                memoryAvailable += blocksSizes[i];
                int rm_size = blocksSizes[i];
                blocksSizes.erase(blocksSizes.begin() + i);
                string logMsg = "removed block of " + to_string(rm_size) + " size";
                logger.LogTime(logMsg);
                return true;
            }
        }
        return false;
    }

    void Defragment() {
        int sortedSize = 0;
        for (int i = 0; i < blocks.size(); i++) {
            memcpy(static_cast<char*>(ptr) + sortedSize, blocks[i], blocksSizes[i]);
            blocks[i] = static_cast<char*>(ptr) + sortedSize;
            sortedSize += blocksSizes[i];
        }
        shift = sortedSize;
        logger.LogTime("Memory block was defragmented");
    }
};
