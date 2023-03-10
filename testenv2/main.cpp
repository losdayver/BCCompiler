#include <iostream>
#include "MemoryManager.h"

int main()
{
    MemoryManager mm(100);

    mm.Alloc<int>(100);
}