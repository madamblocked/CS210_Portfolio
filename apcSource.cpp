/* Author: Adam Conger
*  CS 210 SNHU
*
*  This program takes input from a text file and loads each unique word into a vector.
*  It also initializes a respective vector for that word's occurrence in the list input.
*  The menu allows the user to choose between several actions.
*
*
*/
#include <Python.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> groceryInput;
vector<string> uniqueWords;
vector<int> uniqueValue;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("apcPython");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"apcPython");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"apcPython");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

int loadData() {
	ifstream inFS;

	inFS.open("dailyInput.txt"); //Opens the input text file.
	if (!inFS.is_open()) {
		cout << "Could not read file, try again." << endl;
		return 1; //Returning 1 results in an error and the file was not found.
	}
	cout << "Now reading file..." << endl; //The following reads in the text file.
	while (!inFS.eof()) {
		string toPushBack;
		getline(inFS, toPushBack);
		groceryInput.push_back(toPushBack);
	}
	cout << "All done." << endl; //done reading the file
	inFS.close();

	if (groceryInput.size() != 0)
	{
		uniqueWords.push_back(groceryInput.at(0));
		uniqueValue.push_back(1);
	}
	cout << "Initial Vector Size: " << uniqueWords.size() << endl;
	cout << "Text file vector: " << groceryInput.size() << endl << endl;

	for (int i = 1; i < groceryInput.size(); ++i) {
		for (int j = 0; j < uniqueWords.size(); ++j) {
			if (groceryInput.at(i) == uniqueWords.at(j)) {
				uniqueValue.at(j) += 1;
				break;
			}
			else {
				if (j == uniqueWords.size() - 1) {
					uniqueWords.push_back(groceryInput.at(i));
					uniqueValue.push_back(1);
				}
				continue;
			}
		}
	}
}

int getOccurrence() { //Generates the vector lists.
	for (int i = 0; i < uniqueWords.size(); ++i) {
		cout << uniqueWords.at(i) << " was purchased " << uniqueValue.at(i) << " times." << endl;
	}
	cout << endl;
}

int getIndividualOccurrence() { //Gathers userNameInput for Python function
	string userNameInput;
	cout << "Which item do you want to see? Captialize the first letter.>>" << endl;
	cin >> userNameInput;
	callIntFunc("get_individual_occurrence", userNameInput);
}

void histogram() {
	char X = 'X';
	cout << " H I S T O G R A M " << endl << endl;
	for (int i = 0; i < uniqueWords.size(); ++i) {
		cout << uniqueWords.at(i);
		for (int j = 0; j < uniqueValue.at(i) + 1; ++j) {
			cout << " " << X;
		}
		cout << endl;
	}
	cout << endl;
}
/*void loadToPython() {  //This passes the 'unique' vectors into Python
	for (int i = 0; i < uniqueWords.size(); ++i) {
		callIntFunc("append_word", uniqueWords.at(i));
		callIntFunc("append_value", uniqueValue.at(i));
	}
}*/

void menu() {
	int userInput = 0;

	while (userInput != 4) {
		cout << "Corner Grocer Inventory" << endl;
		cout << "(1) See everything bought today" << endl;
		cout << "(2) Search item frequency" << endl;
		cout << "(3) Histogram" << endl;
		cout << "(4) Quit" << endl;
		cin >> userInput;

		switch (userInput) {                       
		case 1:
			getOccurrence();
			break;
		case 2:
			getIndividualOccurrence();
			break;
		case 3:
			histogram();
			break;
		case 4:
			break;
		default: cout << "Please choose another option." << endl;
		}
	}

	if (userInput == 4) {
		cout << "Thanks for playing." << endl;
	}
}

void main()
{
	loadData();
	//loadToPython();
	menu();
}