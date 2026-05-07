/**
* @file Drawing.h
 * @brief Module for drawing basic geometric shapes over images.
 */
#pragma once
#include "Image.h"
#include "Point.h"
#include "Rectangle.h"

/**
 * @namespace Drawing
 * @brief Groups utility functions for rasterizing geometric shapes.
 */
namespace Drawing {
    /**
     * @brief Draws a circle on the image.
     * @param img The image to draw on.
     * @param center The central point of the circle.
     * @param radius The radius of the circle.
     * @param color The drawing color (0-255).
     */
    void drawCircle(Image& img, Point center, int radius, unsigned char color);

    /**
     * @brief Draws a line between two points using Bresenham's line algorithm.
     * @param img The image to draw on.
     * @param p1 The starting point.
     * @param p2 The ending point.
     * @param color The color of the line.
     */
    void drawLine(Image& img, Point p1, Point p2, unsigned char color);

    /**
     * @brief Draws a rectangle based on a Rectangle object.
     * @param img The image to draw on.
     * @param r The Rectangle object defining the position and size.
     * @param color The color of the rectangle outline.
     */
    void drawRectangle(Image& img, Rectangle r, unsigned char color);

    /**
     * @brief Draws a rectangle using top-left and bottom-right points.
     * @param img The image to draw on.
     * @param tl The top-left corner point.
     * @param br The bottom-right corner point.
     * @param color The color of the rectangle outline.
     */
    void drawRectangle(Image& img, Point tl, Point br, unsigned char color);
}