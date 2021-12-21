#include <stdio.h>
#include <stdlib.h>

struct node {
    double value;
    struct node *next;
    struct node *previous;
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

    node_t *dl_list;
    dl_list = NULL;

    add_node(3, &dl_list);
    add_node(5, &dl_list);
    add_node(10, &dl_list);
    add_node(13, &dl_list);
    insert_node(25, &dl_list);
    insert_node(40, &dl_list);

    delete_node(13, &dl_list);
    print_list(dl_list);
    insert_node(100, &dl_list);
    insert_node(20, &dl_list);
    delete_node(10, &dl_list);

    printf("List 1:\n");
    print_list(dl_list);
    node_t *new = copy_list(dl_list);
    add_node(26, &dl_list);
    printf("List 2:\n");
    print_list(new);
    find_element(10, new);
    printf("List 1 updated:\n");
    print_list(dl_list);
    insert_node(25, &dl_list);
    printf("List 1 updated:\n");
    print_list(dl_list);
    find_element(25, dl_list);
    destroy(dl_list);
    destroy(new);
    return 0;
}

void add_node(double value, node_t **head) {

    node_t *new, *current = *head;
    new = malloc(sizeof(node_t));
    new->value = value;
    new->next = NULL;
    new->previous = NULL;

    if (current == NULL) {
        *head = new;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
        current->next->previous = current;
    }
} // Adds node at the end of the list

void insert_node(double value, node_t **head) {

    node_t *new  = malloc(sizeof(node_t));
    new->value = value;
    new->next = (*head);
    new->previous = NULL;
    (*head)->previous = new;
    *head = new;
} // Adds node at the beginning of the list

void print_list(node_t *head) {

    node_t *temp = head;

    //printf("start -> ");
    while (temp != NULL) {
        printf("%f (next: %p, current: %p, previous: %p) -> \n",temp->value, temp->next, temp, temp->previous);
        temp = temp->next;
    }
    //printf("end\n");
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

    node_t *temp = *head;

    if(*head == NULL) {
        printf("Nothing to delete ... ");
        return;
    }

    while (temp != NULL) {
        if (temp->value == value) {
            temp->previous->next = temp->next;
            free(temp);
            return;
        } else {
            temp = temp->next;
        }
    }
} // Deletes node which contains given value

void destroy(node_t *head) {

    node_t *temp = head;

    while (temp != NULL) {
        free(temp->previous);
        temp = temp->next;
    }
    free(temp);
} // Deletes all the nodes of the given list

node_t *copy_list(node_t *head) {

    node_t *new_head = NULL, *temp = head, *new_node, *previous;

    while (temp != NULL) {
        new_node = malloc(sizeof(node_t));
        new_node->value = temp->value;
        new_node->previous = NULL;

        if (new_head == NULL) {
            new_head = new_node;
        } else {
            new_node->previous = previous;
            new_node->previous->next = new_node;
            (*new_node).next = new_node;
        }
        previous = temp;
        temp = temp->next;
    }
    if (new_head != NULL) {
        new_node->next = NULL;
    }
    return new_head;
} // Copies entire linked list starting at head and returns pointer to a new head
