#include<iostream>
#include"../include/Vector.h"

int main(){
    Vector A(2.4,3.55,4.67);
    Vector B(1.6,4.5,5.6);
    
    Vector C;
    C = A + B ; 
    std::cout << C << std::endl;
    C = A - B ;
    std::cout << C << std::endl;

    C = A^B;
    std::cout << C << std::endl;

    std::cout << (A*B) << std::endl;
    return 0 ;
}