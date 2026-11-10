#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>



// only for square matrices

inline std::vector <std::vector <double>> A_matrix_population(std::size_t n){
    std::vector <std::vector <double>> A(n, std::vector <double> (n, 0.0));
    for(std::size_t i = 0; i < n; i++){
        for(std::size_t j = 0; j< n; j++){
            if(j+1 == i || j == i+1){
                A[i][j] = 1;
            }
        }
        A[i][i] = -2;
    }
    return A;
}

inline void matrix_display(const std::vector <std::vector <double>> &A){
    std::size_t n = A.size();
    for(std::size_t i = 0; i < n; i++){
        std::cout<<"[ ";
        for(std:: size_t j = 0; j < n; j++){
            std::cout << std::setw(2) << std::setprecision(3) << A[i][j] <<"  ";
        }
        std::cout<<"]\n";
    }
}

inline double v_dot(const std::vector <double> &a, const std::vector <double> &b){
    std::size_t na = a.size();
    if(na != b.size()){
        throw std::invalid_argument("Cannot perform vector scalar multiplication (dimensions differ)!");
    }
    double sum = 0.0;
    for(std::size_t i = 0; i < na; i++){
        sum += a[i]*b[i];
    }
    return sum;
}

inline std::vector <double> matrix_vector_multiplication(const std::vector <std::vector <double>> &A, const std::vector <double> &v){
    std::size_t nv = v.size();
    if(nv != A.size()){
        throw std::invalid_argument("Cannot perform matrix-vector multiplication (dimensions differ)!");
    }
    std::vector <double> Ax (nv, 0.0);
    for(std::size_t r = 0; r < nv; r++){
        double sum = 0.0;
        for(std::size_t c = 0; c < nv; c++){
            sum += A[r][c]*v[c];
        }
        Ax[r] = sum;
    }
    return Ax;
}

inline double v_norm(const std::vector <double> &v){
    std::size_t nv = v.size();
    double sum = 0.0; 
    for(std::size_t i = 0; i < nv; i++){
        sum += v[i]*v[i];
    }
    return std::sqrt(sum);
}

inline std::vector <double> v_normalization(const std::vector <double> &v){
    std::size_t nv = v.size();
    double vnorm = v_norm(v);
    std::vector <double> c (nv, 0.0);

    for(std::size_t i = 0; i < nv; i++){
        c[i] = v[i]/vnorm;
    }
    return c;
}

inline std::vector <double> random_v_fill(std::size_t n){
    std::vector <double> x (n, 0.0);

    for(std::size_t i = 0; i < n; i++){
        x[i] = (double)rand()/RAND_MAX;
    }
    return x;
}