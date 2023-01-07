#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    void *next;
} Node;

void printfMenu();
void pushNode(Node **head, int new_data);
int insertNode(Node **head, int new_data, int index);
void appendNode(Node **head, int new_data);
int removeNode(Node **head, int data);
void errorHandler(int error);
void printfList(Node *head);
void freeList(Node *head);

int main() {
    int option = -1, data, position;
    int scanf_return, insert_return, remove_return;
    Node *head = NULL;

    while (option != 6) {
        printfMenu();

        scanf_return = scanf("%d", &option);

        if (scanf_return == 1 && option > 0 && option <= 6) {
            switch (option) {
                case 1:
                    puts("Enter a number to be pushed:");
                    scanf_return = scanf("%d", &data);
                    if (!scanf_return)
                        errorHandler(2);
                    
                    pushNode(&head, data);
                    break;
                case 2:
                    puts("Enter a number to be inserted: ");
                    scanf_return = scanf("%d", &data);
                    if (!scanf_return)
                        errorHandler(2);

                    puts("At what position would you like to insert it?");
                    scanf_return = scanf("%d", &position);
                    if (!scanf_return)
                        errorHandler(2);

                    insert_return = insertNode(&head, data, position);
                    if (!insert_return)
                        puts("\nPosition out of bounds\n");

                    break;
                case 3:
                    puts("What number would you like to append?");
                    scanf_return = scanf("%d", &data);
                    if (!scanf_return)
                        errorHandler(2);
                    
                    appendNode(&head, data);

                    break;
                case 4:
                    puts("What number would you like to remove?");
                    scanf_return = scanf("%d", &data);
                    if (!scanf_return)
                        errorHandler(2);
                    
                    remove_return = removeNode(&head, data);
                    if (!remove_return)
                        puts("\nData not found\n");

                    break;
                case 5:
                    printfList(head);
                    
                    break;
                case 6:
                    break;
            }
        }
    }
    freeList(head);

    return 0;
}

void printfMenu() {
    puts("Select an option:\n");
    puts("\t1- Push into the list.");
    puts("\t2- Insert at a desired position");
    puts("\t3- Append into the list.");
    puts("\t4- Remove from the list.");
    puts("\t5- Print the list.");
    puts("\t6- Quit");
}

void pushNode(Node **head, int new_data) {
    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL)
        errorHandler(1);

    new->data = new_data;
    new->next = *head;
    *head = new;
}

int insertNode(Node **head, int new_data, int index) {
    int i = 0;
    Node *current = *head;

    while (current->next != NULL && ++i < index)
        current = current->next;

    if (i != index) {
        return 0;
    }

    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL)
        errorHandler(1);

    new->data = new_data;
    new->next = current->next;
    current->next = new;

    return 1;
}

void appendNode(Node **head, int new_data) {
    Node *new = (Node *) malloc(sizeof(Node));
    if (new == NULL)
        errorHandler(1);

    new->data = new_data;
    new->next = NULL;

    if (*head == NULL) {
        *head = new;
        return;
    }

    Node *last = *head;

    while (last->next != NULL)
        last = last->next;
    
    last->next = new;
}

int removeNode(Node **head, int data) {
    Node *current = *head;
    Node *previous = *head;

    while (current != NULL) {
        if (current->data == data) {
            if (current == *head)
                *head = current->next;
            else
                previous->next = current->next;
            free(current);

            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

void errorHandler(int error) {
    switch (error) {
        case 1:
            fprintf(stderr, "\n\nUnable to allocate memory!!\n");
            exit(error);
            break;
        case 2:
            fprintf(stderr, "\n\nUnable to read from stdin!!\n");
            exit(error);
            break;
    }
}

void printfList(Node *head) {
    putchar('\n');
    puts("--------------------------------------------------------------------------------------------------");
    while (head->next != NULL) {
        printf(" %d ->", head->data);
        head = head->next;
    }
    if (head != NULL) printf(" %d\n", head->data);
    puts("--------------------------------------------------------------------------------------------------");
}

void freeList(Node *head) {
    Node *current = head;

    while (head->next != NULL) {
        head = head->next;
        free(current);
        current = head;
    }
}