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

int is_valid(Node * n){
   int i, j, k, l;

   for (i = 0; i < 9; i++) {
       int row_marks[10] = {0};
       for (j = 0; j < 9; j++) {
           if (n->sudo[i][j] != 0 && row_marks[n->sudo[i][j]] == 1) {
               return 0;
           }
           row_marks[n->sudo[i][j]] = 1;
       }
   }

   for (j = 0; j < 9; j++) {
       int col_marks[10] = {0};
       for (i = 0; i < 9; i++) {
           if (n->sudo[i][j] != 0 && col_marks[n->sudo[i][j]] == 1) {
               return 0;
           }
           col_marks[n->sudo[i][j]] = 1;
       }
   }

   for (k = 0; k < 3; k++) {
       for (l = 0; l < 3; l++) {
           int sub_marks[10] = {0};
           for (i = 3*k; i < 3*k+3; i++) {
               for (j = 3*l; j < 3*l+3; j++) {
                   if (n->sudo[i][j] != 0 && sub_marks[n->sudo[i][j]] == 1) {
                       return 0;
                   }
                   sub_marks[n->sudo[i][j]] = 1;
               }
           }
       }
   }

   return 1;
}


List* get_adj_nodes(Node* n){
   List* list=createList();
   int i, j;
   for (i = 0; i < 9; i++) {
       for (j = 0; j < 9; j++) {
           if (n->sudo[i][j] == 0) {
               int k;
               for (k = 1; k <= 9; k++) {
                   Node* new_node = copy(n);
                   new_node->sudo[i][j] = k;
                   if(is_valid(new_node)){
                       pushBack(list, new_node);
                   }
               }
               return list;
           }
       }
   }
   return list;
}


int is_final(Node* n){
  int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if(n->sudo[i][j]==0){
                return 0;
            }
        }
    }
    return 1;
}


Node* DFS(Node* n, int* cont) {
    List* S = createList();
    pushBack(S, n);
    
    while (!is_empty(S)) {
        Node* node = (Node*) popBack(S);
        if (isFinal(node)) {
            freeList(S);
            return node;
        }
        
        List* adjList = getAdjacents(node);
        for (Node* node = pop(S); front(adjList); adjNode != NULL; adjNode = (Node*) next(adjList)) {
            pushBack(S, adjNode);
        }
        
        freeNode(node);
        freeList(adjList);
    }
    
    freeList(S);
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