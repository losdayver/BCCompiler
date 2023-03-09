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
};
