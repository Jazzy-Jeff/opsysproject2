#include <vector>
#include <list>
#include <iterator>
#include<iostream>

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
  list<Partition> memory;
  memory.push_back(Partition(NULL, memSize));
  int time = 0;
  cout << "time " << time << "ms: Simulator started (Contiguous -- First-Fit)" << endl;
  int freeMem = memSize;
  unsigned int skipped = 0;
  unsigned int finished = 0;
  //while there are processes left to be processed
  while(finished + skipped < processes.size()) { // remove processes from vector or keep variable count of finished processes
    for(unsigned int i = 0; i < processes.size(); i++) {
      if(processes[i].getArrivalTime() == time) {
	cout << "time " << time << "ms: Process " << processes[i].getId() << " arrived (requires " << processes[i].getSize() << " frames)" << endl;
	//add process to memory if possible
	//  print memory if added
	//else if defragmentation() possible do it
	//else skip process
	bool partitionAdded = false;
	if(freeMem >= processes[i].getSize()) {
	  for(list<Partition>::iterator itr = memory.begin(); itr != memory.end(); itr++) {
	    if((*itr).getSize() >= processes[i].getSize() && (*itr).isEmpty()) {
	      addPartition(memory, itr, processes[i]);
	      cout << "time " << time << "ms: Placed process " << processes[i].getId() << ":" << endl;
	      printMemory(memory);
	      freeMem -= processes[i].getSize();
	      partitionAdded = true;
	    }
	  }
	  if(!partitionAdded) {
	    defragmentation(memory, freeMem);
	    addPartition(memory, memory.end(), processes[i]);
	  }
	}
	else {
	  //skip process
	  skipped++;
	  cout << "time " << time << "ms: Cannot place process " << processes[i].getId() << " -- skipped!" << endl;
	  continue;
	}
      }
    }

    //loop over memory/partitions looking for processes that expire at this time
    //  if process expires
    //    set partition that process uses as free (update freeMem variable, etc.)
    //    remove process from processes list or add to count of finished processes
    for(list<Partition>::iterator itr = memory.begin(); itr != memory.end(); itr++) {
      if((*itr).getExpirationTime() == time) {
	if((*(*itr).getProcess()).processComplete()) {
	  finished++;
	}
	cout << "time " << time << "ms: Process " << (*itr).getId() << " removed:" << endl;
	(*itr).emptyPartition();
	freeMem += (*itr).getSize();
	printMemory(memory);
      }
    }
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

//deframent memory
void defragmentation(list<Partition> &memory, int &freeMem) {
  for(list<Partition>::iterator itr = memory.begin(); itr != memory.end(); itr++) {
    if((*itr).isEmpty()) {
      freeMem += (*itr).getSize();
      memory.erase(itr);
    }
  }
  memory.push_back(Partition(NULL, freeMem));
}

int runContiguous(vector<Process> processes, int memSize) {

  //nextFit(processes, memSize);
  firstFit(processes, memSize);
  //bestFit(processes, memSize);

  return EXIT_SUCCESS;
}

