#include<iostream>
#include<vector>
#include "./include/Point.h"

class Node{
    private: 
            std::size_t index; 
            Point centroid ; 
            std::vector<std::size_t> iFaces;
            std::vector<std::size_t> iCells;
    
    public: 
            Node(std::size_t index_=0, Point centroid_(0,0,0));
}

Node::Node(std::size_t index_, Point centroid){
    this->index = index_;
    this->centroid = centroid_;
}