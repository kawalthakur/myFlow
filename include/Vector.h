#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>

class Vector: public Point{
	// This class is the primary object vector. 
	// This has 3 components x , y and z
	// Also includes operations like dot products and cross products
	private:
			double x, y, z ; 
	public: 
			Vector(double x_=0.0, double y_=0.0, double z_=0.0 ):Point(x_,y_,z_){};
			double dot(Vector& A,Vector& B);
			Vector cross(Vector& A, Vector& B);
			friend std::ostream& operator<<(std::ostream& os, Vector& A);
			Vector operator+(Vector& B);	// Addition 
			Vector operator-(Vector& B);	// Subtraction
			Vector operator^(Vector& B);	// Cross product 
			double operator*(Vector& B);	// Dot product 
};

double Vector::dot(Vector& A, Vector& B){
	double result = 0; 
	result = A.X() * B.X() + A.Y() * B.Y() + A.Y()*B.Y();
	return result;
}

Vector Vector::cross(Vector& A, Vector& B){
	double X, Y, Z ; 
	X = A.Y() * B.Z() - A.Z() * B.Y();
	Y = A.Z() * B.X() - A.X() * B.Z();
	Z = A.X() * B.Y() - A.Y() * B.X();
	return Vector(X,Y,Z);
}

std::ostream& operator<<(std::ostream& os,Vector& A){
	os << "(" << A.X() << "," << A.Y() << "," << A.Z() <<")" ; 
	return os ;
}

Vector Vector::operator+(Vector& B){
	double X_, Y_, Z_ ; 
	X_ = this->x + B.X();
	Y_ = this->y + B.Y();
	Z_ = this->z + B.Z();
	return Vector(X_,Y_,Z_) ;
}

Vector Vector::operator-(Vector& B){
	double X_, Y_, Z_ ; 
	X_ = this->x - B.X();
	Y_ = this->y - B.Y();
	Z_ = this->z - B.Z();
	return Vector(X_,Y_,Z_) ;
}

Vector Vector::operator^(Vector& B){
	Vector C(0,0,0);
	C = this->cross(*this,B);
	return C;
}

double Vector::operator*(Vector& B){
	return this->dot(*this,B);
}

#endif