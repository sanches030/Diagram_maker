#ifndef HIERARCHY_LIB
#define HIERARCHY_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lang_syntax/lang.h"

typedef enum Type{
    PROGRAM,
    IO,
    PROCESS,
    DECISION
} Type;

typedef struct Node{
    const char* text;
    Type type;

    struct Node *child;
    struct Node *sibling;

} Node;


Node *create_node(const char *text, Type type){
    Node *next = malloc(sizeof(Node));
    if (next == NULL)
        return NULL;

    next->type = type;
    next->text = strdup(text);

    if (next->text == NULL){
        free(next);
        return NULL;
    }
    
    next->child = NULL;
    next->sibling = NULL;

    return next;
}

void add_child(Node* parent, Node* child){
    if (parent->child == NULL){
        parent->child = child;
        return;
    }

    Node *current = parent->child;
    while (current->sibling != NULL)
        current = current->sibling;
    current->sibling = child;
}

Type recognizer(const char* data){
    const char *data_types[] = {
        "int",
        "char",
        "bool",
        "double",
        "float",
        "long double",
        "long long"
    };

    if (strstr(data, "int main(") != NULL){
        return PROGRAM;    
    }

    for (int i = 0; i < 7; ++i){
        if (strstr(data, (const char *)data_types[i]) != NULL){
            return PROCESS;
        }
    }
}

Node *reading(FILE *source){
    Node *head = create_node("program", PROGRAM);
    if (source == NULL || head == NULL)
        return NULL;

    Node *stack[256];
    unsigned int top = 0;
    stack[top++] = head;

    char data[2048];

    while (fgets(data, sizeof(data), source) != NULL){
        if (strstr(data, "int") != NULL){
            Node *n = create_node(data, PROCESS);
            if (n == NULL)
                return NULL;
            add_child(stack[top - 1], n);
        }
        else if (strstr(data, "if") != NULL){
            Node *n = create_node(data, DECISION);
            if (n == NULL)
                return NULL;
            add_child(stack[top - 1], n);
            stack[top++] = n;
        } 
        else if (strstr(data, "}") != NULL){
            --top;
        }
    }
    return head;
}

void write_nodes(Node *node, FILE *result, int depth) {
    while (node != NULL) {
        const char *tag;

        switch (node->type) {
            case PROGRAM:  tag = "program";  break;
            case IO:       tag = "io";       break;
            case PROCESS:  tag = "process";  break;
            case DECISION: tag = "decision"; break;
            default:
                node = node->sibling;
                continue;
        }

        for (int i = 0; i < depth; ++i)
            fprintf(result, "    ");

        fprintf(result, "<%s>", tag);
        fprintf(result, "%s", node->text);

        write_nodes(node->child, result, depth + 1);

        for (int i = 0; i < depth; ++i)
            fprintf(result, "    ");

        fprintf(result, "</%s>\n", tag);

        node = node->sibling;
    }
}
#endif 
