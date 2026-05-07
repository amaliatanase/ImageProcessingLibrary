/**
* @file Image.h
 * @brief Definition of the Image class for representing and manipulating grayscale images.
 */
#pragma once
#include "Rectangle.h"
#include "Size.h"
#include <string>

/**
 * @class Image
 * @brief Manages a grayscale image (pixel values between 0 and 255).
 * * This class uses dynamic memory allocation to store the 2D pixel matrix and
 * implements the Rule of Three (destructor, copy constructor, assignment operator)
 * for proper memory management.
 */
class Image{
public:
    /**
     * @brief Default constructor. Initializes an empty image (0x0).
     */
    Image();

    /**
     * @brief Parameterized constructor.
     * @param w The width of the image.
     * @param h The height of the image.
     */
    Image(unsigned int w, unsigned int h);

    /**
     * @brief Copy constructor.
     * @param other The source image to be copied.
     */
    Image(const Image &other);

    /**
     * @brief Assignment operator.
     * @param other The source image.
     * @return Reference to the current image.
     */
    Image& operator=(const Image &other);

    /**
     * @brief Destructor. Releases dynamically allocated memory.
     */
    ~Image();

    /**
     * @brief Loads an image from the filesystem in PGM format.
     * @param imagePath The path to the image file.
     * @return True if the operation was successful, False otherwise.
     */
    bool load(std::string imagePath);

    /**
     * @brief Saves the current image to the filesystem in PGM format.
     * @param imagePath The path and name of the output file.
     * @return True if the operation was successful, False otherwise.
     */
    bool save(std::string imagePath) const;

    /**
     * @brief Performs pixel-wise addition of two images.
     * @param i The image to be added.
     * @return A new Image representing the sum (values clamped to 255).
     */
    Image operator+(const Image &i);

    /**
     * @brief Performs pixel-wise subtraction of two images.
     * @param i The image to be subtracted.
     * @return A new Image representing the difference (values clamped to 0).
     */
    Image operator-(const Image &i);

    /**
     * @brief Multiplies all image pixels by a scalar value.
     * @param s The scalar value.
     * @return A new resulting Image.
     */
    Image operator*(double s);

    /**
     * @brief Extracts a Region of Interest (ROI) based on a Rectangle object.
     * @param roiImg The destination image where the ROI will be stored.
     * @param roiRect The rectangle defining the extraction area.
     * @return True if extraction succeeds, False if the area is out of bounds.
     */
    bool getROI(Image &roiImg, Rectangle roiRect);

    /**
     * @brief Extracts a Region of Interest (ROI) based on coordinates.
     * @param roiImg The destination image.
     * @param x The X coordinate of the top-left corner.
     * @param y The Y coordinate of the top-left corner.
     * @param width The width of the area.
     * @param height The height of the area.
     * @return True if extraction succeeds, False otherwise.
     */
    bool getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    /**
     * @brief Checks if the image is empty (no allocated data).
     * @return True if empty, False otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Returns the dimensions of the image.
     * @return A Size object containing the width and height.
     */
    Size size() const;

    /** @brief Sets the width of the image. @param newWidth The new width. */
    void setWidth(unsigned int newWidth);
    /** @brief Sets the height of the image. @param newHeight The new height. */
    void setHeight(unsigned int newHeight);

    /** @brief Returns the width of the image. @return The width in pixels. */
    unsigned int width() const;
    /** @brief Returns the height of the image. @return The height in pixels. */
    unsigned int height() const;

    /**
     * @brief Accesses a pixel by reference to modify it.
     * @param x The X coordinate (column).
     * @param y The Y coordinate (row).
     * @return Reference to the pixel value.
     */
    unsigned char& at(unsigned int x, unsigned int y);
    /// @overload
    unsigned char at(unsigned int x, unsigned int y) const;

    /// @overload
    unsigned char& at(Point pt);
    /// @overload
    unsigned char at(Point pt) const;

    /**
     * @brief Returns a pointer to the beginning of a specified row.
     * @param y The row index.
     * @return Pointer to the row data.
     */
    unsigned char* row(int y);

    /**
     * @brief Releases allocated memory and resets dimensions to 0.
     */
    void release();

    /** @brief Writes the image in PGM format to an output stream. */
    friend std::ostream& operator<<(std::ostream& os, const Image& dt);
    /** @brief Reads an image in PGM format from an input stream. */
    friend std::istream& operator>>(std::istream& is, Image& dt);

    /**
     * @brief Factory method that creates an image with all pixels set to 0 (black).
     * @param width The width of the image.
     * @param height The height of the image.
     * @return The generated image.
     */
    static Image zeros(unsigned int width, unsigned int height);

    /**
     * @brief Factory method that creates an image with all pixels set to 1.
     * @param width The width of the image.
     * @param height The height of the image.
     * @return The generated image.
     */
    static Image ones(unsigned int width, unsigned int height);

private:
    unsigned char** m_data; ///< Dynamically allocated 2D pixel matrix.
    unsigned int m_width;   ///< The width of the image.
    unsigned int m_height;  ///< The height of the image.
};