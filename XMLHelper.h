#pragma once
#include "XMLDate.h"


class XMLHelper
{

public:
	XMLHelper();
    static void saveData(string, XMLData);
	static XMLData loadData(string);
};

