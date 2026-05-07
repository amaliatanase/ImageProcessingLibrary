/**
 * @file Size.h
 * @brief Definition of the Size class that encapsulates the dimensions of an object.
 */
#pragma once

/**
 * @class Size
 * @brief Represents the size of an object using width and height.
 * * Comparisons between Size objects are made based on their total area.
 */
class Size {
public:
    /**
     * @brief Default constructor. Initializes dimensions to 0.
     */
    Size();

    /**
     * @brief Parameterized constructor.
     * @param width The width dimension.
     * @param height The height dimension.
     */
    Size(const unsigned int width, const unsigned int height);

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void setWidth(const unsigned int width);
    void setHeight(const unsigned int height);

    /**
     * @brief Compares if two sizes have an equal area.
     * @param other The Size to compare with.
     * @return True if areas are equal, False otherwise.
     */
    bool operator==(const Size &other) const;

    /**
     * @brief Checks if the current area is strictly less than the other area.
     * @param other The Size to compare with.
     * @return True if this area is smaller, False otherwise.
     */
    bool operator<(const Size &other) const;

    /**
     * @brief Checks if the current area is less than or equal to the other area.
     * @param other The Size to compare with.
     * @return True if this area is smaller or equal, False otherwise.
     */
    bool operator<=(const Size &other) const;

    /**
     * @brief Checks if the current area is strictly greater than the other area.
     * @param other The Size to compare with.
     * @return True if this area is larger, False otherwise.
     */
    bool operator>(const Size &other) const;

    /**
     * @brief Checks if the current area is greater than or equal to the other area.
     * @param other The Size to compare with.
     * @return True if this area is larger or equal, False otherwise.
     */
    bool operator>=(const Size &other) const;

private:
    unsigned int width; ///< The width dimension.
    unsigned int height; ///< The height dimension.
};