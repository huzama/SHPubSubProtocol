#include "Queue.hpp"
#include <iostream>

pthread_mutex_t Node::queueLock;


Node::Node()
{
	if(pthread_mutex_init(&queueLock, NULL) != 0)
	    std::cout << "Queue Mutex init Failed" << std::endl;

}

void nextNode(Node*& queue)
{
	auto deleteMe = queue;
	
	pthread_mutex_lock(&Node::queueLock);
	queue = queue->Next;
	pthread_mutex_unlock(&Node::queueLock);
	
	delete deleteMe;
}


Node::~Node()
{
	pthread_mutex_destroy(&queueLock);
}


Node* lastNode(Node* Head)
{
	while (Head->Next)
		Head = Head->Next;

	return Head;
}


void addInQueue(Node *&Queue, Node* queueNode)
{    

	pthread_mutex_lock(&Node::queueLock);
	if(!Queue)
		Queue = queueNode;
	else
		lastNode(Queue)->Next = queueNode;

    pthread_mutex_unlock(&Node::queueLock);

}