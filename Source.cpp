#include <iostream>
#include "XMLHelper.h"
#include <wchar.h>


using namespace std;


int main()
{

  XMLHelper::saveData("write.xml",XMLHelper::loadData("read.xml"));
	

	return 0;
}

