#include<iostream>
#include<stdio.h>
#include<vector>

void dispArray(auto& array){
    for(auto a : array){
        for(int i = 0; i < a.size() ; i++){
            std::cout << a[i] << " " ;
        }
        std::cout << std::endl;
    }
}

void disp1dArray(auto& array){
    for(int i = 0; i < array.size() ; i++){
        std::cout << array[i] << " " ;
    }
    std::cout << std::endl;
}