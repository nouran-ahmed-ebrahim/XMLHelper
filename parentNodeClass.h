#pragma once
#include "Node.h"
#include <list>

class parentNodeClass: public Node
{
	list<Node *>childNodes;

public:
	parentNodeClass(string);
	void saveNode(int , ofstream &);
	void addNode(Node*);

};

