#include <stdio.h>
#include <stdlib.h>

struct node {
    double value;
    struct node* next;
}; // structure of list's node
typedef struct node node_t;

void print_list(node_t *head);
void add_node(double value, node_t **head);
void insert_node(double value, node_t **head);
void delete_node(double value, node_t **head);
void destroy(node_t *head);
node_t *copy_list(node_t *head);
node_t *find_element(double value, node_t *head);


int main() {

    node_t *sl_list;
    sl_list = NULL;

    add_node(3, &sl_list);
    add_node(5, &sl_list);
    add_node(10, &sl_list);
    add_node(13, &sl_list);
    insert_node(100, &sl_list);
    insert_node(20, &sl_list);
    delete_node(10, &sl_list);

    printf("List 1:\n");
    print_list(sl_list);
    node_t *new = copy_list(sl_list);
    add_node(26, &sl_list);
    printf("List 2:\n");
    print_list(new);
    find_element(10, new);
    printf("List 1 updated:\n");
    print_list(sl_list);
    insert_node(25, &sl_list);
    printf("List 1 updated:\n");
    print_list(sl_list);
    find_element(25, sl_list);
    destroy(sl_list);
    destroy(new);
    return 0;
}

void add_node(double value, node_t **head) {

    node_t *new, *current = *head;
    new = malloc(sizeof(node_t));
    new->value = value;
    new->next = NULL;

    if (current == NULL) {
        *head = new;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
} // Adds node at the end of the list

void insert_node(double value, node_t **head) {

    node_t *new  = malloc(sizeof(node_t));
    new->value = value;
    new->next = *head;

    *head = new;
} // Adds node at the beginning of the list

void print_list(node_t *head) {

    node_t *temp = head;

    printf("start -> ");
    while (temp != NULL) {
        printf("%f -> ",temp->value);
        temp = temp->next;
    }
    printf("end\n");
} // Prints out all elements from the list in order

node_t *find_element(double value, node_t *head) {

    node_t *temp = head;
    size_t index = 0;

    while (temp != NULL) {
        if (temp->value == value) {
            printf("Found %f at index %zu\n", value, index);
            return temp;
        } else {
            temp = temp->next;
            index += 1;
        }
    }
    printf("Found nothing ...\n");
    return NULL;
} // Returns memory address of the given value, if not in list returns 0

void delete_node(double value, node_t **head) {

    node_t *temp = *head, *before;

    if(*head == NULL) {
        printf("Nothing to delete ... ");
        return;
    }

    while (temp != NULL) {
        if (temp->value == value) {
            before->next = temp->next;
            free(temp);
            return;
        } else {
            before = temp;
            temp = temp->next;
        }
    }
} // Deletes node which contains given value

void destroy(node_t *head) {

    node_t *temp = head, *before;

    while (temp != NULL) {
        before = temp;
        temp = temp->next;
        free(before);
    }
    free(temp);
} // Deletes all the nodes of the given list

node_t *copy_list(node_t *head) {

    node_t *new_head = NULL, *temp = head, *new_node, *previous;

    while (temp != NULL) {
        new_node = malloc(sizeof(node_t));
        new_node->value = temp->value;
        if (new_head == NULL) {
            new_head = new_node;
            previous = new_head;
        } else {
            previous->next = new_node;
            previous = previous->next;
        }
        temp = temp->next;
    }
    if (new_head != NULL) {
        new_node->next = NULL;
    }
    return new_head;
} // Copies entire linked list starting at head and returns pointer to a new head
