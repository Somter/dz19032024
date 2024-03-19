#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#pragma comment(lib, "urlmon.lib")
using namespace std;

int main()
{
	//setlocale(0, "ru");
	//SetConsoleOutputCP(1251);
	//SetConsoleCP(1251);

	// the URL to download from 
	//string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";

	string year, month, day, date;
	string currency;
	string link;
	cout << "Enter year: ";
	cin >> year;
	cout << "Enter month: ";
	cin >> month;
	cout << "Enter day: ";
	cin >> day;
	date = year + month + day;

	cout << "Enter currency: ";
	cin >> currency;
	string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?valcode=" + currency + "&date=" + date + "&json"; 

	// the destination file 
	string destFile = "file.txt";
	//// URLDownloadToFile returns S_OK on success 
	if (S_OK == URLDownloadToFileA(NULL, srcURL.c_str(), destFile.c_str(), 0, NULL))
	{
		cout << "Saved to " << destFile << "\n";
	}
	else cout << "Fail!\n";

	ifstream file("file.txt");

	string textFromFile;
	if (file.is_open()) {
		stringstream text;
		text << file.rdbuf();
		textFromFile = text.str();

		file.close();
	}

	string ResultDate;
	size_t startStr = textFromFile.find("\"exchangedate\":\"");
	startStr += 16;
	size_t endStr = textFromFile.find('"', startStr);
	ResultDate = textFromFile.substr(startStr, endStr - startStr);

	string ResultCurrency;
	startStr = textFromFile.find("\"cc\":\"");
	startStr += 6;
	endStr = textFromFile.find('"', startStr);
	ResultCurrency = textFromFile.substr(startStr, endStr - startStr);

	string ResultRate;
	startStr = textFromFile.find("\"rate\":");
	startStr += 7;
	endStr = textFromFile.find(',', startStr);
	ResultRate = textFromFile.substr(startStr, endStr - startStr);

	cout << endl;
	cout << "Date: " << ResultDate << endl;
	cout << "Currency: " << ResultCurrency << endl;
	cout << "Rate: " << ResultRate << endl;


	/*
	1. С клавиатуры вводим следующие данные:
	  дата
	  Валюта
	  Вывести актуальную информацию!
	  формат вывода - Дата: 19.03.2024г, Валюта - USD, 1$ = 38.9744 грн.

	*/

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
