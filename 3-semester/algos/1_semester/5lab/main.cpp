#include <iostream>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <ctime>

class matrix {
public:
    int **mtrx;
    int rows, cols, powOf2;

    matrix(const matrix& that) : powOf2{that.powOf2}, rows{that.rows}, cols{that.cols} {
        mtrx = new int* [powOf2];
        for (int i = 0; i < powOf2; ++i) {
            mtrx[i] = new int[powOf2];
        }

        for (int i = 0; i < powOf2; ++i) {
            memcpy(mtrx[i], that.mtrx[i], powOf2 * sizeof(int));
        }
    }

    matrix(const matrix &A, const matrix &B, const matrix &C, const matrix &D) {
        rows = cols = powOf2 = 2 * A.powOf2;
        mtrx = new int* [powOf2];

        for (int i = 0; i < powOf2; i++)
            mtrx[i] = new int[powOf2];

        for (int i = 0; i < A.powOf2; i++) {
            memcpy(mtrx[i], A.mtrx[i], A.powOf2 * sizeof(int));
            memcpy(mtrx[i + A.powOf2], C.mtrx[i], A.powOf2 * sizeof(int));
            memcpy(mtrx[i + A.powOf2] + A.powOf2, D.mtrx[i], A.powOf2 * sizeof(int));
            memcpy(mtrx[i] + A.powOf2, B.mtrx[i], A.powOf2 * sizeof(int));
        }

//        for (int j = 0; j < A.powOf2; j++){
//            mtrx [i][j] = A.mtrx[i][j];
//            mtrx [i+A.powOf2][j] = C.mtrx[i][j];
//            mtrx [i+A.powOf2][j+A.powOf2] = D.mtrx[i][j];
//            mtrx [i][j+A.powOf2] = B.mtrx[i][j];
//        }
    }

    matrix(const matrix &A, const int &fromRows, const int &toRows, const int &fromCols, const int &toCols) {
        cols = A.cols - fromCols;
        rows = A.rows - fromCols;
        powOf2 = A.powOf2 / 2;

        mtrx = new int* [powOf2];
        for (int i = 0; i < powOf2; i++)
            mtrx[i] = new int[powOf2];

        for (int i = 0; i < powOf2; i++)
            memcpy(mtrx[i], A.mtrx[i + fromRows] + fromCols, powOf2 * sizeof(int));
//        for (int j = 0; j < powOf2; j++)
//             if (i>=rows || j>=cols)
//                 mtrx[i][j] = 0;
//             else
//                 mtrx[i][j] = A.mtrx[i+from][j+from];
    }

    matrix(const int &n, const int &m) : rows(n), cols(m) {
        powOf2 = 1;
        while (powOf2 < std::max(m, n))
            powOf2 *= 2;

        mtrx = new int* [powOf2];
        for (int i = 0; i < powOf2; i++)
            mtrx[i] = new int[powOf2];

        for (int i = 0; i < powOf2; i++)
            for (int j = 0; j < powOf2; j++)
                mtrx[i][j] = 0;
    }

//    matrix(const int &n, const int &m, int **matr) : rows(n), cols(m) {
//        powOf2 = 1;
//        while (powOf2 < std::max(m, n))
//            powOf2 *= 2;
//
//        mtrx = new int *[powOf2];
//        for (int i = 0; i < powOf2; i++)
//            mtrx[i] = new int[powOf2];
//
//        for (int i = 0; i < powOf2; i++)
//            for (int j = 0; j < powOf2; j++)
//                if (i >= rows || j >= cols)
//                    mtrx[i][j] = 0;
//                else
//                    mtrx[i][j] = matr[i][j];
//    }

    ~matrix() {
        for (int i = 0; i < powOf2; i++)
            delete[] mtrx[i];
        delete[] mtrx;
    }
};


matrix sumMatr(const matrix &A, const matrix &B) {
    matrix C(A.powOf2, A.powOf2);
    for (int i = 0; i < A.powOf2; i++)
        for (int j = 0; j < A.powOf2; j++)
            C.mtrx[i][j] = A.mtrx[i][j] + B.mtrx[i][j];
    return C;
}

matrix diffMatr(const matrix &A, const matrix &B) {
    matrix C(A.powOf2, A.powOf2);
    for (int i = 0; i < A.powOf2; i++)
        for (int j = 0; j < A.powOf2; j++)
            C.mtrx[i][j] = A.mtrx[i][j] - B.mtrx[i][j];
    return C;
}
matrix cubeMult(const matrix& A, const matrix& B){
    matrix C(A.powOf2,B.powOf2);
    for (int i = 0; i <C.powOf2;i++)
        for (int j = 0;j < C.powOf2; j++)
            for (int k = 0; k< std::min(C.rows,C.cols); k++)
                C.mtrx[i][j]+= A.mtrx[i][k]*B.mtrx[k][j];
    return C;
}
matrix multMatr(const matrix &A, const matrix &B) {

    if (A.powOf2 == 64 && B.powOf2 == 64) {

        return cubeMult(A,B);
    }
    int newPow = A.powOf2/2;
    matrix A11(A, 0, newPow, 0, newPow);
    matrix A12(A, 0, newPow, newPow, A.powOf2);
    matrix A21(A, newPow, A.powOf2, 0, newPow);
    matrix A22(A, newPow, A.powOf2, newPow, A.powOf2);
    newPow = B.powOf2/2;
    matrix B11(B, 0, newPow, 0, newPow);
    matrix B12(B, 0, newPow, newPow, B.powOf2);
    matrix B21(B, newPow, B.powOf2, 0, newPow);
    matrix B22(B, newPow, B.powOf2, newPow, B.powOf2);
    if (A.powOf2 < B.powOf2)
        return matrix(multMatr(A, B11), multMatr(A, B12), matrix(B11.powOf2, B11.powOf2),
                      matrix(B11.powOf2, B11.powOf2));
    if (A.powOf2 > B.powOf2)
        return matrix(multMatr(A11, B), matrix(A11.powOf2, A11.powOf2), multMatr(A21, B),
                      matrix(A11.powOf2, A11.powOf2));
    matrix P1 = multMatr(sumMatr(A11, A22), sumMatr(B11, B22));
    matrix P2 = multMatr(sumMatr(A21, A22), B11);
    matrix P3 = multMatr(A11, diffMatr(B12, B22));
    matrix P4 = multMatr(A22, diffMatr(B21, B11));
    matrix P5 = multMatr(sumMatr(A11, A12), B22);
    matrix P6 = multMatr(diffMatr(A21, A11), sumMatr(B11, B12));
    matrix P7 = multMatr(diffMatr(A12, A22), sumMatr(B21, B22));

    return matrix(diffMatr(sumMatr(sumMatr(P1, P4), P7), P5), sumMatr(P3, P5), sumMatr(P2, P4),
                  diffMatr(sumMatr(sumMatr(P1, P3), P6), P2));
}


int main() {
    int ARows, BRows, AColls, BColls;

    std::cout << "Enter number of rows and colls in A: ";
    std::cin >> ARows >> AColls;
    std::cout << "Enter number of rows and colls in B: ";
    std::cin >> BRows >> BColls;
    srand(time(0));
    matrix A(ARows, AColls), B(BRows, BColls);
   // std::cout << "Enter A:\n";
    for (int i = 0; i < ARows; i++)
        for (int j = 0; j < AColls; j++)
             A.mtrx[i][j] = rand()%200;
   // std::cout << "Enter B:\n";
    for (int i = 0; i < BRows; i++)
        for (int j = 0; j < BColls; j++)
            B.mtrx[i][j]= rand()%200;
    std::cout << "Result:\n";

    auto start= std::chrono::system_clock::now();
    matrix C = multMatr(A, B);
    auto endi = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = endi-start;

    std::cout<< "elapsed time in fast mult: " << elapsed_seconds.count() << " s \n";


//    for (int i = 0; i < C.rows; i++) {
//        for (int j = 0; j < C.cols; j++)
//            std::cout << C.mtrx[i][j] << " ";
//        std::cout << '\n';
//    }
    start= std::chrono::system_clock::now();
    matrix D = cubeMult(A,B);
    endi = std::chrono::system_clock::now();
    elapsed_seconds = endi-start;

    std::cout<< "elapsed time in regular mult: " << elapsed_seconds.count() << " s \n";
//    for (int i = 0; i < D.rows; i++) {
//        for (int j = 0; j < D.cols; j++)
//            std::cout << D.mtrx[i][j] << " ";
//        std::cout << '\n';
//    }

    return 0;
}