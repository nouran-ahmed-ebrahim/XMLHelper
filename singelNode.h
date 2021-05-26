#pragma once
#include "Node.h"
#include <string>

class singelNode : public Node
{
	string nodeValue;
public :
	singelNode(string , string);
	void saveNode(int , ofstream &);
};

