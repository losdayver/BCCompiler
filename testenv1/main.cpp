#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <string>
#include <format>

using namespace std;

class MemoryManager {
private:
    // начало блока памяти     1 2 4 5 6          1 2 (3) 4 5 6
    void* ptr;
    int size;
    vector<void*> blocks;
    vector<int> blocksSizes;
    int shift = 0;

    void Log(string message)
    {
        if (logTarget == 0)
        {
            cout << message;
        }
        else if (logTarget == 1)
        {
            ofstream fout("./log.txt");
            fout << message;
        }
    }

    void LogTime(string message)
    {
        // Get the current time
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        std::time_t time_now = std::chrono::system_clock::to_time_t(now);

        // Format the time as a string
        std::stringstream ss;
        #pragma warning(suppress : 4996)
        ss << std::put_time(std::localtime(&time_now), "%Y-%m-%d %H:%M:%S.");
        ss << std::setfill('0') << std::setw(3) << ms.count();
        std::string str_time = ss.str();

        string timeString = "log time: " + str_time;
        string resultMessage = message + " " + timeString + "\n";

        Log(resultMessage);
    }
public:
    bool loggerFlag = false;
    // 0 - console
    // 1 - log.txt
    int logTarget = 0;

    MemoryManager(int numBytes) {
        this->size = numBytes;
        ptr = malloc(numBytes);
        // TODO выяснить че это такое
        //memset(ptr, 0, numBytes);
    }

    ~MemoryManager() {
        free(ptr);
    }

    void LogAll()
    {
        for (int i = 0; i < blocksSizes.size(); i++)
        {
            const void* address = static_cast<const void*>(blocks[i]);
            stringstream ss;
            ss << address;
            string stringAddress = ss.str();
            Log("block #" + to_string(i) + ' ' + stringAddress + ' ' + "with size " + to_string(blocksSizes[i]) + '\n');
        }
    }

    template<typename T>
    T* Allocate(T value) {
        int valueSize = sizeof(value);
        if (size - shift >= valueSize) {
            void* newPtr = static_cast<char*>(ptr) + shift;
            shift += valueSize;
            *(T*)newPtr = value;
            // TODO возможно переделать в структуры
            blocks.push_back(newPtr);
            blocksSizes.push_back(valueSize);

            if (loggerFlag)
            {
                string logMsg = "allocated " + to_string(valueSize) 
                    + " bytes for " 
                    + typeid(value).name();
                LogTime(logMsg);
            }

            return (T*)newPtr;
        }
        else {
            if (loggerFlag)
            {
                string logMsg = "error occured allocating " 
                    + to_string(valueSize) + " bytes for " 
                    + typeid(value).name();
                LogTime(logMsg);
            }

            // TODO Exception
            cout << "oops! " << sizeof(value) << endl;
        }
    }

    void Remove(void* pointer) {
        for (int i = 0; i < blocks.size(); i++) {
            if (pointer == blocks[i]) {
                blocks.erase(blocks.begin() + i);
                blocksSizes.erase(blocksSizes.begin() + i);
                Defragment();
                if (loggerFlag)
                {
                    string logMsg = "removed block";
                    LogTime(logMsg);
                }
                return;
            }
        }
    }

    void Defragment() {
        int sortedSize = 0;
        for (int i = 0; i < blocks.size(); i++) {
            memcpy(static_cast<char*>(ptr) + sortedSize, blocks[i], blocksSizes[i]);
            sortedSize += blocksSizes[i];
        }
        shift = sortedSize;
    }
};

int main() {
    MemoryManager mm(100);
    mm.loggerFlag = true;
    auto a = mm.Allocate<int>(100);
    const char* aboba = "aboba";
    auto b = mm.Allocate<const char*>(aboba);
    auto c = mm.Allocate<double>(101.123);
    auto d = mm.Allocate<char>('a');
    auto e = mm.Allocate<bool>(false);

    mm.LogAll();
    
    mm.Remove(a);
    mm.Remove(d);
    mm.Remove(c);

    cout << *b << endl;

    mm.LogAll();

    auto notEnough = mm.Allocate<int>(999999999999999999);

    auto f = mm.Allocate<double>(405.26);
    auto g = mm.Allocate<char>('g');
    auto h = mm.Allocate<bool>(true);

    mm.LogAll();

    //return 0;
}