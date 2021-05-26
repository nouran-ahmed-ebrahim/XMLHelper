#include "XMLHelper.h"
#include <iostream>
#include <fstream>
#include <stack>


XMLHelper::XMLHelper(){}

void XMLHelper::saveData(string path, XMLData file)
{
	ofstream XMLFile(path, ios::out);
	file.savexXMLData(XMLFile);
	XMLFile.close();
}


XMLData XMLHelper::loadData(string path)
{
	ifstream XFile(path, ios::in);

	string Line, name, value;
	int start, charCount;

	stack<Node*>parentNodes;

	Node * currentNode ,* Data =NULL ;
	
	while (getline(XFile , Line))
	{
		start = Line.find("<") + 1;
		charCount = Line.find(">")  - start;
		name = Line.substr(start, charCount);

		if (Line.find("</") == string::npos)
		{
			currentNode = new parentNodeClass(name);
			if (parentNodes.size() != 0)
			{
				((parentNodeClass*)parentNodes.top())->addNode(currentNode);
			}
			parentNodes.push(currentNode);
		}
		else if( Line[Line.find("<")+1] !='/')  // is a single node ( "</" pos is not at the first)
		{
			start = Line.find(">") + 1;
			charCount = (Line.find("</")) - start;
			value = Line.substr(start, charCount);

			currentNode = new singelNode(name, value);
			((parentNodeClass*)parentNodes.top())->addNode(currentNode);

		}
		else
		{
			if (parentNodes.size() == 1)
				Data = parentNodes.top();

			parentNodes.pop();
		}
	}
	XFile.close();

	XMLData newXml(Data);
	return newXml;
}