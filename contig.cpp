//Isaac Dugas dugasi
//Jeff Willoughby willoj
//Gabe Langlois langlg

#include <vector>
#include <list>
#include <iterator>
#include<iostream>

#include "functions.h"

#define T_MEMMOVE 1

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

void mergePartitions(list<Partition> &memory, list<Partition>::iterator loc) {
  int size = 0;
  list<Partition>::iterator left = loc;
  left--;
  list<Partition>::iterator right = loc;
  right++;
  
  if(loc != memory.begin() && (*left).isEmpty()) {
    size = (*left).getSize();
    (*loc).updateSize(size + (*loc).getSize());
    memory.erase(left);
  }
  if(right != memory.end() && (*right).isEmpty()) {
    size = (*right).getSize();
    (*loc).updateSize(size + (*loc).getSize());
    memory.erase(right);
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
  int defragTime = 0;
  unsigned int finished = 0;
  //while there are processes left to be processed
  while(finished < processes.size()) { // remove processes from vector or keep variable count of finished processes
    for(unsigned int i = 0; i < processes.size(); i++) {
      if(processes[i].getArrivalTime() + defragTime == time) {
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
	      break;
	    }
	  }
	  if(!partitionAdded) {
	    string movedProcesses = "";
	    cout << "time " << time << "ms: Cannot place process " << processes[i].getId() << " -- starting defragmentation" << endl;
	    int framesMoved = memSize - defragmentation(memory, freeMem, movedProcesses);
	    defragTime += framesMoved*T_MEMMOVE;
	    time += defragTime;
	    cout << "time " << time << "ms: Defragmentation complete (moved " << framesMoved << " frames:" << movedProcesses << ")" << endl;
	    cout << "time " << time << "ms: Placed process " << processes[i].getId() << ":" << endl;
	    addPartition(memory, --memory.end(), processes[i]);
	    printMemory(memory);
	  }
	}
	else {
	  //skip process
	  if(processes[i].processComplete()) {
	    finished++;
	  }
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
      if((*itr).getExpirationTime() + defragTime == time) {
	if((*(*itr).getProcess()).processComplete()) {
	  finished++;
	}
	cout << "time " << time << "ms: Process " << (*itr).getId() << " removed:" << endl;
	(*itr).emptyPartition();
	freeMem += (*itr).getSize();
	mergePartitions(memory, itr);
	//if(finished < processes.size()) {
	  printMemory(memory);
	  //}
      }
    }
    time++;
  }
  cout << "time " << time-1 << "ms: Simulator ended (Contiguous -- First-Fit)" << endl;
}

bool addToBestLocation(list<Partition> &memory, Process &process, int &freeMem, int time) {
  int minDiff = freeMem;
  list<Partition>::iterator bestLoc = memory.end();
  for(list<Partition>::iterator itr = memory.begin(); itr != memory.end(); itr++) {
    if((*itr).getSize() - process.getSize() < minDiff && (*itr).getSize() - process.getSize() >= 0 && (*itr).isEmpty()) {
      minDiff = (*itr).getSize() - process.getSize();
      bestLoc = itr;
    }
  }
  if(bestLoc == memory.end()) {
    return false;
  }
  addPartition(memory, bestLoc, process);
  cout << "time " << time << "ms: Placed process " << process.getId() << ":" << endl;
  printMemory(memory);
  freeMem -= process.getSize();
  return true; 
}

void bestFit(vector<Process> processes, int memSize) {
  list<Partition> memory;
  memory.push_back(Partition(NULL, memSize));
  int time = 0;
  cout << "time " << time << "ms: Simulator started (Contiguous -- Best-Fit)" << endl;
  int freeMem = memSize;
  int defragTime = 0;
  unsigned int finished = 0;
  //while there are processes left to be processed
  while(finished < processes.size()) { // remove processes from vector or keep variable count of finished processes
    for(unsigned int i = 0; i < processes.size(); i++) {
      if(processes[i].getArrivalTime() + defragTime == time) {
	cout << "time " << time << "ms: Process " << processes[i].getId() << " arrived (requires " << processes[i].getSize() << " frames)" << endl;
	//add process to memory if possible
	//  print memory if added
	//else if defragmentation() possible do it
	//else skip process
	bool partitionAdded = false;
	if(freeMem >= processes[i].getSize()) {
	  //findbestlocation
	  partitionAdded = addToBestLocation(memory, processes[i], freeMem, time);
	  if(!partitionAdded) {
	    string movedProcesses = "";
	    cout << "time " << time << "ms: Cannot place process " << processes[i].getId() << " -- starting defragmentation" << endl;
	    int framesMoved = memSize - defragmentation(memory, freeMem, movedProcesses);
	    defragTime += framesMoved*T_MEMMOVE;
	    time += defragTime;
	    cout << "time " << time << "ms: Defragmentation complete (moved " << framesMoved << " frames:" << movedProcesses << ")" << endl;
	    cout << "time " << time << "ms: Placed process " << processes[i].getId() << ":" << endl;
	    addPartition(memory, --memory.end(), processes[i]);
	    printMemory(memory);
	  }
	}
	else {
	  //skip process
	  if(processes[i].processComplete()) {
	    finished++;
	  }
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
      if((*itr).getExpirationTime() + defragTime == time) {
	if((*(*itr).getProcess()).processComplete()) {
	  finished++;
	}
	cout << "time " << time << "ms: Process " << (*itr).getId() << " removed:" << endl;
	(*itr).emptyPartition();
	freeMem += (*itr).getSize();
	mergePartitions(memory, itr);
	//if(finished < processes.size()) {
	  printMemory(memory);
	  //}
      }
    }
    time++;
  }
  cout << "time " << time-1 << "ms: Simulator ended (Contiguous -- Best-Fit)" << endl;
}

//defragment memory, returns number of frames moved
int defragmentation(list<Partition> &memory, int &freeMem, string &movedProcesses) {
  int open = 0;
  list<Partition>::iterator itr = memory.begin();
  bool processMoved = false;
  while(itr != memory.end()) {
    if((*itr).isEmpty()) {
      processMoved = true;
      open += (*itr).getSize();
      itr = memory.erase(itr);
    }
    else {
      if(processMoved) {
	movedProcesses += " "+ (*itr).getId();
      }
      ++itr;
    }
  }
  freeMem = open;
  memory.push_back(Partition(NULL, freeMem));
  return open;
}

int runContiguous(vector<Process> processes, int memSize) {

  //nextFit(processes, memSize);
  //firstFit(processes, memSize);
  bestFit(processes, memSize);

  return EXIT_SUCCESS;
}

