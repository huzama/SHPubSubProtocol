class Node
{
public:
	int Data;
	Node* Next;
	Node* Prev;

	Node();
	Node(int);
	Node(Node &);
	~Node();
};