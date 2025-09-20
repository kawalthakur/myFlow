#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath> 

class Point {
protected:
    double x, y, z;

public: 
    Point(double x_ = 0.0, double y_ = 0.0, double z_ = 0.0);
    Point(std::vector<double>& coord);

    // This method should also be const as it doesn't modify this object
    double distance(const Point& B) const;

    // Getter functions - ADDED const HERE to match the implementation
    double X() const;
    double Y() const;
    double Z() const;
}
// --- Implementation ---

// Using a member initializer list is more standard and efficient
Point::Point(double x_, double y_, double z_) {
    this->x = x_;
    this->y = y_;
    this->z = z_;
}

Point::Point(std::vector<double>& coord){
    if(coord.size() < 3 ){
        throw std::runtime_error("Point needs atleast 3 coordinates ");
    }
    this->x = coord[0];
    this->y = coord[1];
    this->z = coord[2];
}

double Point::X() const {
    return this->x;
}

double Point::Y() const {
    return this->y;
}

double Point::Z() const {
    return this->z;
}

// The implementation of distance was also made const
double Point::distance(const Point& B) const {
    double dx = this->x - B.x;
    double dy = this->y - B.y;
    double dz = this->z - B.z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

#endif // POINT_H
