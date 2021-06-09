#include "XMLHelper.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <assert.h>
#include <codecvt>

bool XMLHelper::isErrorFound = false ;
wstring XMLHelper::errorInfo = L"";
bool XMLHelper::isRootFound = false;

XMLHelper::XMLHelper(){
}

wstring XMLHelper::getErrorInfo()
{
	return errorInfo;
}

void XMLHelper::clearPreviousData()
{
	XMLHelper::isRootFound = false;
	XMLHelper::errorInfo = L"";
	XMLHelper::isErrorFound = false;
}

bool XMLHelper::getIsErrorFound(){
	return isErrorFound;
}

void XMLHelper::saveData(string path, XMLData file)
{
	wofstream XMLFile(path, ios::out);

	// to write arabic in file
	XMLFile.imbue(locale("en_US.UTF-8"));

	file.savexXMLData(XMLFile);
	XMLFile.close();
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

	wstring Line , name , value;
	int firsLessThan, firstGreaterThan, secondLessThan;

	stack<Node*>parentNodes;

	Node * currentNode ,* Data =NULL ;
	
	while (getline(XFile , Line))
	{
		firsLessThan = Line.find('<');
		firstGreaterThan = Line.find('>');
		secondLessThan = Line.find(L"</");

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
		else if( Line[Line.find('<') + 1] != '/')  // is a single node ( "< / " pos is not at the first)
		{
			value = cutValue(Line, firstGreaterThan , secondLessThan);

			currentNode = new singelNode(name, value);

			if (name != L"root")
			{
				((parentNodeClass*)parentNodes.top())->addNode(currentNode);
			}
			else
			{
				Data = currentNode;
				break;
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


wstring XMLHelper::cutName(wstring line, int firstLessThan, int firstGreaterThan) { //swap
	int nameLength = firstGreaterThan - firstLessThan - 1; // forget -1 

	return line.substr(firstLessThan + 1, nameLength);
}

wstring XMLHelper::cutValue(wstring line, int firstGreaterThan, int secondLessThan) {
	int valueLength = secondLessThan - firstGreaterThan - 1; // -1

	return line.substr(firstGreaterThan + 1, valueLength);
}

bool XMLHelper::validateXMLFile(string path)
{	
	// order is important
	// validateRootExistence after validateBrackets to get the correct error. 
	// validateRootExistence before the other to save the time.
	// validateTagClosing after validateBrackets to work correctly. 
	// checkAfterRoot after validateTagClosing to get the correct error. (it will check if there is anything after root closing tag not its existence )
	return validateBrackets(path) && validateRootExistence(path) && validateTagClosing(path) && checkAfterRoot(path) ; 
}

bool XMLHelper::validateBrackets(string path)
{
	wifstream file(path, ios::in);
	file.imbue(locale("en_US.UTF-8"));

	int firstLess, firstGrater, lastLess,lastGrater , lineNum = 0;
	wstring line ;
	string lineCopy;

	while (getline(file, line))
	{
		lineNum++;

		// creating wstring to string convertor
		using convert_type = codecvt_utf8<wchar_t>;
		wstring_convert< convert_type, wchar_t> convertor;

		lineCopy = convertor.to_bytes(line);
		 firstLess = line.find('<');
		 firstGrater = line.find('>');

		if (!checkBracketsPostions(firstLess,firstGrater) || !checkNumOfSpaces(lineCopy.substr(0, firstLess)))     // check that all chars at the begain are only space
		{
			file.close();
			if (!checkBracketsPostions(firstLess, firstGrater))
			{
				XMLHelper::errorInfo = L"There is a mistake in open tag brackets in line. Mistake in line ";
			}
			else
			{
				XMLHelper::errorInfo = L"Nothing should be written before open tag in line. Mistake in line ";
			}
			XMLHelper::errorInfo.push_back(lineNum + '0');
			return false;
		}

		if (firstGrater != line.size()-1)    //  not parent tag (single node)
		{
			lastGrater = line.rfind('>');
			lastLess = line.rfind(L"</");

			if (!checkBracketsPostions(lastLess, lastGrater) ||  lastGrater !=line.size()-1 )
			{
				file.close();
				if (!checkBracketsPostions(lastLess, lastGrater))
				{
					XMLHelper::errorInfo = L"There is a mistake in closing tag brackets. Mistake in line ";
				}
				else
				{
					XMLHelper::errorInfo = L"Nothing should be written after  closing tag. Mistake in line ";
				}
				XMLHelper::errorInfo.push_back(lineNum + '0');
				return false;
			}
		}
	}
	file.close();

   	return true;
}

bool XMLHelper::validateTagClosing(string path)
{
	wifstream file(path, ios::in);
	file.imbue(locale("en_US.UTF-8"));
	wstring line , name , sName ;

	int firstLess, firstGrater, lineNum = 0;
	stack<wstring> nodes;

	while (getline(file, line))
	{
		lineNum++;

		firstLess = line.find('<');
		firstGrater = line.find('>');
		name = cutName(line,firstLess, firstGrater);
		
		if (isRootUnique(name) == false)
		{
			XMLHelper::errorInfo = L"Root tag can't be repeted. Mistake in line";
			XMLHelper::errorInfo.push_back(lineNum + '0');
			return false;
		}

		if (name[0] != '/') 
		{
			if (firstGrater != line.size()-1)    //  not parent tag (single node)
			{
				if (isTagNamesMatching(line, name) == false)
				{
					XMLHelper::errorInfo = L"Closing Tag name is not correct in line ";
				    XMLHelper::errorInfo.push_back( lineNum+'0');
					return false;
				}
			}
			else {
					nodes.push(name);
			}
		}
		else {
			sName = cutName(line, firstLess + 1, firstGrater);
			if (sName == nodes.top())
				nodes.pop();
			else
			{
				XMLHelper::errorInfo = L"Tag "+ nodes.top() + L" forgotten to be closed or Tag "+ sName + L" didn't be opened";
				return false;
			}
		}
	}
	
	file.close();
	return (nodes.empty());
}

bool XMLHelper::validateRootExistence(string path) //start with root
{
	wifstream file(path, ios::in);
	file.imbue(locale("en_US.UTF-8"));
	int grater, less;

	wstring line , name ;

    getline(file, line);
	
	grater = line.find('>');
	less = line.find('<');
	name=cutName(line, less,grater);
    file.close();
	
	if (name != L"root")
	{
		XMLHelper::errorInfo = L"Root tag should be at the first";
	}
	return name == L"root"; 
}

bool XMLHelper::checkNumOfSpaces(string str) //Check for no characters before tag
{
	return count(str.begin() ,str.end(), ' ') == str.size(); 
}

bool XMLHelper::checkBracketsPostions(int fIdx, int sIdx) //check brackets existence, tag name existence and brackets position (< > not > <)
{
	return  fIdx != string::npos && sIdx != string::npos && fIdx < sIdx && fIdx + 1 != sIdx; 
}

bool XMLHelper::checkAfterRoot(string path) //check for no characters after root tag
{
	wstring lastLine = getLastLine(path) ;

	if(lastLine.find(L"</root>") == string::npos)
	{
		XMLHelper::errorInfo = L"  Closing root tag should be the last thing in the file";
	}
	return (lastLine.find(L"</root>")>=0);
}

bool XMLHelper::isTagNamesMatching(wstring line , wstring openTagName)
{
	wstring closeTagName;
	int lastGrater, lastLess;

	lastGrater = line.rfind('>');
	lastLess = line.rfind(L"</");
	closeTagName = cutName(line, lastLess + 1, lastGrater);
	return openTagName == closeTagName;
}

bool XMLHelper::isRootUnique(wstring tagName)
{

	if (tagName == L"root")
	{
		if (isRootFound == false)
		{
			isRootFound = true;
			return true;
		}
		else
			return false;
	}

	return true;
}

wstring XMLHelper::getLastLine(string path) {

	wifstream file(path, ios::in);
	file.imbue(locale("en_US.UTF-8"));
	wstring lastLine ;


	if (file.is_open()) {
		file.seekg(-1, ios_base::end);                // go to one spot before the EOF

		bool keepLooping = true;
		while (keepLooping) {
			wchar_t ch;
			file.get(ch);

			if ((int)file.tellg() <= 1) {             // If the data was at or before the 0th byte
				file.seekg(0);                       // The first line is the last line
				keepLooping = false;                // So stop there
			}
			else if (ch == '\n') {                   // If the data was a newline
				keepLooping = false;                // Stop at the current position.
			}
			else {                                  // If the data was neither a newline nor at the 0 byte
				file.seekg(-2, ios_base::cur);        // Move to the front of that data, then to the front of the data before it
			}
		}


		getline(file, lastLine);                      // Read the current line

		file.close();
	}

	return lastLine;
}

