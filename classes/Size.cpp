#include "Size.h"

Size::Size(): width(0), height(0) {}

Size::Size(const unsigned int width, const unsigned int height)
    : width(width), height(height) {}

unsigned int Size::getWidth() const {return width;}

unsigned int Size::getHeight() const {return height;}

void Size::setWidth(const unsigned int newWidth) {width = newWidth;}

void Size::setHeight(const unsigned int newHeight) {height = newHeight;}

bool Size::operator==(const Size &other) const {
    return other.getWidth() * other.getHeight() == width * height;
}

bool Size::operator<(const Size &other) const {
    return width * height < other.getWidth() * other.getHeight();
}

bool Size::operator<=(const Size &other) const {
    return (*this < other) || (*this == other);
}

bool Size::operator>(const Size &other) const {
    return other < *this;
}

bool Size::operator>=(const Size &other) const {
    return (*this > other) || (*this == other);
}
