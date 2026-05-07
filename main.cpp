#include <iostream>
#include "classes/Image.h"
#include "classes/ImageProcessing.h"
#include "classes/Drawing.h"

int main() {
    Image img;
    if (!img.load("/Users/amaliatanase/CLionProjects/ImageProcessing/mona_lisa.ascii.pgm")) {
        std::cout << "Failed to load image!" << std::endl;
        return -1;
    }

    Image dst1;
    BrightnessContrastAdjustment bca(1.5, 30);
    bca.process(img, dst1);
    dst1.save("/Users/amaliatanase/CLionProjects/ImageProcessing/brightness.pgm");

    Image dst2;
    GammaCorrection gc(0.5);
    gc.process(img, dst2);
    dst2.save("/Users/amaliatanase/CLionProjects/ImageProcessing/gamma.pgm");

    //Mean blur
    double** meanKernel = new double*[3];
    for (int i = 0; i < 3; i++) {
        meanKernel[i] = new double[3];
        for (int j = 0; j < 3; j++)
            meanKernel[i][j] = 1.0;
    }
    Image dst3;
    Convolution meanBlur(meanKernel, 3, 3, Convolution::meanScale);
    meanBlur.process(img, dst3);
    dst3.save("/Users/amaliatanase/CLionProjects/ImageProcessing/blur.pgm");
    for (int i = 0; i < 3; i++) delete[] meanKernel[i];
    delete[] meanKernel;

    //Gaussian blur
    double** gaussKernel = new double*[3];
    gaussKernel[0] = new double[3]{1, 2, 1};
    gaussKernel[1] = new double[3]{2, 4, 2};
    gaussKernel[2] = new double[3]{1, 2, 1};
    Image dst4;
    Convolution gaussBlur(gaussKernel, 3, 3, Convolution::gaussianScale);
    gaussBlur.process(img, dst4);
    dst4.save("/Users/amaliatanase/CLionProjects/ImageProcessing/gaussian.pgm");
    for (int i = 0; i < 3; i++) delete[] gaussKernel[i];
    delete[] gaussKernel;

    //Sobel horizontal
    double** sobelHKernel = new double*[3];
    sobelHKernel[0] = new double[3]{1, 2, 1};
    sobelHKernel[1] = new double[3]{0, 0, 0};
    sobelHKernel[2] = new double[3]{-1, -2, -1};
    Image dst5;
    Convolution sobelH(sobelHKernel, 3, 3, Convolution::sobelScale);
    sobelH.process(img, dst5);
    dst5.save("/Users/amaliatanase/CLionProjects/ImageProcessing/sobel_h.pgm");
    for (int i = 0; i < 3; i++) delete[] sobelHKernel[i];
    delete[] sobelHKernel;

    //Sobel vertical
    double** sobelVKernel = new double*[3];
    sobelVKernel[0] = new double[3]{-1, 0, 1};
    sobelVKernel[1] = new double[3]{-2, 0, 2};
    sobelVKernel[2] = new double[3]{-1, 0, 1};
    Image dst6;
    Convolution sobelV(sobelVKernel, 3, 3, Convolution::sobelScale);
    sobelV.process(img, dst6);
    dst6.save("/Users/amaliatanase/CLionProjects/ImageProcessing/sobel_v.pgm");
    for (int i = 0; i < 3; i++) delete[] sobelVKernel[i];
    delete[] sobelVKernel;

    //extract a ROI from the original picture
    Image roi;
    Rectangle roiRect(-50, 30, 100, 100);
    img.getROI(roi, roiRect);
    roi.save("/Users/amaliatanase/CLionProjects/ImageProcessing/roi.pgm");

    //draw on the original image the rectangle which marks the ROI
    Drawing::drawRectangle(img, roiRect, 255);
    Drawing::drawCircle(img, Point(90, 80), 10, 0);
    img.save("/Users/amaliatanase/CLionProjects/ImageProcessing/drawing.pgm");

    Image img2;
    if (!img2.load("/Users/amaliatanase/CLionProjects/ImageProcessing/venus1.ascii.pgm")) {
        std::cout << "Failed to load image!" << std::endl;
        return -1;
    }

    Image dst7;
    BrightnessContrastAdjustment bca2(1.5, 30);
    bca2.process(img2, dst7);
    dst7.save("/Users/amaliatanase/CLionProjects/ImageProcessing/brightness_venus.pgm");

    std::cout << "Done! All images saved." << std::endl;

    return 0;
}