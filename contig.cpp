#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <list>
#include "functions.h"

using namespace std;

void nextFit(vector<Process> processes) {
  
}

void firstFit(vector<Process> processes) {
  list<Partition> memory;
  int time = 0;
  //int freeMem = SIZE;
  //while there are processes left to be processed
  while(processes.size() > 0) { // remove processes from vector or keep variable count of finished processes
    for(unsigned int i = 0; i < processes.size(); i++) {
      if(processes[i].getArrivalTime() == time) {
	//add process to memory if possible
	//  print memory if added
	//else if defragmentation() possible do it
	//else skip process
      }
    }

    //loop over memory/partitions looking for processes that expire at this time
    //  if process expires
    //    set partition that process uses as free (update freeMem variable, etc.)
    //    remove process from processes list or add to count of finished processes
    time++;
  }
}

void bestFit(vector<Process> processes) {

}

//loop over memory and check if there is space
//could also just keep running total of memory in each function, could be easier
bool isEnoughMemory() {
  return false;
}

//check if there is enough memory for process, if there is deframentate and return true, else false
bool defragmentation() {
  //if isEnoughMemory()
  //  defragmentate
  //  return true
  //return false
  return false;
}

int runContiguous(vector<Process> processes) {

  nextFit(processes);
  firstFit(processes);
  bestFit(processes);

  return EXIT_SUCCESS;
}
