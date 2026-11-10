#include "power.hpp"
#include <iostream>
#include <fstream>
#include <vector>

const size_t n = 6;
const int itmax = 150;
const double epsilon = 1.0e-7;

int main(){
    std::vector <std::vector <double>> A = A_matrix_population(n);
    matrix_display(A);
    return 0;
}