#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static QNode *createQnode(void* val)
{
    QNode *node = (QNode *)malloc(sizeof(QNode));
    node->val = val;
    node->next = NULL;

    return node;
}

Queue *initQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue *queue)
{
return (queue->front == NULL);
}

void enqueue(Queue *queue, void* val)
{
    QNode *node = createQnode(val);
    if (queue->front == NULL)
    {
        queue->rear = queue->front = node;
        return;
    }

    queue->rear->next = node;
    queue->rear = node;
}

void* dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue is empty.\n");
        exit(1);
    }

    QNode *front = queue->front;

    void* val = front->val;

    queue->front = front->next;

    free(front);

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    return val;
}

void releaseQueue(Queue *queue)
{
    while (queue->front != NULL)
    {
        dequeue(queue);
    }

    free(queue);
}

void printInt(void *data) 
{
    printf("%d", *(int *)data);
}

void printQueue(Queue *queue)
{
    QNode *it = queue->front;
    printf("\nQueue: ");
    while (it != NULL)
    {
        printInt(it->val);
        printf(" -> ");
        it = it->next;
    }
    printf("NULL");
}


