#include "Queue.hpp"

Node::Node()
{
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


Node::~Node()
{
	if (this->Next)
		delete this->Next;
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
	if(!Queue)
		Queue = queueNode;
	else
		lastNode(Queue)->Next = queueNode;
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
