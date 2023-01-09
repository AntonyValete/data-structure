#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_VALUE 4
#define MAX_BUFFER 30

typedef struct {
    int *array;
    int size;
    int max_size;
} vector;

void printMenu();
int readElement();
void printVector(vector *arr);
void mallocErr(int *array);
void initVector(vector *arr);
void insertElement(vector *arr, int e);
int findElement(int *array, int size, int e);
void removeElement(vector *arr, int e);

int main() {
    int option = -1;
    int e, scanf_return;
    vector dynamic_arr;
    
    initVector(&dynamic_arr);

    while (option != 4) {
        printMenu();

        scanf_return = scanf("%d", &option); getchar();

        if (scanf_return == 1 && option > 0 && option <= 4) {
            switch(option) {
                case 1:
                    e = readElement();
                    if (e == 0)
                        continue;
                    insertElement(&dynamic_arr, e);

                    break;
                case 2:
                    e = readElement();
                    if (e == 0)
                        continue;
                    removeElement(&dynamic_arr, e);

                    break;
                case 3: printVector(&dynamic_arr); break;
                case 4: break;
            }
        }
    }
    free(dynamic_arr.array);

    return 0;
}

void printMenu() {
    puts("Select an option:");
    puts("Elements must be different of zero.\n");
    puts("\t1- Insert an element to the vector.");
    puts("\t2- Remove an element of the the vector.");
    puts("\t3- Print the vector.");
    puts("\t4- Quit");
}

int readElement() {
    char buffer[MAX_BUFFER];

    char *fgets_return = fgets(buffer, MAX_BUFFER, stdin);
    if (fgets_return == NULL) {
        fprintf(stderr, "Failed to read from stdin");
        exit(2);
    }
    buffer[strlen(buffer) - 1] = '\0';

    int e = (int) strtoll(buffer, NULL, 10);

    return e;
}

void printVector(vector *arr) {
    puts("--------------------------------------------------------------");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->array[i]);
    }
    puts("\n--------------------------------------------------------------");
}

void mallocErr(int *array) {
    if (array == NULL) {
        fprintf(stderr, "Failed to allocate array\n");
        exit(1);
    }
}

void initVector(vector *arr) {
    arr->array = (int *) malloc(INIT_VALUE * sizeof(int));
    mallocErr(arr->array);
    arr->size = 0;
    arr->max_size = INIT_VALUE;
}

void insertElement(vector *arr, int e) {
    if (arr->size < arr->max_size) {
        arr->array[arr->size] = e;
        (arr->size)++;

        return;
    }

    int *array_aux = (int *) malloc((arr->max_size * 2) * sizeof(int));
    mallocErr(array_aux);

    memcpy(array_aux, arr->array, arr->size * sizeof(int));

    array_aux[(arr->size)++] = e;
    free(arr->array);

    arr->array = array_aux;
}

int findElement(int *array, int size, int e) {
    for (int i = 0; i < size; i++) {
        if (array[i] == e)
            return i;
    }
    return -1;
}

void removeElement(vector *arr, int e) {
    int index = findElement(arr->array, arr->size, e);

    if (index != -1) {
        for (int i = index; i < arr->size - 1; i++) {
            arr->array[i] = arr->array[i + 1];
        }
        (arr->size)--;

        if (arr->size < arr->max_size * 0.25 && arr->size > 0) {
            int *array_aux = (int *) malloc((arr->max_size / 2) * sizeof(int));
            mallocErr(array_aux);
            arr->max_size /= 2;

            memcpy(array_aux, arr->array, arr->size * sizeof(int));

            free(arr->array);

            arr->array = array_aux;
        }

        return;
    }
    puts("Index not found");
}