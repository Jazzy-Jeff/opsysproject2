#include "partition.h"

//Contiguous memory function definitions
void nextFit(std::vector<Process*> processes);
void firstFit(std::vector<Process*> processes);
void bestFit(std::vector<Process*> processes);
bool defragmentation();
int runContiguous(std::vector<Process> processes);
int runNonContiguous(std::vector<Process> processes, int size);

//Non-Contiguous memory function definitions
