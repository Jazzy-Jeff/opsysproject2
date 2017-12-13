//Isaac Dugas dugasi
//Jeff Willoughby willoj
//Gabe Langlois langlg

#include "partition.h"

//Project2.cpp
void printMemory(const list<Partition> &memory);

//Contiguous memory function definitions
void nextFit(std::vector<Process*> processes);
void firstFit(std::vector<Process*> processes);
void bestFit(std::vector<Process*> processes);
int defragmentation(list<Partition> &memory, int &freeMem, string &movedProcesses);
int runContiguous(std::vector<Process> processes, int memSize);
//Non-Contiguous memory function definitions
int runNonContiguous(std::vector<Process> processes, int size);
//Function definitions for both
void mergePartitions(list<Partition> &memory, list<Partition>::iterator loc);
