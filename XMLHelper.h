#pragma once
#include "XMLDate.h"


class XMLHelper
{
    static wstring cutName(wstring, int, int);
	static wstring cutValue(wstring, int, int);
	static bool validateBrackets(string);
	static bool validateTagClosing(string);
	static bool validateRoot(string);
	static bool checkNumOfSpaces(string ); 
	static wstring getLastLine(string);
	static bool checkBracketsPostions(int, int);
	static bool cheackAfterRoot(string path);

public:
	static bool validateXMLFile(string);
	XMLHelper();
        static void saveData(string, XMLData);
	static XMLData loadData(string);
	

};

