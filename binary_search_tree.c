#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    double value;
    struct node *left_child;
    struct node *right_child;
} node;

node *create_node(double value);
node *find_value(node *root, double value);
void print_tree(node *root);
void add_element(node **root_ptr, double value);
void destroy(node *root);


int main(void) {

    node *root = NULL;

    add_element(&root, 15);
    add_element(&root, 11);
    add_element(&root, 24);
    add_element(&root, 19);
    add_element(&root, 20);
    add_element(&root, 5);
    add_element(&root, 7);

    print_tree(root);
    find_value(root, 5);
    destroy(root);
    return 0;
}

node *create_node(double value) {

    node *new_node = malloc(sizeof(node));

    if (new_node != NULL) {
        new_node->left_child = NULL;
        new_node->right_child = NULL;
        new_node->value = value;
    }
    return new_node;
}

void print_tree(node *root) {

    if (root == NULL) {
        printf("<empty>\n");
        return;
    }
    printf("%f\n", root->value);
    printf("Left: \n");
    print_tree(root->left_child);
    printf("Right: \n");
    print_tree(root->right_child);
    printf("Done\n");
}

void add_element(node **root_ptr, double value) {

    node *root = *root_ptr;
    if (root == NULL) {
        (*root_ptr) = create_node(value);
        return;
    } // If there is no root - create one

    if (value == root->value) {
        printf("Value already in the tree ... ");
        return;
    } // If value already exists - do nothing

    if (value < root->value) {
        add_element(&(root->left_child), value);
    } else {
        add_element(&(root->right_child), value);
    }
}

node *find_value(node *root, double value) {

    node *temp = root;

    if (temp == NULL) {
        printf("Tree is empty ...\n");
        return NULL;
    }

    if (temp->value == value) {
        printf("Found %f at address: %p\n", value, temp);
        return temp;
    }

    if (value > temp->value) {
        return find_value(temp->right_child, value);
    } else {
        return find_value(temp->left_child, value);
    }
}

void destroy(node *root) {

    if (root == NULL) {
        return;
    }

    destroy(root->left_child);
    destroy(root->right_child);
    free(root);
}
