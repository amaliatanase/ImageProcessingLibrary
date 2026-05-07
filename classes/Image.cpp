#include "Image.h"
#include "Size.h"
#include  <iostream>
#include  <sstream>
#include  <fstream>
#include  <algorithm>

Image::Image(): m_data(nullptr), m_width(0), m_height(0) {}

Image::Image(unsigned int w, unsigned int h) {
    this->m_width = w;
    this->m_height = h;
    m_data = new unsigned char*[m_height];
    for (unsigned int i = 0; i < m_height; i++) {
        m_data[i] = new unsigned char[m_width];
        for (unsigned int j = 0; j < m_width; j++)
            m_data[i][j] = 0;
    }
}

Image::Image(const Image &other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_data = new unsigned char*[m_height];
    for (unsigned int i = 0; i < m_height; i++) {
        m_data[i] = new unsigned char[m_width];
        for (unsigned int j = 0; j < m_width; j++) {
            m_data[i][j] = other.m_data[i][j];
        }
    }
}

Image & Image::operator=(const Image &other) {
    if (this != &other) {
        release();
        m_width = other.m_width;
        m_height = other.m_height;
        m_data = new unsigned char*[m_height];
        for (unsigned int i = 0; i < m_height; i++) {
            m_data[i] = new unsigned char[m_width];
            for (unsigned int j = 0; j < m_width; j++)
                m_data[i][j] = other.m_data[i][j];
        }
    }
    return *this;
}

Image::~Image() {release();}

bool Image::load(std::string imagePath) {
    std::ifstream file(imagePath);
    if (!file.is_open()) return false;
    file >> *this;
    file.close();
    return true;
}

bool Image::save(std::string imagePath) const {
    std::ofstream file(imagePath);
    if (!file.is_open()) return false;
    file << *this;
    file.close();
    return true;
}

Image Image::operator+(const Image &i) {
    if (m_width != i.m_width || m_height != i.m_height)
        throw std::invalid_argument("Cannot add images with different sizes");

    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; y++)
        for (unsigned int x = 0; x < m_width; x++)
            result.m_data[y][x] = std::min(m_data[y][x] + i.m_data[y][x], 255);
    return result;
}

Image Image::operator-(const Image &i) {
    if (m_width != i.m_width || m_height != i.m_height)
        throw std::invalid_argument("Cannot subtract images with different sizes");

    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; y++)
        for (unsigned int x = 0; x < m_width; x++)
            result.m_data[y][x] = std::max((int)m_data[y][x] - (int)i.m_data[y][x], 0);
    return result;
}

Image Image::operator*(double s) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; y++)
        for (unsigned int x = 0; x < m_width; x++)
            result.m_data[y][x] = std::min((int)(m_data[y][x] * s),255);
    return result;
}

bool Image::getROI(Image &roiImg, Rectangle roiRect) {
    return getROI(roiImg, (unsigned int)roiRect.getX(), (unsigned int)roiRect.getY(), roiRect.getWidth(), roiRect.getHeight());
}

bool Image::getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    if (x + width > m_width || y + height > m_height || isEmpty())
        return false;
    roiImg.release();
    roiImg.m_width = width;
    roiImg.m_height = height;
    roiImg.m_data = new unsigned char*[height];
    for (unsigned int i = 0; i < height; i++) {
        roiImg.m_data[i] = new unsigned char[width];
        for (unsigned int j = 0; j < width; j++)
            roiImg.m_data[i][j] = m_data[y + i][x + j]; // copiem pixelii din zona specificata
    }
    return true;
}

bool Image::isEmpty() const {
    return m_data == nullptr && m_width == 0 && m_height == 0;
}

Size Image::size() const{ return Size(m_width, m_height); }

void Image::setWidth(unsigned int newWidth) {
    *this = Image(newWidth, m_height);
}

void Image::setHeight(unsigned int newHeight) {
    *this = Image(m_width, newHeight);
}

unsigned int Image::width() const { return m_width; }

unsigned int Image::height() const { return m_height; }

unsigned char & Image::at(unsigned int x, unsigned int y) {
    return m_data[y][x];
}

unsigned char Image::at(unsigned int x, unsigned int y) const {
    return m_data[y][x];
}


unsigned char & Image::at(Point pt) {
    return m_data[pt.getY()][pt.getX()];
}

unsigned char Image::at(Point pt) const {
    return m_data[pt.getY()][pt.getX()];
}

unsigned char * Image::row(int y) {
    return m_data[y];
}

void Image::release() {
    if (m_data != nullptr) {
        for (unsigned int i = 0; i < m_height; i++) {
            delete[] m_data[i];
        }
        delete[] m_data;
        m_data = nullptr;
        m_width = 0;
        m_height = 0;
    }
}

std::ostream& operator<<(std::ostream& os, const Image& dt) {
    os << "P2" << std::endl;
    os << "# Simple pgm image example" << std::endl;
    os << dt.m_width << " " << dt.m_height << std::endl;
    os << "255" << std::endl;
    for (unsigned int i = 0; i < dt.m_height; i++) {
        for (unsigned int j = 0; j < dt.m_width; j++) {
            os << (int)dt.m_data[i][j];
            if (j < dt.m_width - 1)
                os << " ";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Image& dt) {
    std::string line;
    std::getline(is, line); //P2

    std::getline(is, line); //ignore the comments
    while (line.empty() || line[0] == '#')
        std::getline(is, line);

    std::istringstream dims(line);
    unsigned int w, h;
    dims >> w >> h;

    int maxVal;
    is >> maxVal;

    dt.release();
    dt.m_width = w;
    dt.m_height = h;
    dt.m_data = new unsigned char*[h];
    for (unsigned int i = 0; i < h; i++) {
        dt.m_data[i] = new unsigned char[w];
        for (unsigned int j = 0; j < w; j++) {
            int pixel;
            is >> pixel;
            dt.m_data[i][j] = (unsigned char)pixel;
        }
    }
    return is;
}

Image Image::zeros(unsigned int width, unsigned int height) {
    return Image(width, height);
}

Image Image::ones(unsigned int width, unsigned int height) {
    Image image(width, height);
    for (unsigned int i = 0; i < height; i++)
        for (unsigned int j = 0; j < width; j++)
            image.m_data[i][j] = 1;
    return image;
}
