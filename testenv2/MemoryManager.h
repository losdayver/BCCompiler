#pragma once
#include <vector>;

using namespace std;

class MemoryManager
{
private:
	// размер всей памяти
	int memSize;
	// указатель на 0 адрес памяти
	void* memPtr;
	// казатель на конец последнего выделенного блока
	int lastPrt = 0;
	// порядковый номер последней выделенной области памяти (записывается в структуру)
	int lastIndex = 0;
	// таблица соответствий порядковых номеров адресам в памяти
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
		// записи в векторе не должны удаляться поскольку при удалении меняется номер записи
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