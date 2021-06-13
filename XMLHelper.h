#pragma once
#include "XMLData.h"
#include <vector>


class XMLHelper
{
	static  bool isErrorFound;
	static wstring errorInfo;

	static bool validateBrackets(wifstream & ,int);
	static bool validateTagClosing(wifstream & ,int);
	static bool validateRootExistence(wifstream &);
	static bool checkAfterRoot(wifstream & ,int&);

	static bool checkNumOfSpaces(wstring ); 
	static bool checkBracketsPostions(int, int );
	static bool isTagNamesMatching(wstring, wstring);

	static wstring cutSubStr(wstring, int, int);
	static wstring getLastLine(wifstream& , int&);
	static wstring getFirstLine(wifstream&);


public:
	static void clearPreviousData();
	static bool getIsErrorFound();
	static wstring getErrorInfo();
	static bool validateXMLFile(string);
    static void saveData(string, XMLData);
	static XMLData loadData(string);
	

};
