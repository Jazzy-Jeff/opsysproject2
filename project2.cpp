#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>

#include <list>

#include "functions.h"

#define F 3
#define SIZE 256
#define LINE 32

using namespace std;

void printMemory(const list<Partition> &memory) {
  int count = 0;
  string id;
  for(int i = 0; i < LINE; i++) { cout << "=";}
  cout << endl;
  for(list<Partition>::const_iterator itr = memory.begin(); itr != memory.end(); itr++) {
    for(int i = 0; i < (*itr).getSize(); i++) {
      cout << (*itr).getId();
      count++;
      if(count == LINE) {
	cout << endl;
	count = 0;
      }
    }
  }
  for(int i = 0; i < LINE; i++) { cout << "=";}
  cout << endl;
}

void parseInput(string filename, vector<Process> &processes) {
  ifstream input(filename.c_str());
  string line;
  while(getline(input, line)) {
    if(line[0] == '#') {
      continue;
    }
    string id = line.substr(0, 1);
    size_t start = line.find(" ") + 1;
    size_t end = line.find(" ", start + 1) - start;
    int size = stoi(line.substr(start, end));

    list<int> arrivalTimes;
    list<int> runTimes;
    while((start = line.find(" ", start + end)) != string::npos) {
      start++;
      size_t middle = line.find("/", start) - start;
      if((end = line.find(" ", start + 1)) == string::npos) {
	end = line.length();
      }
      end -= start;
      int arrival = stoi(line.substr(start, middle));
      arrivalTimes.push_back(arrival);
      int runTime = stoi(line.substr(middle+start+1, end-middle));
      runTimes.push_back(runTime);
    }
    processes.push_back(Process(id, size, arrivalTimes, runTimes));
  }
}

int main (int argc, char* argv[]) {
  string filename = argv[1];
  vector<Process> processes;
  
  parseInput(filename, processes);

  for(unsigned int i = 0; i < processes.size(); i++) {
    cout << "id = " << processes[i].getId() <<endl;
    cout << "size = " << processes[i].getSize() <<endl;
    cout << "arrival = " << processes[i].getArrivalTime() <<endl;
    cout << "runTime = " << processes[i].getRunTime() <<endl;
    cout << endl;
  }
  runContiguous(processes, SIZE);
  
  return EXIT_SUCCESS;
}

