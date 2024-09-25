#include <iostream>

using namespace std;

// Function to input a 3x3 matrix
void inputMatrix(int matrix[3][3], int dim) {
    cout << "Enter elements for a " << dim << "x" << dim << " matrix:\n";
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            cin >> matrix[i][j];
        }
    }
}

// Function to print a 3x3 matrix
void printMatrix(int matrix[3][3], int dim) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Standard matrix multiplication
void matrixMultiply(int A[3][3], int B[3][3], int C[3][3], int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            C[i][j] = 0;  // Initialize the result matrix element
            for (int k = 0; k < dim; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Divide and Conquer matrix multiplication (for simplicity, directly applied to 2x2 submatrices)
void divideAndConquerMultiply(int A[2][2], int B[2][2], int C[2][2]) {
    int P1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);  // P1 = (A11 + A22)(B11 + B22)
    int P2 = (A[1][0] + A[1][1]) * B[0][0];              // P2 = (A21 + A22)B11
    int P3 = A[0][0] * (B[0][1] - B[1][1]);              // P3 = A11(B12 - B22)
    int P4 = A[1][1] * (B[1][0] - B[0][0]);              // P4 = A22(B21 - B11)
    int P5 = (A[0][0] + A[0][1]) * B[1][1];              // P5 = (A11 + A12)B22
    int P6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);  // P6 = (A21 - A11)(B11 + B12)
    int P7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);  // P7 = (A12 - A22)(B21 + B22)

    C[0][0] = P1 + P4 - P5 + P7;  // C11 = P1 + P4 - P5 + P7
    C[0][1] = P3 + P5;            // C12 = P3 + P5
    C[1][0] = P2 + P4;            // C21 = P2 + P4
    C[1][1] = P1 - P2 + P3 + P6;  // C22 = P1 - P2 + P3 + P6
}

// Wrapper function to apply divide and conquer to 3x3 matrices by working on 2x2 submatrices
void divideAndConquerMatrixMultiply(int A[3][3], int B[3][3], int C[3][3]) {
    int A11[2][2] = {{A[0][0], A[0][1]}, {A[1][0], A[1][1]}};
    int A12[2][2] = {{A[0][2], 0}, {A[1][2], 0}};
    int A21[2][2] = {{A[2][0], A[2][1]}, {0, 0}};
    int A22[2][2] = {{A[2][2], 0}, {0, 0}};

    int B11[2][2] = {{B[0][0], B[0][1]}, {B[1][0], B[1][1]}};
    int B12[2][2] = {{B[0][2], 0}, {B[1][2], 0}};
    int B21[2][2] = {{B[2][0], B[2][1]}, {0, 0}};
    int B22[2][2] = {{B[2][2], 0}, {0, 0}};

    int C11[2][2], C12[2][2], C21[2][2], C22[2][2];

    divideAndConquerMultiply(A11, B11, C11);
    divideAndConquerMultiply(A12, B21, C12);
    divideAndConquerMultiply(A21, B12, C21);
    divideAndConquerMultiply(A22, B22, C22);

    // Combine results into final 3x3 matrix C
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C[i][j] = C11[i][j] + C12[i][j];  // Upper-left quadrant
            C[i][j + 1] = C11[i][j] + C12[i][j + 1];  // Upper-right quadrant
            C[i + 1][j] = C21[i][j] + C22[i][j];  // Lower-left quadrant
        }
    }
}

int main() {
    int dim = 3;
    int A[3][3], B[3][3], C[3][3];

    // Input matrices
    inputMatrix(A, dim);
    inputMatrix(B, dim);

    // Performing standard matrix multiplication
    matrixMultiply(A, B, C, dim);

    // Display the result
    cout << "Matrix multiplication result:\n";
    printMatrix(C, dim);

    // Performing divide and conquer multiplication
    divideAndConquerMatrixMultiply(A, B, C);

    // Display the result
    cout << "Divide and Conquer multiplication result:\n";
    printMatrix(C, dim);

    return 0;
}
