#pragma once
#include <pthread.h>

class Node
{
public:
	static pthread_mutex_t queueLock;

private:
	int timeStamp;

public:
	char Topic;


	int Data;
	Node* Next = 0;
	Node* Prev = 0;

	Node();
	Node(Node &);
	~Node();
};

void addInQueue(Node *& Queue, Node* queueNode);
void nextNode(Node*& queue);

