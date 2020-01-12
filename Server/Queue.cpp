#include "Queue.hpp"
#include<iostream>
int MemoryCheck = 0;

Node::Node()
	:Data(MemoryCheck)
{
	MemoryCheck++;
}

Node::Node(int No)
	: Data(MemoryCheck)
{
	MemoryCheck++;
	
	if (No <= 0)
		return;
	No--;

	Node* Temp = this, *Prev = this;

	while (No--)
	{
		Temp->Next = new Node;
		Temp = Temp->Next;
		Temp->Prev = Prev;
		Prev = Temp;
	}
}

Node::Node(Node & toCopy)
{
	Node *To = this, *From = &toCopy;
	MemoryCheck++;

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
	MemoryCheck--;
	if (this->Next)
		delete this->Next;
}

void Traversion_F(Node* Head)
{
	while (Head)
	{
		std::cout << Head->Data << std::endl;
		Head = Head->Next;
	}
}

Node* EndingPointer(Node* Head)
{
	while (Head->Next)
		Head = Head->Next;

	return Head;
}

Node* Traversion_B(Node* Head)
{
	while (Head)
	{
		std::cout << Head->Data << std::endl;
		Head = Head->Prev;
	}
	return Head;
}

void InsertAtStarts(Node*& Head, Node* Start)
{
	Start->Next = Head;
	Head->Prev = Start;
	Head = Start;
}

void InsertAtEnd(Node *& Back, Node* End)
{
	End->Prev = Back;
	Back->Next = End;
	Back = End;
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
