#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <iomanip>
using namespace std;

typedef struct Matrix
{
    int** m;
    int n;
}Matrix;

// Ham tao ma tran bang cach copy tu ma tran o
void copyMatrix(Matrix& matrix, Matrix& o)
{
    matrix.n = o.n;
    matrix.m = new int*[matrix.n];
    for (int i = 0; i < matrix.n; i++)
    {
        matrix.m[i] = new int[matrix.n];
    }
    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.n; j++)
        {
            matrix.m[i][j] = o.m[i][j];
        }
    }
    
}

void createMatrix(Matrix& matrix)
{
    matrix.m = new int*[matrix.n];
    for (int i = 0; i < matrix.n; i++)
    {
        matrix.m[i] = new int[matrix.n];
    }
}
void printMatrix(Matrix& matrix)
{
    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.n; j++)
        {
            if (matrix.m[i][j] == 10000)
            {
                cout << setw(6) <<  "\u221E";
            }
            else
            {
                cout << setw(4) << matrix.m[i][j];
            }
            
        }
        cout << "\n";
    }
}
void detroyMatrix(Matrix& matrix)
{
    for (int i = 0; i < matrix.n; i++)
    {
        delete [] matrix.m[i];
    }
    delete [] matrix.m;
}
#endif

