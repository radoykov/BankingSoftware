#ifndef QUEUE_H
#define QUEUE_H

typedef struct QNode
{
    void* val;
    struct QNode *next;
} QNode;

typedef struct Queue
{
    QNode *front;
    QNode *rear;
} Queue;

static QNode *createQnode(void* val);
Queue *initQueue();

void enqueue(Queue *queue, void* val);
int dequeue(Queue *queue);

void releaseQueue(Queue *queue);
void printQueue(Queue *queue);

#endif