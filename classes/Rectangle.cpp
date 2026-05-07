#include "Rectangle.h"
#include "Point.h"

Rectangle::Rectangle(): x(0), y(0), width(0), height(0) {}

Rectangle::Rectangle(int x, int y, const unsigned int width, const unsigned int height)
    : x(x), y(y), width(width), height(height) {}

void Rectangle::setWidth(const unsigned int newWidth) { width = newWidth; }

void Rectangle::setHeight(const unsigned int newHeight) { height = newHeight; }

void Rectangle::setX(const int newX) { x = newX; }

void Rectangle::setY(const int newY) { y = newY; }

unsigned int Rectangle::getWidth() const { return width; }

unsigned int Rectangle::getHeight() const { return height; }

int Rectangle::getX() const { return x; }

int Rectangle::getY() const { return y; }

Rectangle Rectangle::operator+(const Point &point) const {
    return Rectangle(x + point.getX(), y + point.getY(), width, height);
}

Rectangle Rectangle::operator-(const Point &point) const {
    return Rectangle(x - point.getX(), y - point.getY(), width, height);
}

Rectangle Rectangle::operator&(const Rectangle &other) const {
    int newX = x > other.x ? x : other.x;
    int newY = y > other.y ? y : other.y;
    int newRight = (x + width) < (other.x + other.width) ? (x + width) : (other.x + other.width);
    int newBottom = (y + height) < (other.y + other.height) ? (y + height) : (other.y + other.height);

    if (newRight <= newX || newBottom <= newY)
        return Rectangle(0, 0 , 0, 0);
    return Rectangle(newX, newY, newRight - newX, newBottom - newY);
}

Rectangle Rectangle::operator|(const Rectangle &other) const {
    int newX = x < other.x ? x : other.x;
    int newY = y < other.y ? y : other.y;
    int newRight = (x + width) > (other.x + other.width) ? (x + width) : (other.x + other.width);
    int newBottom = (y + height) > (other.y + other.height) ? (y + height) : (other.y + other.height);

    return Rectangle(newX, newY, newRight - newX, newBottom - newY);
}
