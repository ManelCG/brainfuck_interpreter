#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bf.h>

// #define DEBUG
// #define SHOW_VALUES
// #define READ_INSTRUCTIONS

void mapLoops(struct SourceCode *src){
  src->loops = malloc(sizeof(struct LoopStruct) * src->size);
  char c;

  int *aux_pos = malloc(sizeof(int) * src->nloops);
  int *aux_num = malloc(sizeof(int) * src->nloops);
  int aux_ptr = -1;
  int loop_o = 0;

  #ifdef DEBUG
    printf("Program has %d loops\n", src->nloops);
  #endif

  for (int i = 0; i < src->size; i++){
    c = *(src->buffer + i);

    if (c == '['){
      aux_ptr ++;
      *(aux_pos + loop_o) = i;        //Store position of loop in aux
      *(aux_num + aux_ptr) = loop_o;   //Store loop number

      //Save loop data in struct
      (src->loops + i)->pos = i;
      (src->loops + i)->loopn = loop_o;

      loop_o++;             //Count one more loop



    } else if (c == ']'){

      (src->loops + i)->pos = i;
      (src->loops + i)->loopn = *(aux_num + aux_ptr);


      //Search matching opening bracket
      (src->loops +i)->pos_matching = *(aux_pos + *(aux_num + aux_ptr));
      (src->loops + ((src->loops + i)->pos_matching))->pos_matching = i;

      aux_ptr --;

    }

  }

  free(aux_pos);
  free(aux_num);


  #ifdef DEBUG
  for (int i = 0; i < src->size; i++){
    if (*(src->buffer + i) == '['){
      printf("Open  loop pos %d\t\tLoop #%d\t\tClose loop pos %d\n", (src->loops + i)->pos, (src->loops+i)->loopn, (src->loops+i)->pos_matching);
    }
    if (*(src->buffer + i) == ']'){
      printf("Close loop pos %d\t\tLoop #%d\t\tOpen  loop pos %d\n", (src->loops + i)->pos, (src->loops+i)->loopn, (src->loops+i)->pos_matching);

    }
  }
  #endif

}


int seekClose(int IP, struct SourceCode *src){
  return (src->loops + IP)->pos_matching;
}

int seekOpen(int IP, struct SourceCode *src){
  return (src->loops + IP)->pos_matching;
}

void outputValue(struct DataPointer *d){
  putc(d->value, stdout);
}

struct DataPointer *initPointer(struct DataPointer *prev, struct DataPointer *next){
  struct DataPointer *v = malloc(sizeof(struct DataPointer));
  v->value = 0;
  v-> next = next;
  v->prev = prev;

  return v;
}

int freeMemory(struct DataPointer *v, struct SourceCode *src){
  struct DataPointer *aux;
  while (v != NULL){
    aux = v->next;
    free(v);
    v = aux;
  }

  free(src->buffer);
  free(src->src_file);
  free(src->loops);

  free(src);
}

void readFile(struct SourceCode *src){
  char c;
  FILE *file = fopen(src->src_file, "r");
  int ptr = 0;

  //Get size of file
  fseek(file, 0, SEEK_END);
  src->size = ftell(file);
  rewind(file);

  src->buffer = malloc(src->size);

  //Read file into buffer
  while (ptr != src->size) {
    *(src->buffer + ptr) = (char) fgetc(file);
    if (*(src->buffer +ptr) == '['){
      src->nloops ++;
    }
    ptr ++;
  }

  fclose(file);
}
