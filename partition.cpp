//Isaac Dugas dugasi
//Jeff Willoughby willoj
//Gabe Langlois langlg

#include "partition.h"

Partition::Partition() {
  process = NULL;
  size = 0;
}

Partition::Partition(Process* proc, int size1) {
  process = proc;
  size = size1;
}

string Partition::getId() const {
  if(process == NULL) {
    return ".";
  }
  return (*process).getId();
}

int Partition::getSize() const {
  return size;
}

int Partition::getExpirationTime() const {
  if(process == NULL) {
    return -1;
  }
  return (*process).getArrivalTime() + (*process).getRunTime();
}

Process* Partition::getProcess() const {
  return process;
}

void Partition::updateSize(int size1) {
  size = size1;
}

void Partition::emptyPartition() {
  process = NULL;
}

void Partition::assignPartition(Process* proc) {
  process = proc;
}

bool Partition::isEmpty() {
  return process == NULL;
}
