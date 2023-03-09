#pragma once
#include "libraries.h"
#include "memory_manager.h"
#include "logger.h"

using namespace std;

template<typename T>
class stack {
	list<T> elements;
	MemoryManager mm;
	Logger logger;

public:
	stack(int bytes): mm(bytes), logger(true, 1, "stackLog.txt") {
		elements = {};
	}

	void push(T element) {
		elements.push_back(T());
		if (!mm.Allocate(&elements.back(), element)) {
			elements.pop_back();
		}
	}

	void pop() {
		if (elements.size() == 0) {
			return;
		}
		if (mm.Remove(&elements.back())) {
			elements.pop_back();
		}	
	}

	void info() {
		string message = "";
		message += "Stack info:\n";
		int index = 1;
		for (auto element : elements) {
			ostringstream oss;
			oss << element;
			message += "Element #" + to_string(index) + ": " + oss.str() + "\n";
			index++;
		}
		message += "\n";
		logger.Log(message);
		mm.Info();
	}
};

template<typename T>
class queue {
	list<T> elements;
	MemoryManager mm;
	Logger logger;

public:
	queue(int bytes): mm(bytes), logger(true, 1, "queueLog.txt") {
		elements = {};
	}

	void push(T element) {
		elements.push_back(T());
		if (!mm.Allocate(&elements.back(), element)) {
			elements.pop_back();
		}
	}

	void pop() {
		if (elements.size() == 0) {
			return;
		}
		if (mm.Remove(&elements.front())) {
			elements.pop_front();
		}
	}

	void info() {
		string message = "";
		message += "Queue info:\n";
		int index = 1;
		for (auto element : elements) {
			ostringstream oss;
			oss << element;
			message += "Element #" + to_string(index) + ": " + oss.str() + "\n";
			index++;
		}
		message += "\n";
		logger.Log(message);
		mm.Info();
	}
};

template<typename T>
class dequeue {
	list<T> elements;
	MemoryManager mm;
	Logger logger;

public:
	dequeue(int bytes): mm(bytes), logger(true, 1, "dequeueLog.txt") {
		elements = {};
	}

	void push_back(T element) {
		elements.push_back(T());
		if (!mm.Allocate(&elements.back(), element)) {
			elements.pop_back();
		}
	}

	void push_front(T element) {
		elements.push_front(T());
		if (!mm.Allocate(&elements.front(), element)) {
			elements.pop_front();
		}
	}

	void pop_back() {
		if (elements.size() == 0) {
			return;
		}
		if (mm.Remove(&elements.back())) {
			elements.pop_back();
		}
	}

	void pop_front() {
		if (elements.size() == 0) {
			return;
		}
		if (mm.Remove(&elements.front())) {
			elements.pop_front();
		}
	}

	void info() {
		string message = "";
		message += "Dequeue info:\n";
		int index = 1;
		for (auto element : elements) {
			ostringstream oss;
			oss << element;
			message += "Element #" + to_string(index) + ": " + oss.str() + "\n";
			index++;
		}
		message += "\n";
		logger.Log(message);
		mm.Info();
	}
};
