#include "partition.h"

//Project2.cpp
void printMemory(const list<Partition> &memory);

//Contiguous memory function definitions
void nextFit(std::vector<Process*> processes);
void firstFit(std::vector<Process*> processes);
void bestFit(std::vector<Process*> processes);
bool defragmentation(list<Partition> &memory);
int runContiguous(std::vector<Process> processes, int memSize);

//Non-Contiguous memory function definitions
