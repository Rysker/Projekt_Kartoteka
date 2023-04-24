#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <typeinfo>
#include <random>

using namespace std;

int getInt(string txt);
string getString(string txt);
string getStringEdit(string txt);
string getString(string txt, int options);
string getStringEdit(string txt, int options);
bool isSWN(string txt);
bool isSWL(string txt);
string generateUniqueID(char prefix);
bool checkParameters(int argc, char* argv[]);
void cls();

template<class T>
void purge(vector<T*> v);

template<class T>
void showAllRecords(vector<T*> v);

template<class T>
void saveAllRecords(vector<T*> v, string source);

