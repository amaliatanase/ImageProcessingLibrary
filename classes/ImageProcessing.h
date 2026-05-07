/**
 * @file ImageProcessing.h
 * @brief Contains classes for image processing operations (filters, adjustments).
 */
#pragma once
#include "Image.h"

/**
 * @class ImageProcessing
 * @brief Base interface for all image processing operations.
 */
class ImageProcessing {
public:
    /**
     * @brief Pure virtual method for applying the processing operation.
     * @param src The source image (input).
     * @param dst The destination image (output).
     */
    virtual void process(const Image& src, Image& dst) = 0;

    /** @brief Virtual destructor. */
    virtual ~ImageProcessing() = default;
};

/**
 * @class BrightnessContrastAdjustment
 * @brief Adjusts the brightness and contrast of an image using the formula: dst = alpha * src + beta.
 */
class BrightnessContrastAdjustment : public ImageProcessing {
public:
    /** @brief Default constructor (alpha = 1.0, beta = 0.0 - no operation). */
    BrightnessContrastAdjustment();

    /**
     * @brief Parameterized constructor.
     * @param alpha The contrast factor (gain).
     * @param beta The brightness factor (bias).
     */
    BrightnessContrastAdjustment(double alpha, double beta);

    /** @brief Applies brightness and contrast adjustment to the source image. */
    void process(const Image& src, Image& dst) override;

private:
    double alpha; ///< Contrast factor.
    double beta;  ///< Brightness factor.
};

/**
 * @class GammaCorrection
 * @brief Applies gamma correction to non-linearly adjust overall brightness.
 */
class GammaCorrection : public ImageProcessing {
public:
    /** @brief Default constructor (gamma = 1.0 - no operation). */
    GammaCorrection();

    /**
     * @brief Parameterized constructor.
     * @param gamma The gamma encoding factor.
     */
    GammaCorrection(double gamma);

    /** @brief Applies gamma correction to the source image. */
    void process(const Image& src, Image& dst) override;

private:
    double gamma; ///< Gamma encoding factor.
};

/**
 * @class Convolution
 * @brief Applies spatial filters based on convolution kernels (e.g., Blur, Sobel).
 */
class Convolution : public ImageProcessing {
public:
    /** @brief Default constructor. */
    Convolution() = default;

    /**
     * @brief Parameterized constructor.
     * @param kernel The convolution kernel matrix.
     * @param kernelWidth The width of the kernel.
     * @param kernelHeight The height of the kernel.
     * @param scaleFunc Pointer to a function used to scale the result to [0, 255].
     */
    Convolution(double** kernel, unsigned int kernelWidth, unsigned int kernelHeight, double (*scaleFunc)(double));

    /** @brief Destructor. Releases dynamically allocated kernel memory. */
    ~Convolution();

    /** @brief Copy constructor. @param other The source Convolution to copy. */
    Convolution(const Convolution& other);

    /** @brief Assignment operator. @param other The source Convolution. @return Reference to this. */
    Convolution& operator=(const Convolution& other);

    /** @brief Applies the convolution kernel to the source image. */
    void process(const Image& src, Image& dst) override;

    /** @brief Scaling function for mean blur (multiplies by 1/9). @param val The convolution result. @return Scaled value. */
    static double meanScale(double val);

    /** @brief Scaling function for Gaussian blur (multiplies by 1/16). @param val The convolution result. @return Scaled value. */
    static double gaussianScale(double val);

    /** @brief Scaling function for Sobel (maps [-4*255, 4*255] to [0, 255]). @param val The convolution result. @return Scaled value. */
    static double sobelScale(double val);

private:
    double** kernel = nullptr;       ///< Dynamically allocated convolution kernel.
    unsigned int kernelWidth = 0;    ///< Width of the kernel.
    unsigned int kernelHeight = 0;   ///< Height of the kernel.
    double (*scaleFunc)(double) = nullptr; ///< Pointer to the scaling function.
};