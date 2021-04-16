#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

using namespace std;
using namespace cv;

static IplImage *ipl_img = NULL;

Mat createBGR(unsigned char *rData, unsigned char *gData, unsigned char *bData, unsigned int dimX, unsigned int dimY)
{
	Mat outputMat;

	Mat channelR = Mat(dimY, dimX, CV_8UC1, rData).clone();
	Mat channelG = Mat(dimY, dimX, CV_8UC1, gData).clone();
	Mat channelB = Mat(dimY, dimX, CV_8UC1, bData).clone();

	vector<Mat> channels = {channelB, channelG, channelR};
	merge(channels, outputMat);

	return outputMat;
}

Mat hconcatRGB(unsigned char *rData, unsigned char *gData, unsigned char *bData, unsigned int dimX, unsigned int dimY)
{
	Mat outputMat;

	Mat channelRR = Mat(dimY, dimX, CV_8UC1, rData).clone();
	Mat channelRG = Mat(dimY, dimX, CV_8UC1, char(0)).clone();
	Mat channelRB = Mat(dimY, dimX, CV_8UC1, char(0)).clone();
	Mat channelR;
	vector<Mat> r_channels = {channelRB, channelRG, channelRR};
	merge(r_channels, channelR);

	Mat channelGR = Mat(dimY, dimX, CV_8UC1, char(0)).clone();
	Mat channelGG = Mat(dimY, dimX, CV_8UC1, gData).clone();
	Mat channelGB = Mat(dimY, dimX, CV_8UC1, char(0)).clone();
	Mat channelG;
	vector<Mat> g_channels = {channelGB, channelGG, channelGR};
	merge(g_channels, channelG);

	Mat channelBR = Mat(dimY, dimX, CV_8UC1, char(0)).clone();
	Mat channelBG = Mat(dimY, dimX, CV_8UC1, char(0)).clone();
	Mat channelBB = Mat(dimY, dimX, CV_8UC1, bData).clone();
	Mat channelB;
	vector<Mat> b_channels = {channelBB, channelBG, channelBR};
	merge(b_channels, channelB);

	vector<Mat> channels = {channelB, channelG, channelR};
	hconcat(channels, outputMat);

	return outputMat;
}

int main(int argc, char *argv[])
{
	DicomImage *r_img = new DicomImage("test.dcm");
	DicomImage *g_img = new DicomImage("test.dcm");
	DicomImage *b_img = new DicomImage("test.dcm");
	unsigned int nRows = r_img->getHeight();
	unsigned int nCols = r_img->getWidth();
	

	b_img->setWindow(-744, 512);
	Uint8 *blueData = (Uint8 *)(b_img->getOutputData(8));
	// Mat b_mat = Mat(nRows, nCols, CV_8UC1, blueData).clone();
	// imwrite("test_b.png", b_mat);

	g_img->setWindow(-232, 512);
	Uint8 *greenData = (Uint8 *)(g_img->getOutputData(8));
	// Mat g_mat = Mat(nRows, nCols, CV_8UC1, greenData).clone();
	// imwrite("test_g.png", g_mat);

	r_img->setWindow(280, 512);
	Uint8 *redData = (Uint8 *)(r_img->getOutputData(8));
	// Mat r_mat = Mat(nRows, nCols, CV_8UC1, redData).clone();
	// imwrite("test_r.png", r_mat);

	Mat rgb_concat = hconcatRGB(redData, greenData, blueData, nRows, nCols);
	imwrite("test.png", rgb_concat);

	cout << "Concatenation RGB" << endl;
	cout << rgb_concat.size() << endl;
	cout << rgb_concat.channels() << endl;

	// Mat rgb_out = createBGR(redData, greenData, blueData, nRows, nCols);
	// imwrite("test_rgb_merge.png", rgb_out);

	// cout << "Merged RGB" << endl;
	// cout << rgb_out.size() << endl;
	// cout << rgb_out.channels() << endl;

	return 0;
}
