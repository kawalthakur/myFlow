#include<iostream>

class Vector{
	// This class is the primary object vector. 
	// This has 3 components x , y and z
	// Also includes operations like dot products and cross products
	private:
			double x, y, z ; 
	public: 
			Vector(double x_, double y_, double z_ );
			Vector dot(Vector A,Vector B);
			Vector cross(Vector A, Vector B);
};

// Implement all the functionalities 
