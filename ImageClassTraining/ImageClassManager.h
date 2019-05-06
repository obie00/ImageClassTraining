#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
class ImageClassManager
{
public:
	ImageClassManager(vector<vector<string>> classFilesList, int imgRow, int imgColumn);
	~ImageClassManager();
	void trainClasses();
	int testClasses(string imgPath);
	vector<Mat> classifiers;
private:
	vector<vector<string>> classFiles;
	
	int row;
	int column;
	int numOfClasses;
	Mat optimizeImage(Mat img);
};

