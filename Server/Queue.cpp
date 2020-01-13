#include "Queue.hpp"
#include <iostream>

pthread_mutex_t Node::queueLock;


Node::Node()
{
	if(pthread_mutex_init(&queueLock, NULL) != 0)
	    std::cout << "Queue Mutex init Failed" << std::endl;

}

Node::Node(Node & toCopy)
{
	Node *To = this, *From = &toCopy;

	To->Data = From->Data;

	while (From->Next)
	{
		To->Next = new Node;
		To->Next->Prev = To;
		To = To->Next;
		From = From->Next;
		To->Data = From->Data;
	}
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


void InsertAtStarts(Node*& Head, Node* Start)
{
	Start->Next = Head;
	Head->Prev = Start;
	Head = Start;
}

void addInQueue(Node *& Queue, Node* queueNode)
{    
	std::cout << "Added in queue" << std::endl;

	pthread_mutex_lock(&Node::queueLock);
	if(!Queue)
		Queue = queueNode;
	else
		lastNode(Queue)->Next = queueNode;

    pthread_mutex_lock(&Node::queueLock);

}

void InsertAtN(Node * Head, Node* Middle, int N)
{
	while (N-- && Head->Next)
		Head = Head->Next;

	Node* Temp = Head->Next;
	Head->Next = Middle;
	Middle->Next = Temp;
	Middle->Prev = Head;
	Middle->Next->Prev = Middle;
}

void DeleteAtStarts(Node *& Head)
{
	Node* Temp = Head;
	Head = Head->Next;
	Head->Prev = 0;
	Temp->Next = 0;
	delete Temp;
}

void DeleteAtEnd(Node *& Back)
{
	Node* Temp = Back;
	Back = Back->Prev;
	delete Temp;
	Back->Next = 0;
}

void DeleteAtN(Node * Head, int N)
{
	if (!Head)
		return;

	while (N-- && Head->Next)
		Head = Head->Next;

	Node* toDelete = Head;
	Head->Prev->Next = Head->Next;
	Head->Next->Prev = Head;


	Head->Next = 0;
	delete toDelete;
}
