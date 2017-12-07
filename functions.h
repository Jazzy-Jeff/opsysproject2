#include "partition.h"

//Project2.cpp
void printMemory(const list<Partition> &memory);

//Contiguous memory function definitions
void nextFit(std::vector<Process*> processes);
void firstFit(std::vector<Process*> processes);
void bestFit(std::vector<Process*> processes);
<<<<<<< HEAD
bool defragmentation();
int runContiguous(std::vector<Process> processes);
int runNonContiguous(std::vector<Process> processes, int size);
=======
void defragmentation(list<Partition> &memory, int &freeMem);
int runContiguous(std::vector<Process> processes, int memSize);
>>>>>>> 9a878f0d90ffc2274e82071d6665be8e31e0a1da

//Non-Contiguous memory function definitions
