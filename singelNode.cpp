#include "singelNode.h"
#include <iostream>

singelNode::singelNode(wstring nodeName, wstring nodeValue) : Node(nodeName)
{
	this->nodeValue = nodeValue;
}

void singelNode::saveNode(int spaces  , wofstream & path)
{
	for (int i = 0; i < spaces; i++)
		path << "  ";
	path<< "<" << getNodeName() << ">"<< nodeValue<<"</" << getNodeName() << ">\n";
}
