#include "Node.h"
#include <iostream>

Node::Node(string nodeName)
{
	this->nodeName = nodeName;
}


string Node::getNodeName()
{
	return nodeName;
}

