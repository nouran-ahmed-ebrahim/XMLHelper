#include "XMLHelper.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <assert.h>

XMLHelper::XMLHelper(){}

void XMLHelper::saveData(string path, XMLData file)
{
	ofstream XMLFile(path, ios::out);
	file.savexXMLData(XMLFile);
	XMLFile.close();
}


XMLData XMLHelper::loadData(string path)
{

	assert(validateXMLFile(path));
	
	ifstream XFile(path, ios::in);

	string Line, name, value;
	int firsLessThan, firstGreaterThan, secondLessThan;

	stack<Node*>parentNodes;

	Node * currentNode ,* Data =NULL ;
	
	while (getline(XFile , Line))
	{
		firsLessThan = Line.find('<');
		firstGreaterThan = Line.find('>');
		secondLessThan = Line.find("</");

		name = cutName(Line, firsLessThan, firstGreaterThan);

		if (secondLessThan == string::npos)
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
			value = cutValue(Line, firstGreaterThan , secondLessThan);

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

string XMLHelper::cutName(string line, int firstLessThan, int firstGreaterThan) { //swap
	int nameLength = firstGreaterThan - firstLessThan - 1; // forget -1 

	return line.substr(firstLessThan + 1, nameLength);
}

string XMLHelper::cutValue(string line, int firstGreaterThan, int secondLessThan) {
	int valueLength = secondLessThan - firstGreaterThan - 1; // -1

	return line.substr(firstGreaterThan + 1, valueLength);
}

bool XMLHelper::validateXMLFile(string path)
{
//	return  validateBrackts(path) && cheackAfterRoot(path) && validateRoot(path) && validateTagClosing(path);
	return 0;
}

bool XMLHelper::validateBrackts(string path)
{
	ifstream file(path, ios::in);

	int firstGrater, firstLess, lastGrater,lastLess;
	string line;
	while (getline(file, line))
	{
		 firstGrater = line.find('<');
		 firstLess = line.find('>');

		if (cheackPostions(firstGrater,firstLess) || checkNumOfSpaces(line.substr(0, firstLess)))     // check that all chars at the begain are only space
		{
			file.close();
			return false;
		}

		if (firstGrater != line.size())    //  not parent tag
		{
			lastGrater = line.rfind('>');
			lastLess = line.rfind("</");
			if (cheackPostions(lastGrater, lastLess) ||  lastGrater !=line.size() )
			{
				file.close();
				return false;
			}
		}
	}
	file.close();
	return true;
}

bool XMLHelper::validateTagClosing(string path)
{
	return true;
}

bool XMLHelper::validateRoot(string path)
{
	ifstream file(path, ios::in);
	int grater, less;

	string line,name;

    getline(file, line);
	
	grater = line.find('>');
	less = line.find('<');
	name=cutName(line, grater, less);
    file.close();
	
	return name !="root";
}

bool XMLHelper::checkNumOfSpaces(string str)
{
	return count(str.begin() ,str.end(), ' ') != str.size() ;
}

bool XMLHelper::cheackPostions(int fIdx, int sIdx)  //  indx exist / > < / or empty
{
	return  fIdx == string::npos || sIdx == string::npos ||fIdx < sIdx || fIdx + 1 == sIdx;
}

string XMLHelper::cheackAfterRoot(string path)
{
	ifstream file(path, ios::in);
	string line ,name;
	int grater, less;

	file.seekg(-1, ios::end);
	getline(file,line);

	grater = line.find('>');
	less = line.find("</");
	name = cutName(line, grater, less);
	file.close();

	//return name != "root";
	return line;
}

