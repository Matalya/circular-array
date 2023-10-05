#include <stdio.h>
#include <stdlib.h>

//Contains a head and tail int, a size_t length
//
//and a pointer to a (heap-assumed) array.
typedef struct {
    int* array;
    int head;
    int tail;
    size_t capacity;
    size_t length;
} Circle;

//When a circle is full, that means that items have
//
//been added until the tail came right by the head.
int is_circ_full(Circle* circle) {
    return circle->head == (circle->tail + 1) % circle->capacity;
}

//All empty circles are initialized with head and tail = -1.
int is_circ_empty(Circle* circle) {
    return circle->head == -1;
}

//Initializes a circle and returns a pointer to it.
Circle* initCircle(size_t size) {
    Circle* circle = malloc(sizeof(Circle));
    circle->array = malloc(sizeof(int) * size);
    circle->head = circle->tail = -1;
    circle->capacity = size;
    circle->length = 0;
    return circle;
}

//Specialized function that doubles the size of the circle.
Circle* doubleCircleCapacity(Circle* circle) {
    Circle* newCircle = initCircle(circle->capacity * 2);
    int copyFrom = circle->head;
    int copyTo = -1;

    do {
        newCircle->array[copyTo++] = circle->head;
        copyFrom = (copyFrom + 1) % circle->capacity;
    } while (copyFrom != circle->head);

    newCircle->head = 0;
    newCircle->tail = circle->capacity - 1;
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
    circle->length = 0;
}

//Restarts the function by setting head and tail to -1
//
//to signify that it's empty and allow enqueues to
//
//overwrite it.
void emptyCircle(Circle* circle) {
    circle->head = circle->tail = -1;
    circle->length = 0;
}

//Adds an item according to the FIFO principle.
//
//If full, circle is doubled in size.
void enqueueItemSafe(Circle* circle, int value) {
    if (is_circ_full(circle)) {
        circle = doubleCircleCapacity(circle);
    } else if (is_circ_empty(circle)) {
        circle->head++;
    }
    circle->tail = (circle->tail + 1) % circle->capacity;
    circle->array[circle->tail] = value;
    circle->length++;
}

//Adds an item according to the FIFO principle.
//
//If full, it'll simply overwrite the last item.
void enqueueItem(Circle* circle, int value) {
    if (is_circ_full(circle) || is_circ_empty(circle)) {
        circle->head++;
    }
    circle->tail = (circle->tail + 1) % circle->capacity;
    circle->array[circle->tail] = value;
    circle->length++;
}

//Returns the first element of the circle. Contains no
//
//error handling.
int peekCircle(Circle* circle) {
    return circle->array[circle->head];
}


//Eliminates an item according to the FIFO
//
//principle. Returns a 0 if failure, 1 if success.
int dequeueItem(Circle* circle) {
    if (is_circ_empty(circle)) {
        return 0;
    }
    if (circle->head == circle->tail) {
        emptyCircle(circle);
    } else {
        circle->head = (circle->head + 1) % circle->capacity;
        circle->length--;
    }
    return 1;
}
//Sister function to dequeue item. It returns the dequeued
//
//item. Has no error handling cuz I can't be bothered anymore.
int ripLastItemOff(Circle* circle) {
    int item = circle->head;
    circle->head = (circle->head + 1) % circle->capacity;
    circle->length--;
    return item;
}

int main() {

}