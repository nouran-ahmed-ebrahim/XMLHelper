#pragma once
#include <string>
#include <fstream>
using namespace std;

class Node
{
	string nodeName;

public:
	 Node(string name);
	 virtual void saveNode(int , ofstream &) = 0;
protected:
	 string getNodeName();
};

