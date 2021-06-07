#pragma once
#include "Node.h"
#include <string>

class singelNode : public Node
{
	wstring nodeValue;
public :
	singelNode(wstring , wstring);
	void saveNode(int , wofstream &);
};

