#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "fileManager.h"
#include "ImageClassManager.h"
using namespace cv;

int main()
{
	std::cout << "I am Ironman!\n";
	//imread("C:\\Users\\omoob\\Desktop\\TTTtraining\\trainO\\imO" + std::to_string(i+27) + ".png");

	fileManager FilesManager = fileManager("C:\\Users\\omoob\\Desktop\\TTTtraining");
	ImageClassManager imageClassManager = ImageClassManager(FilesManager.classFiles, 110, 150);
	imageClassManager.trainClasses();
	/*for (int i = 0; i < 36; i++) {
		int ans = imageClassManager.testClasses("C:\\Users\\omoob\\Desktop\\TTTtraining\\trainO\\imO" + to_string(i) + ".png");
		cout << "test" << i << "is: " << ans << "\n";
	}*/
	Mat class1 = imageClassManager.classifiers[0];
	imwrite("C:\\Users\\omoob\\Desktop\\trainedClass\\classO.png", class1);
	imwrite("C:\\Users\\omoob\\Desktop\\trainedClass\\class1.png", imageClassManager.classifiers[1]);
	return 0;
}
