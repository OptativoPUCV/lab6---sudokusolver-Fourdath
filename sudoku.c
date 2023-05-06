


Node* DFS(Node* n, int* cont) {
    Stack* S = createStack(); 
    push(S, n);

    while (!isEmptyStack(S)) {
        Node* current_node = top(S);
        pop(S);

        if (is_final(current_node)) { 
            return current_node;
        }

        List* adj_nodes = get_adj_nodes(current_node); 

        Node* adj_node;
        for (adj_node = first(adj_nodes); adj_node != NULL; adj_node =next(adj_nodes)) {       
            push(S, adj_node);
        }

        free(adj_nodes); 
        (*cont)++; /
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