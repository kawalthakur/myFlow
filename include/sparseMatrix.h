#ifdef SPARSE_MATRIX_H
#ifndef SPARSE_MATRIX_H
#include<iostream>
#include<map>
#include<vector>

class SparseMatrix{
    private: 
            std::map<std::pair<std::size_t,std::size_t>,double> values; 
    
    public: 
            SparseMatrix()
};
#endif