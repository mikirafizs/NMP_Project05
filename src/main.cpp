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

    std::vector <std::vector <double>> A_num(n, std::vector <double>(n));
    std::vector <std::vector <double>> A_inv(n, std::vector <double>(n));

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            for (std::size_t k = 0; k < n; k++) {
                A_num[i][j] += eigenvalues[k] * eigenvectors[k][i] * eigenvectors[k][j];
                A_inv[i][j] += (1.0 / eigenvalues[k]) * eigenvectors[k][i] * eigenvectors[k][j];
            }
        }
    }

    std::ofstream matrix_reconstructed;
    matrix_reconstructed.open("../data/reconstructed_matrices.csv");
    if(!matrix_reconstructed.is_open()){
        std::cerr << "Cannot open reconstructed_matrices.csv \n";
        return 1;
    }

    matrix_reconstructed << "--- A_num ---\n";
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            matrix_reconstructed << std::setw(10) << std::setprecision(5) << A_num[i][j] << " ";
        }
        matrix_reconstructed << "\n";
    }

    matrix_reconstructed << "\n--- A_inv ---\n";
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            matrix_reconstructed << std::setw(10) << std::setprecision(5) << A_inv[i][j] << " ";
        }
        matrix_reconstructed << "\n";
    }
    matrix_reconstructed.close();

    return 0;
}