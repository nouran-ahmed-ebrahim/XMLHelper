#include "XMLDate.h"



XMLData::XMLData( Node * data)
{
	this->data = data;
}


void XMLData::savexXMLData(wofstream& path)
{
	data->saveNode(0, path);
}
