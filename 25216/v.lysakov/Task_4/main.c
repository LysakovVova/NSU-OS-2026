#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN (2048)

typedef struct node {
    char* str;
    struct node *next;
} node_t;

typedef struct list {
    node_t *head;
    node_t *tail;
} list_t;

void init_list(list_t *list) {
    list->head = NULL;
    list->tail = NULL;
}

void add_list(list_t *list, const char *str) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(str);

    new_node->str = malloc(len + 1);
    if (new_node->str == NULL) {
        perror("malloc");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->str, str);
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

int main() {
    char buffer[MAX_STR_LEN];
    list_t list;
    init_list(&list);

    while (fgets(buffer, MAX_STR_LEN, stdin) != NULL) {

        if (buffer[0] == '.') {
            break;
        }

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; 
        }
        add_list(&list, buffer);
    }
    
    node_t *current = list.head;
    node_t *temp = NULL;

    while (current != NULL) {
        printf("%s\n", current->str);
        free(current->str);

        temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}