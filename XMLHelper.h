#pragma once
#include "XMLDate.h"


class XMLHelper
{
	static string cutName(string, int, int);
	static string cutValue(string, int, int);
	static bool validateXMLFile(string);
	static bool validateBrackts(string);
	static bool validateTagClosing(string);
	static bool validateRoot(string);
	static bool checkNumOfSpaces(string );
	static bool cheackPostions(int, int);

public:
	XMLHelper();
    static void saveData(string, XMLData);
	static XMLData loadData(string);
	static string cheackAfterRoot(string path);

};

