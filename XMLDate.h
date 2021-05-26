#pragma once
#include "parentNodeClass.h"
#include "singelNode.h"

class XMLData
{
	Node* data;

public:

	XMLData(Node*);
	void savexXMLData(ofstream&);
};

/*

*/