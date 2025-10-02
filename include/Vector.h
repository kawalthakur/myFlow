#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include "Point.h" // Assumes your Point.h header is available

class Vector: public Point{
private:
    // These members hide the members from the Point base class, as per collaborator's design.
    double x, y, z; 
public: 
    // Constructor now correctly initializes its own members and calls the base constructor.
    Vector(double x_ = 0.0, double y_ = 0.0, double z_ = 0.0);

    // Getters for this class's own x,y,z variables.
    double X() const;
    double Y() const;
    double Z() const;

    // Non-member style helper methods (made const-correct for compatibility).
    double dot(const Vector& A, const Vector& B) const;
    Vector cross(const Vector& A, const Vector& B) const;

    // Operator overloads (made const-correct).
    Vector operator+(const Vector& B) const;
    Vector operator-(const Vector& B) const;
    Vector operator^(const Vector& B) const;
    double operator*(const Vector& B) const;

    // Friend function for printing (made const-correct).
    friend std::ostream& operator<<(std::ostream& os, const Vector& A);
};

// --- Implementation ---

// Constructor now initializes its own members.
inline Vector::Vector(double x_, double y_, double z_) : Point(x_, y_, z_), x(x_), y(y_), z(z_) {}

// Implementation for this class's getters.
inline double Vector::X() const { return this->x; }
inline double Vector::Y() const { return this->y; }
inline double Vector::Z() const { return this->z; }

// BUG FIX: Corrected A.Y()*B.Y() to A.Z()*B.Z() and made const-correct.
inline double Vector::dot(const Vector& A, const Vector& B) const {
    return A.X() * B.X() + A.Y() * B.Y() + A.Z() * B.Z();
}

// Made const-correct.
inline Vector Vector::cross(const Vector& A, const Vector& B) const {
    double nX = A.Y() * B.Z() - A.Z() * B.Y();
    double nY = A.Z() * B.X() - A.X() * B.Z();
    double nZ = A.X() * B.Y() - A.Y() * B.X();
    return Vector(nX, nY, nZ);
}

// Made const-correct.
inline std::ostream& operator<<(std::ostream& os, const Vector& A) {
    os << "(" << A.X() << "," << A.Y() << "," << A.Z() << ")"; 
    return os;
}

// Made const-correct.
inline Vector Vector::operator+(const Vector& B) const {
    return Vector(this->x + B.x, this->y + B.y, this->z + B.z);
}

// Made const-correct.
inline Vector Vector::operator-(const Vector& B) const {
    return Vector(this->x - B.x, this->y - B.y, this->z - B.z);
}

// Made const-correct.
inline Vector Vector::operator^(const Vector& B) const {
    return this->cross(*this, B);
}

// Made const-correct.
inline double Vector::operator*(const Vector& B) const {
    return this->dot(*this, B);
}

#endif // VECTOR_H