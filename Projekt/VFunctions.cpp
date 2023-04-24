#include "VFunctions.h"

extern bool NOSAVE;
extern bool NOEDIT;

/**
 * This function gets INT input from user
 * 
 * \param txt String that is displayed so user can know what to input
 * \return  On success returns user's input
 */
int getInt(string txt)
{
	string t;
	int x;
	int blad;
	while (true)
	{
		blad = 0;
		cout << "Podaj" << " " << txt << ": ";
		getline(cin, t);
		try
		{
			t.substr(t.find_first_of("0123456789"));
			int x = stoi(t, NULL, 10);
		}
		catch (...)
		{
			blad++;
		}

		if (t.empty() || blad == 1)
		{
			cout << "Podane dane sa niezgodne z wymaganymi!" << endl;
			cout << "Sprobuj jeszcze raz!" << endl;
		}
		else
			return stoi(t, NULL, 10);
	}
}
/**
 * This function allows user to input string. It is used ONLY
 * when user input can not be empty.
 * 
 * \param txt String that is displayed so user can know what to input
 * \return On success returns user's input
 */
string getString(string txt)
{
	string x;
	cout << "Podaj" << " " << txt << ": ";
	getline(cin, x);
	while (x.empty())
	{
		cout << "Podane dane sa niezgodne z wymaganymi!" << endl;
		cout << "Sprobuj jeszcze raz!" << endl;
		cout << "Podaj" << " " << txt << ": ";
		cin >> x;
		cin.ignore();
	}
	return x;
}

/**
 * This function allows for string input, with option to allow strings only with numbers or
 * no numbers. Use it only when u expect input from user.
 *
 * \param txt String which is displayed to user
 * \param options 1- string without numbers, 0- string with numbers
 * \return On success returns string, on failure returns ""
 */
string getString(string txt, int options)
{
	string x;
	cout << "Podaj" << " " << txt << ": ";
	getline(cin, x);
	//cin.ignore();
	while (x.empty())
	{
		cout << "Podane dane sa niezgodne z wymaganymi!" << endl;
		cout << "Sprobuj jeszcze raz!" << endl;
		cout << "Podaj" << " " << txt << ": ";
		cin >> x;
		cin.ignore();
	}
	
	if (options == 1)
	{
		if (isSWN(x))
			return x;
		else
		{
			cout << "Podano dane w blednym formacie!" << endl;
			return "";
		}
	}

	if (options == 0)
	{
		if (isSWL(x))
			return x;
		else
		{
			cout << "Podano dane w blednym formacie!" << endl;
			return "";
		}
	}
}

/**
 * This function allows user to input string. It is used ONLY
 * when user input can be empty.
 * 
 * \param txt String that is displayed so user can know what to input
 * \return On success returns user's input
 */
string getStringEdit(string txt)
{
	string x;
	cout << "Podaj" << " " << txt << ": ";
	getline(cin, x);
	//cin.ignore();
	return x;
}

/**
 * This function allows for string input, with option to allow strings only with numbers or 
 * no numbers
 * 
 * \param txt String which is displayed to user
 * \param options 1- string without numbers, 0- string with numbers
 * \return On success returns string, on failure returns ""
 */
string getStringEdit(string txt, int options)
{
	string x;
	cout << "Podaj" << " " << txt << ": ";
	getline(cin, x);
	//cin.ignore();
	if (options == 1)
	{
		if (isSWN(x))
			return x;
		else
		{
			cout << "Podano dane w blednym formacie!" << endl;
			return "";
		}
	}

	if (options == 0)
	{
		if (isSWL(x))
			return x;
		else
		{
			cout << "Podano dane w blednym formacie!" << endl;
			return "";
		}
	}
}

/** 
 *
 * Generates 4 digits ID, that can be made from letters or numbers.
 * \param prefix This argument will be the first character of newly generated ID
 * \return On success returns generated ID
 */
string generateUniqueID(char prefix)
{
	int size = 3;
	char ID[100];
	char c;
	int nol;
	ID[0] = prefix;
	for (int i = 1; i <= size; i++)
	{
		if ((nol = rand() % 2 + 1 != 1))
		{
			c = rand()%10 + 48;
		}
		else
		{
			c = rand() % 26 + 65;
		}
		ID[i] = c;
	}
	size++;
	ID[size] = '\0';
	string text(ID);
	return text;
}

/**
 * Deletes all allocated memory from vectors
 * 
 * \param v Vector we want to deallocate
 */
template<class T> 
void purge(vector<T*> v) 
{
	for (auto item : v) 
		delete item;
	v.clear();
}

/**
 * This template displays all records from given vector of class pointers
 * 
 * \param v Vector<T*>, vector of pointers to objects
 */
template<class T>
void showAllRecords(vector<T*> v)
{
	for (auto item : v)
		item->info();
}

/**
 * .
 * This template allows all objects that are using vector of pointers to save it content to file.
 * \param v vector that contains pointers of objects
 * \param source name of file
 */
template<class T>
void saveAllRecords(vector<T*> v, string source)
{
	if (v.empty())
		return;
	ofstream source2{ source, ios::binary };
	source2.clear();
	v.back()->write(source2);
	v.pop_back();
	source2.close();
	ofstream source3{ source, ios::binary | ios::app };
	while (v.size() != 0)
	{
		v.back()->info();
		v.back()->write(source3);
		v.pop_back();
	}
	source3.close();
}

/**
 * .
 * This function clears screen.
 */
void cls() 
{
	system("CLS");
}

/**
 * .
 * This function checks user input parameters and changes options according to them.
 * \param argc number of starting parameters
 * \param argv array of starting parameters
 * \return if user inputs valid parameters function returns true, else false
 */
bool checkParameters(int argc, char* argv[])
{
	string t;
	if (argc > 3)
		return false;
	for (int i = 1; i < argc; i++)
	{
		t = argv[i];
		if (t == "-h")
		{
			cout << "-h pomoc" << endl;
			cout << "-nosave wylaczona mozliwosc zapisywania" << endl;
			cout << "-noedit wylaczona mozliwosc edycji ISTNIEJACYCH obiektow" << endl;
			cin >> t;
			exit(1);
		}

		else if (t == "-nosave")
			NOSAVE = true;

		else if (t == "-noedit")
			NOEDIT = true;
		else return false;
	}
	return true;
}

/**
 * Checks if string contains no numbers
 * 
 * \param txt String to check
 * \return True- string contains no numbers, otherwise false
 */
bool isSWN(string txt)
{
	int size = txt.size();
	int c;
	for (int i = 0; i < size; i++)
	{
		c = isalpha(txt[i]);
		if (c == 0)
			return false;
	}
	return true;
}

/**
 * Checks if string contains only numbers
 * 
 * \param txt String which we want to check
 * \return True if string contains no letters, false otherwise
 */
bool isSWL(string txt)
{
	int size = txt.size();
	int c;
	for (int i = 0; i < size; i++)
	{
		c = isalpha(txt[i]);
		if (c != 0)
			return false;
	}
	return true;
}
