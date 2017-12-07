#include <vector>
#include <list>
#include <iterator>

#include "functions.h"

using namespace std;

void addPartition(list<Partition> &memory, const list<Partition>::iterator &loc, Process &proc ) {
  if((*loc).getSize() == proc.getSize()) {
    (*loc).assignPartition(&proc);
  }
  else {
    int newSize = (*loc).getSize() - proc.getSize();
    (*loc).updateSize(newSize);
    Partition newPart = Partition(&proc, proc.getSize());
    memory.insert(loc, newPart);
  }
}

void nextFit(vector<Process> processes, int memSize) {
  
}

void firstFit(vector<Process> processes, int memSize) {
  cout<< "Start First Fit algorithm" << endl;
  list<Partition> memory;
  memory.push_back(Partition(NULL, memSize));
  int time = 0;
  int freeMem = memSize;
  //while there are processes left to be processed
  while(processes.size() > 0) { // remove processes from vector or keep variable count of finished processes
    for(unsigned int i = 0; i < processes.size(); i++) {
      if(processes[i].getArrivalTime() == time) {
	//add process to memory if possible
	//  print memory if added
	//else if defragmentation() possible do it
	//else skip process
	bool partitionAdded = false;
	if(freeMem >= processes[i].getSize()) {
	  for(list<Partition>::iterator itr = memory.begin(); itr != memory.end(); itr++) {
	    if((*itr).getSize() >= processes[i].getSize()) {
	      addPartition(memory, itr, processes[i]);
	      printMemory(memory);
	      partitionAdded = true;
	    }
	  }
	}
	if(!partitionAdded) {
	  if(!defragmentation(memory)) {
	    //skip
	    continue;
	  }
	  addPartition(memory, memory.end(), processes[i]);
	}
      }
    }

    //loop over memory/partitions looking for processes that expire at this time
    //  if process expires
    //    set partition that process uses as free (update freeMem variable, etc.)
    //    remove process from processes list or add to count of finished processes
    break;
    time++;
  }
}

void bestFit(vector<Process> processes, int memSize) {

}

//loop over memory and check if there is space
//could also just keep running total of memory in each function, could be easier
bool isEnoughMemory() {
  return false;
}

//check if there is enough memory for process, if there is deframentate and return true, else false
bool defragmentation(list<Partition> &memory) {
  //if isEnoughMemory()
  //  defragmentate
  //  return true
  //return false
  return false;
}

int runContiguous(vector<Process> processes, int memSize) {

  //nextFit(processes, memSize);
  firstFit(processes, memSize);
  //bestFit(processes, memSize);

  return EXIT_SUCCESS;
}

