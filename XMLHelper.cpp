#include "XMLHelper.h"
#include <iostream>
#include <fstream>
#include <stack>

bool XMLHelper::isErrorFound = false ;
wstring XMLHelper::errorInfo = L"";


wstring XMLHelper::getErrorInfo()
{
	return errorInfo;
}

void XMLHelper::clearPreviousData()
{
	XMLHelper::errorInfo = L"";
	XMLHelper::isErrorFound = false;
}

bool XMLHelper::getIsErrorFound(){
	return isErrorFound;
}

void XMLHelper::saveData(string path, XMLData data)
{
	
	wofstream XMLFile(path, ios::out);
	
	if (XMLFile)
	{
		XMLFile.imbue(locale("en_US.UTF-8"));  // to write arabic in file

		data.saveXMLData(XMLFile);
		XMLFile.close();
	}
	else
		cout << "This file dosen't exist\n\n";
}


XMLData XMLHelper::loadData(string path)
{
	
	if (validateXMLFile(path) == false)
	{
		XMLHelper::isErrorFound= true;
		return NULL ;
	}

	
	wifstream XFile(path);
	XFile.imbue(locale("en_US.UTF-8"));
 
	wstring line , name , value;
	int firsLessThan, firstGreaterThan, secondLessThan;

	stack<Node*>parentNodes;

	Node * currentNode ,* Data =NULL ;
	
	while (getline(XFile , line))
	{
		if (checkNumOfSpaces(line)) // empty line
		{
			continue;
		}

		firsLessThan = line.find('<');
		firstGreaterThan = line.find('>');
		secondLessThan = line.find(L"</");

		name = cutSubStr(line, firsLessThan, firstGreaterThan);

		if (secondLessThan == string::npos)
		{
			currentNode = new parentNodeClass(name);
			if (parentNodes.size() != 0)
			{
				((parentNodeClass*)parentNodes.top())->addNode(currentNode);
			}
			parentNodes.push(currentNode);
		}
		else if( line[line.find('<') + 1] != '/')  // is a single node ( "< / " pos is not at the first)
		{
			value = cutSubStr(line, firstGreaterThan , secondLessThan);

			currentNode = new singelNode(name, value);

			if (name == L"root" && parentNodes.size()==0)
			{
				Data = currentNode;
				break;
			}
			else
			{
				((parentNodeClass*)parentNodes.top())->addNode(currentNode);

			}
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


wstring XMLHelper::cutSubStr(wstring line, int begin, int End) { 
	int nameLength = End - begin - 1; 

	return line.substr(begin + 1, nameLength);
}

bool XMLHelper::validateXMLFile(string path)
{	
	int latLineNum;
	wifstream file(path, ios::in);
	file.imbue(locale("en_US.UTF-8"));

	if (file)
	{
		// order is important 
		// validateRootExistence before the other to save the time & get the correct error (root at begin not a tag error).
		// validateTagClosing after validateBrackets to work correctly. 
		// checkAfterRoot befor checkAfterRoot and validateTagClosing to get the correct error. (if we swap it anything after root will consider as a Tag without closing)
		bool validate = validateRootExistence(file) && checkAfterRoot(file, latLineNum)
			            && validateBrackets(file, latLineNum) && validateTagClosing(file, latLineNum);
		file.close();
		return validate;
	}
	else
	{
		XMLHelper::errorInfo = L"This file dosen't exist\n\n";
		XMLHelper::isErrorFound = true;
		return false;
	}
}

bool XMLHelper::validateBrackets(wifstream& file ,int lastLineNum)
{
	file.clear();
	file.seekg(0, ios::beg);

	int firstLess, firstGrater, lastLess, lastGrater, lineNum = 0;
	wstring line;

	while (getline(file, line))
	{
		lineNum++;

		if (checkNumOfSpaces(line))  // empty line
		{
			continue;
		}
		else if (lineNum > lastLineNum) // all lines after it is empty
		{
			break;
		}

		firstLess = line.find('<');
		firstGrater = line.find('>');
	

		if (!checkBracketsPostions(firstLess, firstGrater) || checkNumOfSpaces(cutSubStr(line,firstLess, firstGrater)) || !checkNumOfSpaces(line.substr(0, firstLess)))     // check that all chars at the begain are only space
		{
			if (!checkBracketsPostions(firstLess, firstGrater))
			{
				XMLHelper::errorInfo = L"There is a mistake in open tag brackets in line. Mistake in line " + to_wstring(lineNum);
			}
			else if (checkNumOfSpaces(line.substr(firstLess, firstGrater - firstLess - 1)))
			{
				XMLHelper::errorInfo = L"Tag name should'nt be empty. Mistake in line " + to_wstring(lineNum);
			}
			else
			{
				XMLHelper::errorInfo = L"Nothing should be written before open tag in line. Mistake in line " + to_wstring(lineNum);
			}
			return false;
		}

		if (firstGrater != line.size() - 1)    //  not parent tag (single node)
		{
			lastGrater = line.rfind('>');
			lastLess = line.rfind(L"</");

			if (!checkBracketsPostions(lastLess, lastGrater) || lastGrater != line.size() - 1)
			{
				if (!checkBracketsPostions(lastLess, lastGrater))
				{
					XMLHelper::errorInfo = L"There is a mistake in closing tag brackets. Mistake in line " + to_wstring(lineNum);
				}
				else
				{
					XMLHelper::errorInfo = L"Nothing should be written after  closing tag. Mistake in line " + to_wstring(lineNum);
				}
				return false;
			}
		}
	}
	return true;
}

bool XMLHelper::validateTagClosing(wifstream & file , int lastLineNum)
{
	file.clear();
	file.seekg(0, ios::beg);
	wstring line , name , sName ;

	int firstLess, firstGrater, lineNum = 0;
	stack<wstring> nodes;
	while (getline(file, line))
		{
			lineNum++;

			if (checkNumOfSpaces(line)) //empty line (file format is not perfect)
			{
				continue;
			}
			else if (lineNum > lastLineNum) // reach the </root> &all lines after it is empty
			{
				break;
			}

			firstLess = line.find('<');
			firstGrater = line.find('>');
			name = cutSubStr(line, firstLess, firstGrater);

			if (name[0] != '/')
			{
				if (firstGrater != line.size() - 1)    //  not parent tag (single node)
				{
					if (isTagNamesMatching(line, name) == false)
					{
						XMLHelper::errorInfo = L"Closing Tag name is not correct in line " + to_wstring(lineNum);
						return false;
					}
				}
				else {
					nodes.push(name);
				}
			}
			else {
				sName = cutSubStr(line, firstLess + 1, firstGrater);
				if (sName == nodes.top())
					nodes.pop();
				else
				{
					XMLHelper::errorInfo = L"Tag " + nodes.top() + L" forgotten to be closed or Tag " + sName + L" didn't be opened";
					return false;
				}
			}
		}
		return (nodes.empty());
	
}

bool XMLHelper::validateRootExistence(wifstream & file) //start with root
{
	file.clear();
	file.seekg(0, ios::beg);

		int grater, less;

		wstring line, name;

		line = getFirstLine(file);

		grater = line.find('>');
		less = line.find('<');
		name = cutSubStr(line, less, grater);


		if (name != L"root")
		{
			XMLHelper::errorInfo = L"Root tag should be at the first";
		}
		return name == L"root";
	
}

bool XMLHelper::checkNumOfSpaces(wstring str) //Check for no characters before tag
{
	return count(str.begin() ,str.end(), ' ') == str.size();
}

bool XMLHelper::checkBracketsPostions(int fIdx, int sIdx) //check brackets existence brackets position (< > not > <)
{
	return  fIdx != string::npos && sIdx != string::npos && fIdx < sIdx; 
}

bool XMLHelper::checkAfterRoot(wifstream & file , int & lastLineNum) //check for no characters after root tag
{
	file.clear();
	file.seekg(0, ios::beg);

		wstring lastLine = getLastLine(file, lastLineNum);

		if (lastLine.find(L"</root>") == string::npos)
		{
			XMLHelper::errorInfo = L"  Closing root tag should be the last thing in the file";
		}
		return (lastLine.find(L"</root>") != string::npos);
	
}

bool XMLHelper::isTagNamesMatching(wstring line , wstring openTagName)
{
	wstring closeTagName;
	int lastGrater, lastLess;

	lastGrater = line.rfind('>');
	lastLess = line.rfind(L"</");
	closeTagName = cutSubStr(line, lastLess + 1, lastGrater);
	return openTagName == closeTagName;
}

wstring XMLHelper::getLastLine(wifstream& file , int & lastLineNum) {

	int pos = 0;
	wstring lastLine,line;

	while (getline(file,line))
	{
		pos++;
		if (!checkNumOfSpaces(line))
		{
			lastLine = line;
			lastLineNum = pos;
		}
	}
	return lastLine;
}

wstring XMLHelper::getFirstLine(wifstream& file) {

	wstring  line;

	while (getline(file, line))
	{
		if (!checkNumOfSpaces(line))
		{
			return line;
		}
	}
}
