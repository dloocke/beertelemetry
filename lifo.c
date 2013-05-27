#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lifo.h"

void autoQueue(LIFO *queue, float val)
{
	if(queue == NULL)
		return;

	queueVal(queue, val);

	while(queueLength(queue) > queue->max_length) {
		dequeue(queue);
	}
}

int queueBasicAverage(LIFO *queue, float *average)
{
	Node *nd;
	float sum;
	unsigned int count;

	if(queue == NULL || average == NULL)
		return -1;

	sum=0.0;
	count=0;
	nd = queue->last;
	while(nd) {
		sum += nd->value;
		count++;

		nd = nd->next;
	}

	*average = (float)(sum/count);

	return 0;
}

void queueVal(LIFO *queue, float val) 
{
	Node *nd;

	if(queue == NULL)
		return;

	nd = malloc(sizeof(Node));
	nd->value = val;
	nd->next = NULL;

	if(queue->first != NULL) {
		nd->next = queue->last;
		queue->last = nd;
	} else {
		queue->last = nd;
		queue->first = nd;
	}
}

void dequeue(LIFO *queue)
{
	Node *nd;

	if(queue == NULL)
		return;

	nd = queue->last;
	if(nd != NULL) {
		if(nd == queue->first) {
			queue->last = queue->first = NULL;
			free(nd);
			return;
		}

		while(nd->next != queue->first) {
			nd = nd->next;
		}
		free(queue->first);
		queue->first = nd;
		queue->first->next = NULL;
	}
}

void clearQueue(LIFO *queue)
{
	if(queue == NULL)
		return;

	while(queueLength(queue))
		dequeue(queue);
}

unsigned int queueLength(LIFO *queue)
{
	Node *nd;
	unsigned int length;

	if(queue == NULL)
		return 0;

	length = 0;
	nd = queue->last;
	while(nd) {
		nd = nd->next;
		length++;
	}

	return length;
}

void printQueue(const LIFO *queue) 
{
	Node *nd;

	if(queue == NULL)
		return;

	nd = queue->last;
	while(nd) {
		printf("| %f ", nd->value);
		nd = nd->next;
	}
	printf("\n");
}