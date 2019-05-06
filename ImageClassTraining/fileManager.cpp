#include "fileManager.h"


fileManager::fileManager(string classPath)
{
	vector<string> classFolders = listFiles(classPath + "\\");

	for (int i = 0; i < classFolders.size(); i++) {
		string cf = classFolders[i];
		vector<string> currentFolder = listFiles(classPath + "\\" + classFolders[i] + "\\");
		vector<string> currentFiles;
		for (int j = 0; j < currentFolder.size(); j++) {
			string w= "asd";
			currentFiles.push_back(classPath + "\\" + classFolders[i] + "\\" + currentFolder[j]);
		}
		classFiles.push_back(currentFiles);
	}

	
}


fileManager::~fileManager()
{
}


vector<string> fileManager::listFiles(string fullPath) {
	fullPath = fullPath + "*";
	vector <string> allFiles;
	LARGE_INTEGER filesize;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char path[160];
	strcpy_s(path, fullPath.c_str());
	hFind = FindFirstFile(path, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
	}
	else
	{
		printf(TEXT("The first file found is %s\n"), FindFileData.cFileName);
		//FindClose(hFind);
	}
	//get the second ".." file
	FindNextFile(hFind, &FindFileData);

	int i = 0;
	char istring[100];
	while (FindNextFile(hFind, &FindFileData) != 0) {
		sprintf_s(istring, "%d", i);
		//std::cout << " next is " << FindFileData.cFileName << "\n";
		string current = FindFileData.cFileName;
		allFiles.push_back(FindFileData.cFileName);
		i++;
	};
	FindClose(hFind);
	printf("\n\n");
	return allFiles;
}
