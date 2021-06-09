#pragma once
#include "parentNodeClass.h"
#include "singelNode.h"

class XMLData
{
	Node* data;

public:
	bool isEmpty();
	XMLData(); // to create global var it will be filling in loading and it will be used in saving  
	XMLData(Node*);
	void savexXMLData(wofstream&);
};
