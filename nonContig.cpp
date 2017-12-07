#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <list>
#include "functions.h"

using namespace std;

int runNonContiguous(vector<Process> processes, int size) {
  list<Partition> memory;
  int time = 0;
  //int freeMem = SIZE;
  //while there are processes left to be processed
  while(processes.size() > 0) { // remove processes from vector or keep variable count of finished processes
    for(unsigned int i = 0; i < processes.size(); i++) {
      if(processes[i].getArrivalTime() == time) {
        //add process to memory if possible
        if (processes[i].getSize() <= size){
	  cout << "There is enough memory to add process " << processes[i].getId() << endl;
        }
        //  print memory if added
        //else skip process
	cout << "this motha fucka arrived " + processes[i].getId() << " at time " << time << endl;
      }
    }

    //loop over memory/partitions looking for processes that expire at this time
    //  if process expires
    //    set partition that process uses as free (update freeMem variable, etc.)
    //    remove process from processes list or add to count of finished processes
    time++;
  }
  return EXIT_SUCCESS;
}
