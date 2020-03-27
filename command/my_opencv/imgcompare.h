#ifndef MY_IMG_COMPARE_H
#define MY_IMG_COMPARE_H

#include <QString>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
using namespace cv;

class imgcompare
{

public:
    explicit imgcompare();
    ~imgcompare();

private:
    bool compareFacesByHist(Mat img,Mat orgImg);
public:

    void compareImg(QString img1Path,QString img2Path);

};

#endif // MY_IMG_COMPARE_H
