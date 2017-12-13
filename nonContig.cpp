//Isaac Dugas dugasi
//Jeff Willoughby willoj
//Gabe Langlois langlg

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <list>
#include <set>
#include "functions.h"
using namespace std;

void printPageTable(list<Partition> &memory){
  int pageOffset = 0;
  map<string, vector<int>> pageTable;
  for(list<Partition>::iterator itr = memory.begin(); itr != memory.end(); itr++){
    if (!(*itr).isEmpty()){
      for(int i=pageOffset; i<pageOffset+(*itr).getSize(); i++){
        pageTable[(*itr).getId()].push_back(i);
      }
    }
    pageOffset += (*itr).getSize();
  }
  cout << "PAGE TABLE [page,frame]:" << endl;
  for(map<string, vector<int> >::const_iterator it = pageTable.begin(); it != pageTable.end(); ++it){
    cout << it->first << ": ";
    for(unsigned int i=0; i<it->second.size(); i++){
      cout << "[" << i << "," << it->second[i] << "]";
      if((i+1)%10 == 0){cout << endl;}
      else if (i != it->second.size()-1){cout << " ";}
    }
    cout << endl;
  }
}

void addPartition(list<Partition> &memory, const list<Partition>::iterator &loc, Process &proc, int current_size) {
  //cout << "remaining size to place is " << current_size << endl;
  //cout << "loc size is " << (*loc).getSize() << endl;
  if((*loc).getSize() == current_size) {
    (*loc).assignPartition(&proc);
  }
  else if ((*loc).getSize() > current_size){
    int newSize = (*loc).getSize() - current_size;
    (*loc).updateSize(newSize);
    Partition newPart = Partition(&proc, current_size);
    memory.insert(loc, newPart);
  }
  else{
    (*loc).assignPartition(&proc);
    list<Partition>::iterator itr = memory.begin();
    while(itr != memory.end()) {
      if((*itr).isEmpty() && (*itr).getSize() > 0) {
        //cout << "recursing to place! size to pass along next is " << current_size-(*loc).getSize() << endl;
        addPartition(memory, itr, proc, current_size-(*loc).getSize());
        break;
      }
      itr++;
    }
  }
}

int runNonContiguous(vector<Process> processes, int size) {
  list<Partition> memory;
  unsigned int done = 0;
  memory.push_back(Partition(NULL, size));
  int time = 0;
  cout << "time " << time << "ms: Simulator started (Non-contiguous)" << endl;
  //unsigned int skipped = 0;
  //unsigned int finished = 0;
  int freeMem = size;
  //while there are processes left to be processed
  while(processes.size() != done) { // remove processes from vector or keep variable count of finished processes
    for(unsigned int i = 0; i < processes.size(); i++) {
      if(processes[i].getArrivalTime() == time) {
        cout << "time " << time << "ms: Process " << processes[i].getId() << " arrived (requires " << processes[i].getSize() << " frames)" << endl;

        //add process to memory if possible
        if(freeMem >= processes[i].getSize()) {
	  list<Partition>::iterator itr = memory.begin();
          while(itr != memory.end()) {
            if((*itr).isEmpty()) {
              addPartition(memory, itr, processes[i], processes[i].getSize());
              cout << "time " << time << "ms: Placed process " << processes[i].getId() << ":" << endl;
              printMemory(memory);
              printPageTable(memory);
              freeMem -= processes[i].getSize();
              break;
            }
            itr++;
          }
        }
        else {
          //skip process
          //skipped++;
          done++;
          cout << "time " << time << "ms: Cannot place process " << processes[i].getId() << " -- skipped!" << endl;
          printMemory(memory);
          printPageTable(memory);
          continue;
        }
      }
    }
    //loop over memory/partitions looking for processes that expire at this time
    //  if process expires
    //    set partition that process uses as free (update freeMem variable, etc.)
    //    remove process from processes list or add to count of finished processes
    //set<string> ended;
    //set<string>::iterator it;
    list<Partition>::iterator itr2;
    for(list<Partition>::iterator itr = memory.begin(); itr != memory.end(); itr++) {
      if((*itr).getExpirationTime() == time) {
        cout << "time " << time << "ms: Process " << (*itr).getId() << " removed:" << endl;
        //printMemory(memory);
        //ended.insert(it, (*itr).getId());
        itr2 = itr;
        //cout << "pre scan" << endl;
        if (itr2 != memory.end()){itr2++;}
        while(itr2 != memory.end()){
          if ((*itr2).getId() == (*itr).getId()){
            //cout << "needed the scan" << endl;
            (*itr2).emptyPartition();
            freeMem += (*itr2).getSize();
            mergePartitions(memory, itr2);
            //cout << "scanning..." << endl;
          }
          itr2++;
        }
        if((*(*itr).getProcess()).processComplete()){
          //finished++;
          done++;
        }
        (*itr).emptyPartition();
        freeMem += (*itr).getSize();
        mergePartitions(memory, itr);
        printMemory(memory);
        printPageTable(memory);
      }
    }
    time++;
  }
  cout << "time " << time-1 << "ms: Simulator ended (Non-contiguous)"<< endl;
  return EXIT_SUCCESS;
}
