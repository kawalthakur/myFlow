#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "Point.h" // Include the base class header

class Vector : public Point {
public: 
    // CORRECTED CONSTRUCTOR: Calls the base class and has an empty body {}.
    Vector(double x_ = 0.0, double y_ = 0.0, double z_ = 0.0) : Point(x_, y_, z_) {}

    // Operator overloads for vector math
    Vector operator+(const Vector& B) const;
    Vector operator-(const Vector& B) const;
    Vector operator^(const Vector& B) const; // Cross product
    double operator*(const Vector& B) const;   // Dot product

    // Friend function for printing
    friend std::ostream& operator<<(std::ostream& os, const Vector& A);
};

// --- Implementation ---

inline std::ostream& operator<<(std::ostream& os, const Vector& A) {
    // Uses the public X(), Y(), Z() methods inherited from Point
    os << "(" << A.X() << ", " << A.Y() << ", " << A.Z() << ")"; 
    return os;
}

inline Vector Vector::operator+(const Vector& B) const {
    return Vector(this->x + B.x, this->y + B.y, this->z + B.z);
}

inline Vector Vector::operator-(const Vector& B) const {
    return Vector(this->x - B.x, this->y - B.y, this->z - B.z);
}

inline Vector Vector::operator^(const Vector& B) const {
    // Cross product
    return Vector(this->y * B.z - this->z * B.y,
                  this->z * B.x - this->x * B.z,
                  this->x * B.y - this->y * B.x);
}

inline double Vector::operator*(const Vector& B) const {
    // Dot product (CORRECTED BUG)
    return this->x * B.x + this->y * B.y + this->z * B.z;
}

#endif // VECTOR_H