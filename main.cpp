#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void imshowMany(const std::string& _winName, const vector<Mat>& _imgs, VideoWriter& v)
{
 int nImg = (int)_imgs.size();

 Mat dispImg;
 int size;
 int x, y;
 // w - Maximum number of images in a row
 // h - Maximum number of images in a column
 int w, h;
 // scale - How much we have to resize the image
 float scale;
 int max;
 if (nImg <= 0)
 {
  printf("Number of arguments too small....\n");
  return;
 }
 else if (nImg > 12)
 {
  printf("Number of arguments too large....\n");
  return;
 }

 else if (nImg == 1)
 {
  w = h = 1;
  size = 300;
 }
 else if (nImg == 2)
 {
  w = 2; h = 1;
  size = 600;
 }
 else if (nImg == 3)
 {
  w = 3; h = 1;
  size = 600;
 }
 else if (nImg == 4)
 {
	 w = 2; h = 2;
	 size = 300;
 }
 else if (nImg == 5 || nImg == 6)
 {
  w = 3; h = 2;
  size = 200;
 }
 else if (nImg == 7 || nImg == 8)
 {
  w = 4; h = 2;
  size = 200;
 }
 else
 {
  w = 4; h = 3;
  size = 150;
 }

 dispImg.create(Size((1*w +1 + size*w), (1*h +1 + size/5*3*h)), CV_8UC3);
 cout << dispImg.size()<< endl;
 for (int i= 0, m=1, n=1; i<nImg; i++, m+=(1+size))
 {
  x = _imgs[i].cols;
  y = _imgs[i].rows;
  max = (x > y)? x: y;
  scale = (float) ( (float) max / size );
  if (i%w==0 && m!=1)
  {
   m = 1;
   n += 1+size/5*3;
  }

  Mat imgROI = dispImg(Rect(m, n, (int)(x/scale), (int)(y/scale)));
  resize(_imgs[i], imgROI, Size((int)(x/scale), (int)(y/scale)));
 }
 v<<dispImg;
 namedWindow(_winName);
 imshow(_winName, dispImg);
}

int main()
{
	VideoCapture capture1("/home/gaoqi/Downloads/bird/ipm_code/build/1.avi");
	VideoCapture capture2("/home/gaoqi/Downloads/bird/ipm_code/build/2.avi");
	VideoCapture capture3("/home/gaoqi/Downloads/bird/ipm_code/build/3.avi");
	VideoWriter writer("bird.avi", CV_FOURCC('M', 'J', 'P', 'G'), 15.0, Size(1804, 362));

	Mat img1,img2,img3;
	vector<Mat> img;
	while(capture1.read(img1)&&capture2.read(img2)&&capture3.read(img3)){
		img.push_back(img1);
		img.push_back(img2);
		img.push_back(img3);
		imshowMany("bird",img,writer);
		waitKey(1);
		img.clear();
	}
	return 0;
}
