//Isaac Dugas dugasi
//Jeff Willoughby willoj
//Gabe Langlois langlg

#include <string>
#include "process.h"

using namespace std;

class Partition{
 public:
  Partition();
  Partition(Process* proc, int size1);

  //Accessors
  int getSize() const;
  string getId() const;
  Process* getProcess() const;
  int getExpirationTime() const;
  
  bool isEmpty();
  
  //Modifiers
  void updateSize(int size1);
  void emptyPartition();
  void assignPartition(Process* proc);
  
 private:
  int size;
  Process* process;
};
