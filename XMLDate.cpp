#include "XMLDate.h"




bool XMLData::isEmpty()
{
	return data == NULL;
}

XMLData::XMLData()
{
	data = NULL;
}

XMLData::XMLData( Node * data)
{
	this->data = data;
}


void XMLData::savexXMLData(wofstream& path)
{
	data->saveNode(0, path);
}
