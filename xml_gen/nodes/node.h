#ifndef NODE_IMPLEMENTATION
#define NODE_IMPLEMENTATION

#include <stdlib.h>
#include <stdio.h>

typedef enum NodeType{
    NODE_PROGRAM,
    NODE_DECISION,
    NODE_PROCESS,
    NODE_SUBPROCESS,
    NODE_IO
} NodeType;

typedef struct Node{
    NodeType type;
    char *text;

    struct Node *next_child;
    struct Node *next_sibling;
}  Node;

Node creating_node(NodeType type, char[] text) {
    Node n;
    n.type = type;
    n.text = text;

    n.next_child = NULL;
    n.next_sibling = NULL;
}


void write_nodes_to_xml(Node *head, FILE *file){
    Node current = head;
    while (current->next != NULL){
        switch (head.type){
            case NODE_IO:
                break;
            case NODE_PROCESS:
                break;
            case NODE_DECISION:
                break;
            case NODE_SUBPROCESS:
                break;
        }

        current = current->next;
    }
}

#endif
