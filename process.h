#include <string>
#include <list>
using namespace std;

class Process{
 public:
  Process();
  Process(string id1, int size1, list<int> arrivalTimes1, list<int> runTimes1);

  //Accessors
  string getId() const;
  int getSize() const;
  int getArrivalTime() const;
  int getRunTime() const;
  int getRemainingBurstTime() const;
  
  //Modifiers
  void setRemainingBurstTime(int b);
  bool processComplete();

 private:
  string id;
  int size;
  list<int> arrivalTimes;
  list<int> runTimes;
  int remainingBurstTime;
};
