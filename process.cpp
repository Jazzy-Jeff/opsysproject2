#include "process.h"

Process::Process() {
  id = "";
  size = 0;
  list<int> arrivalTimes;
  list<int> runTimes;
  remainingBurstTime = 0;
}

Process::Process(string id1, int size1, list<int> arrivalTimes1, list<int> runTimes1){
  id = id1;
  size = size1;
  arrivalTimes = arrivalTimes1;
  runTimes = runTimes1;
  remainingBurstTime = runTimes1.front();
}

string Process::getId() const{
  return id;
}

int Process::getSize() const {
  return size;
}

//Return front of list which is current time. If its empty we have an error somewhere else
int Process::getArrivalTime() const{
  if(arrivalTimes.empty()) {
    return -1;
  }
  return arrivalTimes.front();
}

//Return front of list which is current time. If its empty we have an error somewhere else
int Process::getRunTime() const{
  if(runTimes.empty()) {
    return -1;
  }
  return runTimes.front();
}

int Process::getRemainingBurstTime() const{
  return remainingBurstTime;
}

//returns true is there are no more arrival times and run times for this process, else false
bool Process::processComplete() {
  arrivalTimes.pop_front();
  runTimes.pop_front();
  if(arrivalTimes.empty() && runTimes.empty()) {
    return true;
  }
  return false;
}
