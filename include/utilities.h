#ifndef UTILITIES_H
#define UTILITIES_H

#include<iostream>
#include<stdio.h>
#include<vector>
#include "Point.h"

// void dispArray(auto& array){
//     for(auto a : array){
//         for(int i = 0; i < a.size() ; i++){
//             std::cout << a[i] << " " ;
//         }
//         std::cout << std::endl;
//     }
// }

// void disp1dArray(auto& array){
//     for(int i = 0; i < array.size() ; i++){
//         std::cout << array[i] << " " ;
//     }
//     std::cout << std::endl;
// }

void displayVector(std::vector<std::size_t>& v1){
    std::cout << "["; 
    for(std::size_t i = 0 ; i < v1.size() ; i++){
        std::cout << v1[i] << " "; 
        if(i == v1.size() - 1){
            std::cout << v1[i];
        }
    }
    std::cout << "]" << std::endl;
}

void displayPoint(Point& p){
    std::cout << "(" << p.X() << "," << p.Y() << "," << p.Z() << ")" << std::endl; 
}

#endif