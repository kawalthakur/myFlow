#ifndef POINT_H
#define POINT_H
#include<iostream>
#include <cmath> 

class Point{
    private: 
            double x,y,z;   // Coordinates 
    public: 
            Point(double x_= 0.0, double y_=0.0, double z_=0.0);
            double distance(Point& A, Point& B);
            double X();
            double Y();
            double Z();
};

Point::Point(double x_, double y_, double z_){
    this->x = x_ ;
    this->y = y_ ;
    this->z = z_ ; 
}

double Point::X(){
    return this->x;
}

double Point::Y(){
    return this->y;
}

double Point::Z(){
    return this->z;
}

#endif
