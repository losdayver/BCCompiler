#pragma once
#include "libraries.h"
#include "memory_manager.h"
#include "logger.h"

using namespace std;

template<typename T>
class stack {
	list<T> elements;
	list<int> indexes;
	Logger logger;

public:
	stack(): logger(true, 1, "stackLog.txt") {
		elements = {};
		indexes = {};
	}

	void push(MemoryManager& mm, T element) {
		int index = mm.Allocate<T>(element);
		if (index >= 0) {
			elements.push_front(element);
			indexes.push_front(index);
		}
	}

	void pop(MemoryManager& mm) {
		if (elements.size() == 0) {
			return;
		}
		bool isRemoved = mm.Remove(indexes.front());
		if (isRemoved) {
			elements.pop_front();
			indexes.pop_front();
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
	}
};

template<typename T>
class queue {
	list<T> elements;
	list<int> indexes;
	Logger logger;

public:
	queue(): logger(true, 1, "queueLog.txt") {
		elements = {};
		indexes = {};
	}

	void push(MemoryManager& mm, T element) {
		int index = mm.Allocate<T>(element);
		if (index >= 0) {
			elements.push_back(element);
			indexes.push_back(index);
		}
	}

	void pop(MemoryManager& mm) {
		if (elements.size() == 0) {
			return;
		}
		bool isRemoved = mm.Remove(indexes.front());
		if (isRemoved) {
			elements.pop_front();
			indexes.pop_front();
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
	}
};

template<typename T>
class dequeue {
	list<T> elements;
	list<int> indexes;
	Logger logger;

public:
	dequeue(): logger(true, 1, "dequeueLog.txt") {
		elements = {};
		indexes = {};
	}

	void push_back(MemoryManager& mm, T element) {
		int index = mm.Allocate<T>(element);
		if (index >= 0) {
			elements.push_back(element);
			indexes.push_back(index);
		}
	}

	void push_front(MemoryManager &mm, T element) {
		int index = mm.Allocate<T>(element);
		if (index >= 0) {
			elements.push_front(element);
			indexes.push_front(index);
		}
	}

	void pop_back(MemoryManager& mm) {
		if (elements.size() == 0) {
			return;
		}
		bool isRemoved = mm.Remove(indexes.back());
		if (isRemoved) {
			elements.pop_back();
			indexes.pop_back();
		}
	}

	void pop_front(MemoryManager& mm) {
		if (elements.size() == 0) {
			return;
		}
		bool isRemoved = mm.Remove(indexes.front());
		if (isRemoved) {
			elements.pop_front();
			indexes.pop_front();
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
	}
};
