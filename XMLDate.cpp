#include "XMLDate.h"



XMLData::XMLData( Node * data)
{
	this->data = data;
}


void XMLData::savexXMLData(ofstream& path)
{
	data->saveNode(0, path);
}
