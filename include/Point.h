#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath> 

class Point {
protected:
    double x, y, z;

public: 
    Point(double x_ = 0.0, double y_ = 0.0, double z_ = 0.0);

    // This method should also be const as it doesn't modify this object
    double distance(const Point& B) const;

    // Getter functions - ADDED const HERE to match the implementation
    double X() const;
    double Y() const;
    double Z() const;
};

// --- Implementation ---

// Using a member initializer list is more standard and efficient
inline Point::Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

inline double Point::X() const {
    return this->x;
}

inline double Point::Y() const {
    return this->y;
}

inline double Point::Z() const {
    return this->z;
}

// The implementation of distance was also made const
inline double Point::distance(const Point& B) const {
    double dx = this->x - B.x;
    double dy = this->y - B.y;
    double dz = this->z - B.z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

#endif // POINT_H