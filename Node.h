#pragma once
#include <string>
#include <fstream>
using namespace std;

class Node
{
	wstring nodeName;

public:
	 Node(wstring name);
	 virtual void saveNode(int , wofstream &) = 0;
protected:
	 wstring getNodeName();
};

