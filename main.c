#include <stdio.h>
#include <stdlib.h>

//Contains a head and tail int, a size_t length
//
//and a pointer to a (heap?) array.
typedef struct {
    int* array;
    int head;
    int tail;
    size_t length;
} Circle;

//When a circle is full, that means that items have
//
//been added until the tail came right by the head.
int is_circ_full(Circle* circle) {
    return circle->head == (circle->tail + 1) % circle->length;
}

//All circles are initialized with head and tail = 0.
int circ_is_empty(Circle* circle) {
    return circle->head == -1;
}

//Initializes a circle and returns a pointer to it.
Circle* initCircle(size_t size) {
    Circle* circle = malloc(sizeof(Circle));
    circle->array = malloc(sizeof(int) * size);
    circle->head = circle->tail = -1;
    circle->length = size;
    return circle;
}

//Specialized function that doubles the size of the circle.
Circle* circleIsFull(Circle* circle) {
    Circle* newCircle = initCircle(circle->length * 2);
    int copyFrom = circle->head;
    int copyTo = -1;

    do {
        newCircle->array[copyTo++] = circle->head;
        copyFrom = (copyFrom + 1) % circle->length;
    } while (copyFrom != circle->head);

    newCircle->head = 0;
    newCircle->tail = circle->length - 1;
    return newCircle;
}

//Restarts the array of the circle be freeing it and
//
//reallocating it somewhere else, while setting head
//
//and tail to -1 to signify that the array is empty.
void nukeCircle(Circle* circle) {
    free(circle->array);
    circle->array = malloc(sizeof(int));
    circle->head = circle->tail = -1;
}

//Restarts the function by setting head and tail to -1
//
//to signify that it's empty and allow enqueues to
//
//overwrite it.
void emptyCircle(Circle* circle) {
    circle->head = circle->tail = -1;
}

//Adds an item according to the FIFO principle
void enqueueItem(Circle* circle, int value) {
    if (is_circ_full(circle)) {
        circle = circleIsFull(circle);
    } else if (circ_is_empty(circle)) {
        circle->head++;
    }
    circle->tail = (circle->tail + 1) % circle->length;
    circle->array[circle->tail] = value;
}

//Eliminates an item according to the FIFO
//
//principle. Returns a 0 if failure, 1 if success.
int dequeueItem(Circle* circle) {
    if (circ_is_empty(circle)) {
        return 0;
    }
    if (circle->head == circle->tail) {
        emptyCircle(circle);
    } else {
        circle->head = (circle->head + 1) % circle->length;
    }
    return 1;
}

int main() {

}