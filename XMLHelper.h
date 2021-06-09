#pragma once
#include "XMLDate.h"


class XMLHelper
{
	static  bool isErrorFound;
	static wstring errorInfo;
	static bool isRootFound ;
    static wstring cutName(wstring, int, int);
	static wstring cutValue(wstring, int, int);
	static bool validateBrackets(string);
	static bool validateTagClosing(string);
	static bool validateRootExistence(string);
	static bool checkNumOfSpaces(string ); 
	static wstring getLastLine(string);
	static bool checkBracketsPostions(int, int);
	static bool checkAfterRoot(string path);
	static bool isTagNamesMatching(wstring, wstring);
	static bool isRootUnique(wstring);
	
public:
	XMLHelper();
	static void clearPreviousData();
	static bool getIsErrorFound();
	static wstring getErrorInfo();
	static bool validateXMLFile(string);
    static void saveData(string, XMLData);
	static XMLData loadData(string);
	

};

