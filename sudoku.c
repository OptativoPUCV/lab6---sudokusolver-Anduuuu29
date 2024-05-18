#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
   //validar filas
   for(int i = 0; i < 9; i++){
      int aux[10] = {0};
      for(int j=0; j < 9; j++){
         int num = n->sudo[i][j];
         if(num != 0){
            if(aux[num])
            {
               return 0;
            }
            aux[num] = 1;
         }
      }
   }
   //validar columnas
   for(int i = 0; i < 9; i++){
      int aux[10] = {0};
      for(int j=0; j < 9; j++){
         int num = n->sudo[j][i];
         if(num != 0){
            if(aux[num])
            {
               return 0;
            }
            aux[num] = 1;
         }
      }
   }
   //validar submatrices
   for(int i = 0; i < 9; i+=3){
      for(int j = 0; j < 9; j+=3){
         int aux[10] = {0};
         for(int k = 0; k < 3; k++){
            for(int l = 0; l < 3; l++){
               int num = n->sudo[i+k][j+l];
               if(num != 0){
                  if(aux[num])
                  {
                     return 0;
                  }
                  aux[num] = 1;
               }
            }
         }
      }
   }
    return 1;
}


List* get_adj_nodes(Node* n){
   List* list_adj=createList();
   int i,j; char new_move;
   for(i=0;i<9;i++)
      for(j=0;j<9;j++){
         if(n->sudo[i][j]==0){
            for(new_move=1;new_move<10;new_move++){
               Node* new_node=copy(n);
               new_node->sudo[i][j]=new_move;
               if(is_valid(new_node)){
                  pushBack(list_adj,new_node);
               }
            }
         }
      }
   return list_adj;
}


int is_final(Node* n){
   for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
         if(n->sudo[i][j]==0){
            return 0;
         }
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* S=createStack();
   push(S,initial);
   while(get_size(S)!=0){
      Node* n=top(S);
      pop(S);
      if(is_final(n)){
         return n;
      }
      List* list_adj=get_adj_nodes(n);
      Node* aux=first(list_adj);
      while(aux)
         {
            push(S,aux);
            aux=next(list_adj);
         }
      free(n);
   }
   
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/