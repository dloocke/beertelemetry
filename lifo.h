typedef struct Node
{
	float value;
	struct Node *next;
} Node;

typedef struct LIFO
{
	unsigned int max_length;
	Node *first;
	Node *last;
} LIFO;

/* Automatically adjusts length of queue to max_length and
 * adds val to end of queue 
 */
void autoQueue(LIFO *queue, float val);

int queueBasicAverage(LIFO *queue, float *average);
int queueDCAverage(LIFO *queue, float *average);

unsigned int queueLength(LIFO *queue);

void queueVal(LIFO *queue, float val);
void dequeue(LIFO *queue);
void clearQueue(LIFO *queue);

void printQueue(const LIFO *queue);
