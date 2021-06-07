#pragma once
#include "Node.h"
#include <list>

class parentNodeClass: public Node
{
	list<Node *>childNodes;

public:
	parentNodeClass(wstring);
	void saveNode(int , wofstream &);
	void addNode(Node*);

};

