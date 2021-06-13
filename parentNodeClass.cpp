#include "parentNodeClass.h"
#include <iostream>


parentNodeClass::parentNodeClass(wstring nodeName):Node(nodeName){}

void parentNodeClass::saveNode(int spaces , wofstream & path)
{
	for (int i = 0; i < spaces; i++)
		path << "  ";

	path << "<" <<getNodeName() << ">\n";
	 
	for (auto child : childNodes)
		child->saveNode(spaces+1, path);
	
	for (int i = 0; i < spaces; i++)
		path << "  ";
	path << "</" << getNodeName() << ">";

	if (spaces !=0 )
		path << "\n";
}

void parentNodeClass::addNode(Node* newChild)
{
	childNodes.push_back(newChild);
}
