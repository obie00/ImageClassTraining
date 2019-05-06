#include "ImageClassManager.h"



ImageClassManager::ImageClassManager(vector<vector<string>> classFilesList, int imgRow, int imgColumn)
{
	classFiles = classFilesList;
	row = imgRow;
	column = imgColumn;
	numOfClasses = classFiles.size();
}


ImageClassManager::~ImageClassManager()
{
}

void ImageClassManager::trainClasses()
{
	for (int i = 0; i < classFiles.size(); i++) {
		Mat emptyClass = Mat::zeros(row, column, 0);

		for (int j = 0; j < classFiles[i].size(); j++) {
			Mat img = imread(classFiles[i][j]);
			
			img = optimizeImage(img);
			for (int k = 0; k < img.rows; k++) {
				for (int l = 0; l < img.cols; l++) {
					int pixel = img.at<uchar>(k, l);
					if (pixel == 0) {
						emptyClass.at<uchar>(k, l) = emptyClass.at<uchar>(k, l) + 1;
					}
				}
			}
			//cout << emptyClass;
		}
		//cout << emptyClass;
		classifiers.push_back(emptyClass);
		Mat trainedClass;
		//cvtColor(emptyClass, trainedClass, CV_BGR2GRAY);
		/*threshold(emptyClass, trainedClass, 3, 255, 0);
		imshow("dtrainedCLass", trainedClass);
		cvWaitKey(0);
		cvDestroyAllWindows();*/
		
	}
}

Mat ImageClassManager::optimizeImage(Mat img)
{
	int myThresh[255] = { 0 };
	Mat src_opt;
	Mat src_gry;
	cvtColor(img, src_gry, CV_BGR2GRAY);
	threshold(src_gry, src_opt, 122, 255, 0);
	//src_opt = src_opt + Mat::ones(90, 142, 0);
	//src_opt.at<uchar>(89, 141) = 300;
	//imshow("img", img);
	/*imshow("gry", src_gry);
	imshow("opt", src_opt);
	cvWaitKey(0);
	cvDestroyAllWindows();*/
	return src_opt;
}

int ImageClassManager::testClasses(string imgPath)
{
	Mat img = imread(imgPath);
	img = optimizeImage(img);
	
	vector<int> precision;

	int chosenClass=-1;
	double maxClassProbabilty = 0;
	int bestPrecision = 0;
	for (int i = 0; i < classifiers.size(); i++) {
		double currentClassProbabilty = 1;
		int currentPrecision = 0;
		for (int j = 0; j < img.rows; j++) {
			for (int k = 0; k < img.cols; k++) {
				double currentClassPix = double(classifiers[i].at<uchar>(j, k) + 1);
				double pixelAverage = currentClassPix/double(36);
				int imgPixel = img.at<uchar>(j, k);
				if (imgPixel == 0) {
					currentClassProbabilty = currentClassProbabilty * pixelAverage;
				}
				else {
					currentClassProbabilty = currentClassProbabilty * (1-pixelAverage);
				}
			}
			if (currentClassProbabilty < 6.2107058365249902e-200) {
				currentPrecision = currentPrecision + 1;
				currentClassProbabilty = currentClassProbabilty * 10e199;
			}
		}
		if ((currentPrecision < bestPrecision) || (bestPrecision == 0)) {
			maxClassProbabilty = currentClassProbabilty;
			bestPrecision = currentPrecision;
			chosenClass = i;
		}
		if (currentPrecision == bestPrecision) {
			if (currentClassProbabilty > maxClassProbabilty) {
				maxClassProbabilty = currentClassProbabilty;
				bestPrecision = currentPrecision;
				chosenClass = i;
			}
		}
		/*if (currentClassProbabilty > maxClassProbabilty) {
			if ((currentPrecision == bestPrecision)||(bestPrecision==0)) {
				maxClassProbabilty = currentClassProbabilty;
				bestPrecision = currentPrecision;
				chosenClass = i;
			}
			else {

			}
		}*/
	}
	return chosenClass;
}
