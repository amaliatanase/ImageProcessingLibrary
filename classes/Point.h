/**
* @file Point.h
 * @brief Definition of the Point class to represent a point in a two-dimensional space.
 */
#pragma once

/**
 * @class Point
 * @brief Represents a 2D point with x and y coordinates.
 */
class Point {
public:
    /**
     * @brief Default constructor. Initializes the point to (0, 0).
     */
    Point();

    /**
     * @brief Parameterized constructor.
     * @param x The X coordinate.
     * @param y The Y coordinate.
     */
    Point(int x, int y);

    /**
     * @brief Gets the X coordinate.
     * @return The X coordinate.
     */
    int getX() const;

    /**
     * @brief Gets the Y coordinate.
     * @return The Y coordinate.
     */
    int getY() const;

    /**
     * @brief Sets the X coordinate.
     * @param x The new X coordinate.
     */
    void setX(int x);

    /**
     * @brief Sets the Y coordinate.
     * @param y The new Y coordinate.
     */
    void setY(int y);

private:
    int x; ///< The X coordinate of the point.
    int y; ///< The Y coordinate of the point.
};