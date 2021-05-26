#include "singelNode.h"
#include <iostream>

singelNode::singelNode(string nodeName, string nodeValue) : Node(nodeName)
{
	this->nodeValue = nodeValue;
}

void singelNode::saveNode(int spaces  , ofstream & path)
{
	for (int i = 0; i < spaces; i++)
		path << "  ";
	path<< "<" << this->getNodeName() << ">"<<" "<< nodeValue<<" </" << this->getNodeName() << ">\n";
}