#include "Node.h"
#include <iostream>

Node::Node(wstring nodeName)
{
	this->nodeName = nodeName;
}


wstring Node::getNodeName()
{
	return nodeName;
}

