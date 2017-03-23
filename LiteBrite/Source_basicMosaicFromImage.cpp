#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "opencv2/imgcodecs.hpp"

using namespace cv;
using namespace std;



Mat getAverageColor(Mat& imageOriginal, int horizonal, int vertical, int width, int height)
{

	// Setup a rectangle to define your region of interest
	Rect myROI(horizonal, vertical, width, height);

	// Note that this doesn't copy the data
	Mat cropSpace = imageOriginal(myROI);

	// computes mean over roi
	Scalar avgPixelIntensity = cv::mean(cropSpace);

	// set RGB to avgPixelIntensity
	cropSpace.setTo(cv::Scalar(avgPixelIntensity.val[0], avgPixelIntensity.val[1], avgPixelIntensity.val[2]));

	return imageOriginal;
}

int main(int argc, char* argv[])
{
	char* imageName("waterfall_v01.jpg"); // by default
	if (argc > 1)
	{
		imageName = argv[1];
	}

	Mat imageOriginal;
	imageOriginal = imread(imageName, 1);

	// get image size
	int image_width = imageOriginal.cols;
	int image_height = imageOriginal.rows;

	// size of each lightbulb
	int adjustableSize = 20; // eventually let user determine size
	int lightbulbSize = image_width / adjustableSize;

	// crop off any remainting height
	int width_remainderPixels = image_width % lightbulbSize;
	int height_remainderPixels = image_height % lightbulbSize;
	Rect cropROI(0, 0, image_width - width_remainderPixels, image_height - height_remainderPixels);
	Mat croppedOriginal = imageOriginal(cropROI);

	// loop through image, changing lightbulb ROI's to their average color
	for (int row = 0; row < image_height - lightbulbSize; row += lightbulbSize){
		for (int col = 0; col < image_width - lightbulbSize; col += lightbulbSize){
			cout << "row is " << row << "\n";
			cout << "col is " << col << "\n";
			getAverageColor(croppedOriginal, col, row, lightbulbSize, lightbulbSize);
		}
	}

	namedWindow("original", CV_WINDOW_AUTOSIZE);
	imshow("original", croppedOriginal);

	cvWaitKey(0);

	return 0;
}
