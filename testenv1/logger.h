#pragma once
#include "libraries.h"

using namespace std;


class Logger {
    bool loggerOn = false;
    bool loggerMode = 0;
    string logName;
public:
    Logger(bool loggerOn=false, int loggerMode=0, string logName="undefinedLog.txt") {
        this->loggerMode = loggerMode;
        this->loggerOn = loggerOn;
        this->logName = logName;
    }

    void Log(string message)
    {
        if (!loggerOn) {
            return;
        }

        if (loggerMode == 0)
        {
            cout << message;
        }
        else if (loggerMode == 1)
        {
            ofstream fout("./" + logName, ios_base::app);
            fout << message;
        }
    }

    void LogTime(string message)
    {
        // Get the current time
        auto now = chrono::system_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;
        time_t time_now = chrono::system_clock::to_time_t(now);

        // Format the time as a string
        stringstream ss;
#pragma warning(suppress : 4996)
        ss << put_time(localtime(&time_now), "%Y-%m-%d %H:%M:%S.");
        ss << setfill('0') << setw(3) << ms.count();
        string str_time = ss.str();

        string resultMessage = str_time + "    " + message + "\n";

        Log(resultMessage);
    }
};
