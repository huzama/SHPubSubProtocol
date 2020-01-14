#pragma once
#include <pthread.h>

class Node
{
public:
	static pthread_mutex_t queueLock;

public:
	char Topic;
	char Data[1024];


	Node* Next = 0;

	Node();
	~Node();
};

void addInQueue(Node *& Queue, Node* queueNode);
void nextNode(Node*& queue);