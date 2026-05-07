/**
 * @file Rectangle.h
 * @brief Definition of the Rectangle class which encapsulates a rectangular area.
 */
#pragma once
#include "Point.h"

/**
 * @class Rectangle
 * @brief Represents a rectangle defined by its top-left corner coordinates and its dimensions.
 */
class Rectangle {
public:
    /**
     * @brief Default constructor. Initializes a rectangle with 0 for all attributes.
     */
    Rectangle();

    /**
     * @brief Parameterized constructor.
     * @param x The X coordinate of the top-left corner.
     * @param y The Y coordinate of the top-left corner.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     */
    Rectangle(int x, int y, const unsigned int width, const unsigned int height);

    void setWidth(const unsigned int newWidth);
    void setHeight(const unsigned int newHeight);
    void setX(const int newX);
    void setY(const int newY);

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    int getX() const;
    int getY() const;

    /**
     * @brief Adds a Point to the rectangle, translating it by the point's coordinates.
     * @param point The point to add.
     * @return A new translated Rectangle.
     */
    Rectangle operator+(const Point &point) const;

    /**
     * @brief Subtracts a Point from the rectangle, translating it by the negative of the point's coordinates.
     * @param point The point to subtract.
     * @return A new translated Rectangle.
     */
    Rectangle operator-(const Point &point) const;

    /**
     * @brief Computes the intersection between two rectangles.
     * @param other The other rectangle to intersect with.
     * @return A new Rectangle representing the intersecting area, or a 0-dimension rectangle if they do not overlap.
     */
    Rectangle operator&(const Rectangle &other) const;

    /**
     * @brief Computes the union of two rectangles (the bounding box that covers both).
     * @param other The other rectangle.
     * @return A new Rectangle representing the bounding union.
     */
    Rectangle operator|(const Rectangle &other) const;

private:
    int x; ///< X coordinate of the top-left corner.
    int y; ///< Y coordinate of the top-left corner.
    unsigned int width; ///< Width of the rectangle.
    unsigned int height; ///< Height of the rectangle.
};