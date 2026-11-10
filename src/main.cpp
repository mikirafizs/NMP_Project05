#include "power.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

const size_t n = 6;
const int itmax = 150;
const double epsilon = 10.0e-8;

int main(){
    std::vector <std::vector <double>> A = A_matrix_population(n);
    matrix_display(A);
    std::vector <std::vector <double>> eigenvectors (n, std::vector <double>(n));
    std::vector <double> eigenvalues(n, 0.0);

    std::ofstream lambda_values;
    lambda_values.open("../data/lambda_values.csv");
    if(!lambda_values.is_open()){
        std::cerr << "Cannot open lambda_values.csv \n";
        return 1;
    }
    
    for(std::size_t k = 0; k < n; k++){
        std::vector <double> x(n, 0.0);
        x = random_v_fill(n);
    
        double old_lambda = 10.0e5;
        double new_lambda;

        for(int it = 1; it <= itmax; it++){
            std::vector <double> y = matrix_vector_multiplication(A, x);
            new_lambda = v_dot(y, x)/v_dot(x, x);

            //Gram-Schmidt orthogonalization
            for(size_t m = 0; m < k; m++){
                double c = v_dot(eigenvectors[m], y);
                for (std::size_t i = 0; i < n; i++) {
                    y[i] -= c * eigenvectors[m][i];
                }
            }
            double ynorm = v_norm(y);
            for(size_t i = 0; i < n; i++){
                x[i] = y[i]/ynorm;
            }

            if(std::abs((new_lambda-old_lambda)/old_lambda) < epsilon) break;

            old_lambda = new_lambda;
        }
        eigenvectors[k] = x;
        eigenvalues[k] = new_lambda;
        lambda_values << k+1 << "," << eigenvalues[k] << "\n";
    }
    lambda_values.close();
    return 0;
}