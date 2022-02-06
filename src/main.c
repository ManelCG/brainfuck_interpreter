#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bf.h>

#define DEBUG
// #define SHOW_VALUES
// #define READ_INSTRUCTIONS

int main(int argc, char *argv[]){
  //Initialize data Pointer
  struct DataPointer *array_head = initPointer(NULL, NULL), *ptr = array_head;

  //Prepare to read source from .bf file
  struct SourceCode *src = malloc(sizeof(struct SourceCode));
  src->src_file = malloc(255);
  src->nloops = 0;

  if (argc < 2){
    strcpy(src->src_file, "bf_src/helloworld.bf");
    printf("Reading %s by default...\n", src->src_file);
  } else {
    strcpy(src->src_file, argv[1]);
    printf("Reading %s...\n", src->src_file);
  }

  //Read file into src buffer
  readFile(src);

  //Map the loops in source for better execution time
  mapLoops(src);

  #ifdef DEBUG
    printf("Reading following brainfuck source code:\n\n");
    for (int i = 0; i < src->size; i++){
      printf("%c", *(src->buffer + i));
    }
    printf("\nNumber of loops: %d\n", src->nloops);
    printf("\n\nExecution Output:\n");
  #endif


  //Execute program
  int IP = 0;
  char current_instruction;
  while (IP != src->size + 1){
    current_instruction = *(src->buffer + IP);

    #ifdef READ_INSTRUCTIONS
      printf("Currently reading instruction: %c\n", current_instruction);
    #endif

    switch(current_instruction){
      case '>':
        if (ptr->next == NULL) {
          ptr->next = initPointer(ptr, NULL);
        }
        ptr = ptr->next;
        IP ++;
        break;

      case '<':
        ptr = ptr->prev;
        IP++;
        break;

      case '+':
        ptr->value ++;
        IP++;
        break;

      case '-':
        ptr->value --;
        IP++;
        break;

      case'.':
        outputValue(ptr);
        IP++;
        break;

      case '[':
        if (ptr->value == 0){
          IP = seekClose(IP, src);
        } else {
          IP ++;
        }
        break;

      case ']':
        if (ptr->value != 0){
          IP = seekOpen(IP, src);
        } else {
          IP ++;
        }
        break;

      case ',':
        char c;
        fread(&c, 1, 1, stdin);
        ptr->value = (int) c;
        IP++;
        break;


      case ' ':
      case '\n':
      case '\0':
        IP++;
        break;

      default:
        printf("Undefined command: %c\n", current_instruction);
        IP++;
        break;
    }

    #ifdef SHOW_VALUES
      if (current_instruction != ' ' && current_instruction != '\n' && current_instruction != '\0'){
        struct DataPointer *aux = array_head;
        while (aux != NULL){
          if (aux == ptr){
            printf("[");
          } else {
            printf(" ");
          }
          printf("%d", aux->value);
          if (aux == ptr){
            printf("]");
          } else {
            printf(" ");
          }
          aux = aux->next;
        }
        printf("\t\t%c\n", current_instruction);
      }

    #endif

  }


  freeMemory(array_head, src);
}
