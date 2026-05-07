#include "Drawing.h"
#include <cmath>

namespace Drawing {
    void drawCircle(Image& img, Point center, int radius, unsigned char color) {
        //(x - cx)^2 + (y - cy)^2 = r^2
        for (unsigned int y = 0; y < img.height(); y++) {
            for (unsigned int x = 0; x < img.width(); x++) {
                int dx = (int)x - center.getX();
                int dy = (int)y - center.getY();
                if (abs(dx*dx + dy*dy - radius*radius) <= radius)
                    img.at(x, y) = color;
            }
        }
    }

    void drawLine(Image& img, Point p1, Point p2, unsigned char color) {
        int x1 = p1.getX(), y1 = p1.getY();
        int x2 = p2.getX(), y2 = p2.getY();
        //distance on x and y axis
        int dx = abs(x2 - x1), dy = abs(y2 - y1);
        //the direction
        int sx = x1 < x2 ? 1 : -1;
        int sy = y1 < y2 ? 1 : -1;
        int err = dx - dy;

        while (true) {
            if (x1 >= 0 && x1 < (int)img.width() && y1 >= 0 && y1 < (int)img.height())
                img.at(x1, y1) = color;
            if (x1 == x2 && y1 == y2) break;
            //where is the next pixel
            int e2 = 2 * err;
            //if the distance from the original line on y axis increased make a step horizontally
            if (e2 > -dy) { err -= dy; x1 += sx; }
            //if the distance from the original line on x axis increased make a step vertically
            if (e2 < dx)  { err += dx; y1 += sy; }
        }
    }

    void drawRectangle(Image& img, Rectangle r, unsigned char color) {
        drawRectangle(img,Point(r.getX(), r.getY()),Point(r.getX() + r.getWidth(), r.getY() + r.getHeight()), color);
    }

    void drawRectangle(Image& img, Point tl, Point br, unsigned char color) {
        //draw the 4 lines
        drawLine(img, tl, Point(br.getX(), tl.getY()), color); // up
        drawLine(img, Point(br.getX(), tl.getY()), br, color); // right
        drawLine(img, br, Point(tl.getX(), br.getY()), color); // down
        drawLine(img, Point(tl.getX(), br.getY()), tl, color); // left
    }
}