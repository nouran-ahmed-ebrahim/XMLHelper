#include <iostream>
#include "XMLHelper.h"


using namespace std;

void addData();

int main()
{
 // XMLHelper::saveData("XMLFile.xml",XMLHelper::loadData("XMLFile.xml"));
	
	cout << XMLHelper::cheackAfterRoot("XMLFile.xml");
	return 0;
}





















void addData()
{
	Node* node = new parentNodeClass("root");

	Node* subNode = new parentNodeClass("Students");

	singelNode* tepS = new singelNode("Nouran", "8/5/2001");
	((parentNodeClass*)subNode)->addNode(tepS);

	tepS = new singelNode("Sama", "15/4/2001");
    ((parentNodeClass*)subNode)->addNode(tepS);

	tepS = new singelNode("MennaTullah", "23/7/2001");
	((parentNodeClass*)subNode)->addNode(tepS);

	tepS = new singelNode("Nada", "10/10/2001");
	((parentNodeClass*)subNode)->addNode(tepS);

	((parentNodeClass*)node)->addNode(subNode);

	XMLData  file(node);

	XMLHelper::saveData("XMLFile.xml" , file);

	delete node, tepS, subNode;
}

/*
<Student>
	<Nouran>
	  <name>Nouran</name>
	</Nouran>
  </Student>
  <TA>
	<Ramy>
	  <Name>Ramy</Name>
	</Ramy>
  </TA>
  */