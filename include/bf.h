#ifndef BF_H
#define BF_H

struct DataPointer {
  unsigned int value:8;
  struct DataPointer *next;
  struct DataPointer *prev;
};

struct SourceCode{
  size_t size;
  int nloops;
  char *buffer;
  char *src_file;
  struct LoopStruct *loops;
};

struct LoopStruct{
  int pos;          //Position of [ or ] in code
  int loopn;        //Number of loop
  int pos_matching; //Position of matching ] or [ in code
};


void outputValue(struct DataPointer *d);  //Prints value
struct DataPointer *initPointer(struct DataPointer *prev, struct DataPointer *next);
int freeMemory(struct DataPointer *v, struct SourceCode *src);
void readFile(struct SourceCode *src); //Stores src and returns size
int seekClose(int IP, struct SourceCode *src);
int seekOpen(int IP, struct SourceCode *src);
void mapLoops(struct SourceCode *src);

#endif
