#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<vector>
#include "Point.h"

class node{
    private: 
            std::size_t index; 
            Point centroid ; 
            std::vector<std::size_t> iFaces;
            std::vector<std::size_t> iCells;
    
    public: 
            node(std::size_t index_=0, Point centroid_=Point());
            void setIndex(std::size_t index_);
            void setCentroid(Point C);
            void pushFaceIndex(std::size_t iFace);
            void displayNode();
};

node::node(std::size_t index_, Point centroid_){
    this->index = index_;
    this->centroid = centroid_;
}

void node::setIndex(std::size_t index_){
    this->index = index_ ; 
}

void node::setCentroid(Point C){
    this->centroid = C;
}

void node::pushFaceIndex(std::size_t iFace){
    iFaces.push_back(iFace);
}

void node::displayNode(){
    std::cout << "Index : " << this->index << std::endl;
    std::cout << "iFace : ( " ; 
    for(int i = 0 ; i < this->iFaces.size() ; i++){
        std::cout << this->iFaces[i] << " " ;
    } 
    std::cout << ")" << std::endl;
}
#endif