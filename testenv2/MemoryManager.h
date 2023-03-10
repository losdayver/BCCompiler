#pragma once
#include <vector>;

using namespace std;

class MemoryManager
{
private:
	// ������ ���� ������
	int memSize;
	// ��������� �� 0 ����� ������
	void* memPtr;
	// �������� �� ����� ���������� ����������� �����
	int lastPrt = 0;
	// ���������� ����� ��������� ���������� ������� ������ (������������ � ���������)
	int lastIndex = 0;
	// ������� ������������ ���������� ������� ������� � ������
	vector<TableEntry> blockTable;
public:
	MemoryManager(int memSize)
	{
		this->memSize = memSize;
		memPtr = malloc(memSize);
	}
	~MemoryManager() {
		free(memPtr);
	}
	template<typename T>
	int Alloc(T object)
	{
		int blockSize = sizeof(object);
		blockTable.push_back(TableEntry(lastIndex, lastPrt, blockSize));
		lastIndex++;
		void* tempPtr = static_cast<char*>(memPtr) + lastPrt;
		lastPrt += blockSize;
		*(T*)tempPtr = object;

		return blockTable.size() - 1;
	}
	void Dealloc(int index)
	{
		// ������ � ������� �� ������ ��������� ��������� ��� �������� �������� ����� ������
	}
	void Defragment();
};

struct TableEntry
{
	int index;
	int beginPrt;
	int blockSize;

	TableEntry(int index, int lastPrt, int blockSize)
	{
		this->index = index;
		this->beginPrt = lastPrt;
		this->blockSize = blockSize;
	}
};