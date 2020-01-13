#pragma once


class Node
{
private:
	int timeStamp;

public:
	char Topic;


	int Data;
	Node* Next = 0;
	Node* Prev = 0;

	Node();
	Node(int);
	Node(Node &);
	~Node();
};