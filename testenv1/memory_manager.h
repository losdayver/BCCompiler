#pragma once
#include "libraries.h"
#include "logger.h"

using namespace std;

struct MemoryBlock {
    bool isUsed;
    void* ptr;
    int size;

    MemoryBlock() {
        isUsed = false;
        ptr = nullptr;
        size = 0;
    }
};

class MemoryManager {
private:
    void* ptr;
    int size;
    vector<MemoryBlock> blocks;
    int shift = 0;
    int memoryAvailable;
    Logger logger;
    
public:
    MemoryManager(int numBytes, string logName="memManagerLog.txt") : logger(true, 1, logName) {
        size = numBytes;
        memoryAvailable = size;
        ptr = malloc(numBytes);
        logger.LogTime("Created a memory block of " + to_string(size) + " bytes size");
    }

    ~MemoryManager() {
        free(ptr);
        logger.LogTime("Removed a memory block of " + to_string(size) + " bytes size\n\n");
    }

    void Info()
    {
        for (int i = 0; i < blocks.size(); i++)
        {
            if (blocks[i].isUsed) {
                const void* address = static_cast<const void*>(blocks[i].ptr);
                stringstream ss;
                ss << address;
                string stringAddress = ss.str();
                logger.Log("block #" + to_string(i) + ' ' + stringAddress + ' ' + "with size " + to_string(blocks[i].size) + '\n');
            }  
        }
    }

    template<typename T>
    int Allocate(T value) {

        int valueSize = sizeof(value);

        // если в "правой" части блока памяти нет, но в целом памяти хватает, то проводим дефрагментацию
        if ((size - shift < valueSize) && (memoryAvailable >= valueSize)) {
            Defragment();
        }
        
        if (size - shift >= valueSize) {
            void* newPtr = static_cast<char*>(ptr) + shift;
            shift += valueSize;
            memoryAvailable -= valueSize;
            *(T*)newPtr = value;

            MemoryBlock newBlock;
            newBlock.ptr = newPtr;
            newBlock.isUsed = true;
            newBlock.size = valueSize;

            blocks.push_back(newBlock);

            string logMsg = "allocated " + to_string(valueSize)
                + " bytes for "
                + typeid(value).name();

            logger.LogTime(logMsg);
   
            return blocks.size()-1;  // возвращаем индекс блока в векторе
        }
        else {
            string logMsg = "error occured allocating "
                + to_string(valueSize) + " bytes for "
                + typeid(value).name();
            logger.LogTime(logMsg);

            return -1;
        }
    }

    bool Remove(int index) {
        if (index >= 0 && index < blocks.size()) {
            blocks[index].isUsed = false;
            logger.LogTime("removed block of " + to_string(blocks[index].size) + " size");
            memoryAvailable += blocks[index].size;
            return true;
        }
        else {
            logger.LogTime("couldn't find block to delete");
            return false;
        }
    }

    void Defragment() {
        int sortedSize = 0;
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks[i].isUsed) {
                memcpy(static_cast<char*>(ptr) + sortedSize, blocks[i].ptr, blocks[i].size);
                blocks[i].ptr = static_cast<char*>(ptr) + sortedSize;
                sortedSize += blocks[i].size;
            } 
        }
        shift = sortedSize;
        logger.LogTime("Memory block was defragmented");
    }

    template<typename T>
    T Get(int index) {
        if (index >= 0 && index < blocks.size()) {
            if (blocks[index].isUsed) {
                return *(T*)blocks[index].ptr;
            }
        }
        
        logger.LogTime("Couldn't find memory block!");
        return NULL;
    }
};
