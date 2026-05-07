#include "ImageProcessing.h"
#include "Image.h"
#include <cmath>
#include <algorithm>

BrightnessContrastAdjustment::BrightnessContrastAdjustment(): alpha(1.0), beta(0.0) {}

BrightnessContrastAdjustment::BrightnessContrastAdjustment(double alpha, double beta)
                                    : alpha(alpha), beta(beta) {}

void BrightnessContrastAdjustment::process(const Image &src, Image &dst) {
    dst = Image(src.width(), src.height());
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            double result = alpha * src.at(x,y) + beta;
            //if bigger than 255 => 255
            result = std::min(result, 255.0);
            //if smaller than 0 => 0
            result = std::max(result, 0.0);
            dst.at(x, y) = (unsigned char)result;
        }
    }
}

GammaCorrection::GammaCorrection(): gamma(1.0) {}

GammaCorrection::GammaCorrection(double gamma): gamma(gamma) {}

void GammaCorrection::process(const Image &src, Image &dst) {
    dst = Image(src.width(), src.height());
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            //normalize the value of the pixel (between 0 and 1)
            double normalized = src.at(x,y) / 255.0;
            double result = std::pow(normalized, gamma) * 255.0;
            //if bigger than 255 => 255
            result = std::min(result, 255.0);
            //if smaller than 0 => 0
            result = std::max(result, 0.0);
            dst.at(x,y) = (unsigned char)result;
        }
    }
}

//because we don't know the size of the kernel at initialization we need to use dynamic allocation
Convolution::Convolution(double **kernel, unsigned int kernelWidth, unsigned int kernelHeight,
    double(*scaleFunc)(double)): kernelWidth(kernelWidth), kernelHeight(kernelHeight), scaleFunc(scaleFunc) {
    //memory allocation for the kernel matrix
    this->kernel = new double*[kernelHeight];
    for (unsigned int i = 0; i < kernelHeight; ++i) {
        this->kernel[i] = new double[kernelWidth];
        for (unsigned int j = 0; j < kernelWidth; ++j)
            //copy the values from the kernel received as a parameter
            this->kernel[i][j] = kernel[i][j];
    }
}

Convolution::~Convolution() {
    if (kernel != nullptr) {
        for (unsigned int i = 0; i < kernelHeight; i++)
            delete[] kernel[i];
        delete[] kernel;
        kernel = nullptr;
    }
}

Convolution::Convolution(const Convolution &other): kernelWidth(other.kernelWidth), kernelHeight(other.kernelHeight), scaleFunc(other.scaleFunc) {
    kernel = new double*[kernelHeight];
    for (unsigned int i = 0; i < kernelHeight; i++) {
        kernel[i] = new double[kernelWidth];
        for (unsigned int j = 0; j < kernelWidth; j++)
            kernel[i][j] = other.kernel[i][j];
    }
}

Convolution & Convolution::operator=(const Convolution &other) {
    if (this != &other) {
        // free the old memory
        if (kernel != nullptr) {
            for (unsigned int i = 0; i < kernelHeight; i++)
                delete[] kernel[i];
            delete[] kernel;
        }
        kernelWidth = other.kernelWidth;
        kernelHeight = other.kernelHeight;
        scaleFunc = other.scaleFunc;
        kernel = new double*[kernelHeight];
        for (unsigned int i = 0; i < kernelHeight; i++) {
            kernel[i] = new double[kernelWidth];
            for (unsigned int j = 0; j < kernelWidth; j++)
                kernel[i][j] = other.kernel[i][j];
        }
    }
    return *this;
}

void Convolution::process(const Image &src, Image &dst) {
    dst = Image(src.width(), src.height());
    // k = how many neighbors one has in a given direction
    // compute the distance from the center of the kernel until its end
    int k = kernelWidth / 2;
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            //compute the sum for each pixel
            double sum = 0.0;
            for (unsigned int u = 0; u < kernelWidth; ++u) {
                for (unsigned int v = 0; v < kernelHeight; v++) {
                    //compute the coordinates of the neighbors
                    int srcX = (int)x - (int)u + k;
                    int srcY = (int)y - (int)v + k;
                    //verify that the neighbors is in the matrix
                    if (srcX >= 0 && srcX < (int)src.width() && srcY >= 0 && srcY < (int)src.height())
                        sum += kernel[v][u] * src.at(srcX, srcY);
                }
            }
            double result = scaleFunc(sum);
            result = std::min(result, 255.0);
            result = std::max(result, 0.0);
            dst.at(x, y) = (unsigned char)result;
        }
    }
}
// just multiply the convolution result to 1/9
double Convolution::meanScale(double val) { return val * (1.0 / 9.0); }

//just multiply the convolution result to 1/16.0
double Convolution::gaussianScale(double val) { return val * (1.0 / 16.0); }

// a linear mapping function that converts the range [-4*255, 4*255] to the range [0, 255].
double Convolution::sobelScale(double val) { return (val + 4 * 255) / (8.0 * 255) * 255.0; }



