#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>

#include <string>
#include <sstream>
#include <fstream>

#include <vector>
using namespace std;

class fileManager
{
public:
	fileManager(string classPath);
	~fileManager();
	vector<vector<string>> classFiles;
private:
	vector<string> listFiles(string fullPath);
};

