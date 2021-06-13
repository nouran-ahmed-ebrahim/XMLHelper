#include <iostream>
#include "XMLHelper.h"
#include <wchar.h>


using namespace std;

XMLData fileData;

void loadOption();
void saveOption();
void checkOption();

int main()
{
	int operationNum = 0;
	string path;
	
	do
	{
		cout << "Chose operation number:\n";
		cout << "1) Load Data from file     2) Save data in file      3) Check file      4) Close\n";
		cout << "Operation Number : ";
		cin >> operationNum;
		switch (operationNum)
		{
		case 1:
			loadOption();
			break;
		case 2 :
			saveOption();
			break;
		case 3:
			checkOption();
			break;
		case 4:
			break;
		default:
			cout << "Enter correct operation number\n\n";
			break;
		}
	} while (operationNum != 4);


	return 0;
}


void loadOption()
{
	string filePath;

	cout << "Enter file path : ";
	cin >> filePath;

	fileData = XMLHelper::loadData(filePath);

	if (XMLHelper::getIsErrorFound() == true)
		wcout << XMLHelper::getErrorInfo()<<"\n\n";
	else
	cout << "Data has been loaded successfully\n\n";
}


void saveOption()
{
	if (fileData.isEmpty())
	{
		cout << "There is no data uploaded\n\n";
		return;
	}
	string filePath;
	
	cout << "Enter File Path : ";
	cin >> filePath;

	XMLHelper::saveData(filePath, fileData);
	
	cout << "File has been saved correctly\n\n";
}


void checkOption()
{
	bool isCorrect;
	string filePath;

	XMLHelper::clearPreviousData();

	cout << "Enter file path : ";
	cin >> filePath;

	isCorrect = XMLHelper::validateXMLFile(filePath);
	
	if (isCorrect == true)
		cout << "File is correct\n\n";
	else
		wcout << XMLHelper::getErrorInfo()<<"\n\n";
	XMLHelper::clearPreviousData();

}

