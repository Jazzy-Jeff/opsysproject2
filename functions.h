#include "partition.h"

//Contiguous memory function definitions
void nextFit(std::vector<Process*> processes);
void firstFit(std::vector<Process*> processes);
void bestFit(std::vector<Process*> processes);
bool defragmentation();
int runContiguous(std::vector<Process*> processes);

//Non-Contiguous memory function definitions