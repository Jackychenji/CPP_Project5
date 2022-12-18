#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <immintrin.h>
#include <omp.h>
using namespace std;

#define MinSize 1
#define MaxSize 10000

template <typename T>
class Matrix;

template <typename T>
class Matrix
{
public:
    // constructor
    Matrix<T>() = delete;                                 // delete origin constructor
    Matrix<T>(int rows, int columns, T value);            // All values in data are value
    Matrix<T>(int rows, int columns, T arr[], int length); // copy from T*
    Matrix<T>(int rows, int columns);                     // input values

    // destructor
    ~Matrix();

    // soft copy
    Matrix<T>(Matrix<T> &);

    // methods
    void printMatrix() const; // print Matrix
    int getRows() const;      // get rows
    int getRefCount() const;
    int getCols() const;             // get columns
    bool ifSquare() const;           // judge if Matrix is square
    Matrix<T> getRowthNums(int row); // get rowth row's nums
    Matrix<T> getColthNums(int col); // get colth column's nums
    void swapRows(int a, int b);     // swap row = a & row = b
    void swapCols(int a, int b);     // swap column = a & column = b
    void transMatrix();              // get transpose

    // overload
    T operator()(int row, int col);    // get rowth row,colth column number
    Matrix<T> &operator+(Matrix<T> &); // add matrix
    Matrix<T> &operator+(T value);     // add T
    Matrix<T> &operator-(Matrix<T> &); // minus matrix
    Matrix<T> &operator-(T value);     // minus T
    Matrix<T> &operator=(Matrix<T> &); // soft copy
    Matrix<T> &operator*(Matrix<T> &); // plainmul with matrix
    Matrix<T> &operator*(T value);     // plainmul with T
    bool operator==(Matrix<T> &);      // judge if equals

private:
    int row;
    int column;
    int size; // row*column
    T *data;  // the numbers in Matrix, data[size+1]is the number that this data is being used
              
};

template <typename T>
Matrix<T>::Matrix(Matrix &matrix)
{
    if (matrix.row < MinSize || matrix.row > MaxSize || matrix.column < MinSize || matrix.column > MaxSize || matrix.data == NULL)
    {
        cout << "invalid input" << endl;
        return;
    }

    row = matrix.row;
    column = matrix.column;
    size = column * row;
    data = new T[row * column];
    // copy
    data = matrix.data;
    data[size + 1]++;
}

template <typename T>
Matrix<T>::Matrix(int rows, int columns, T value)
{
    if (rows < MinSize || rows > MaxSize || columns < MinSize || columns > MaxSize)
    {
        cout << "invalid input" << endl;
        return;
    }
    row = rows;
    column = columns;
    size = column * row;
    data = new T[size + 4];
    data[size + 1] = 1;
    for (int i = 0; i < size; i++)
    {
        *(data + i) = value;
    }
}

template <typename T>
Matrix<T>::Matrix(int rows, int columns, T arr[], int length)
{
    if (rows < MinSize || rows > MaxSize || columns < MinSize || columns > MaxSize || arr == NULL)
    {
        cout << "invalid input" << endl;
        return;
    }

    row = rows;
    column = columns;
    size = column * row;
    if (length != size)
    {
        cout << "invalid input" << endl;
        return;
    }
    data = arr;
    data[size + 1] = 1;
}

template <typename T>
Matrix<T>::Matrix(int rows, int columns)
{
    if (rows < MinSize || rows > MaxSize || columns < MinSize || columns > MaxSize)
    {

        cout << "Invalid input" << endl;
        return;
    }

    data = new T[rows * columns];
    row = rows;
    column = columns;
    size = rows * columns;
    cout << "need to input: " << to_string(size) << " numbers"
         << "\n";

    for (int i = 0; i < size; i++)
    {
        T input;
        cin >> input;
        // 赋值
        *(data + i) = input;
    }
    data[size + 1] = 1;
}

template <typename T>
Matrix<T>::~Matrix()
{
    data[size + 1]--;
    if (data[size + 1] == 0)
    {
        delete[] data;
    }
    data = NULL;
    
}

template <typename T>
void Matrix<T>::printMatrix() const
{
    cout << "The matrix now is:" << endl;
    ;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cout << *(data + i * column + j);
            if (j < column - 1)
            {
                cout << "\t";
            }
            else if (j == column - 1)
            {
                cout << "\n";
            }
        }
    }
}

template <typename T>
int Matrix<T>::getRows() const
{
    return row;
}

template <typename T>
int Matrix<T>::getRefCount() const
{
    return data[size + 1];
}

template <typename T>
int Matrix<T>::getCols() const
{
    return column;
}

template <typename T>
bool Matrix<T>::ifSquare() const
{
    if (column == row)
    {
        cout << "This matrix is square" << endl;
        return true;
    }
    else
    {
        cout << "This matrix is not square" << endl;
        return false;
    }
}

template <typename T>
T Matrix<T>::operator()(int rows, int col)
{
    if (rows < 0 || rows >= row || col < 0 || col >= column)
    {
        cout << "invalid input" << endl;
    }
    T now_value = *(data + rows * (column) + col);
    cout << "The" << to_string(rows) << "th row, " << to_string(col) << "th column's value is " << to_string(now_value) << endl;
    return now_value;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+(Matrix<T> &matrix)
{
    int matrix_row = matrix.getRows();
    int matrix_col = matrix.getCols();
    if (matrix_row != row || matrix_col != column)
    {
        cout << "invalid input" << endl;
    }
    T *matrix_data = matrix.data;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            T matrix_value = *(matrix_data + i * row + j);
            T now_value = *(data + i * row + j);
            *(data + i * row + j) = now_value + matrix_value;
        }
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+(T value)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            T now_value = *(data + i * row + j);
            *(data + i * row + j) = now_value + value;
        }
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-(Matrix<T> &matrix)
{
    int matrix_row = matrix.getRows();
    int matrix_col = matrix.getCols();
    if (matrix_row != row || matrix_col != column)
    {
        cout << "invalid input" << endl;
    }
    T *matrix_data = matrix.data;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            T matrix_value = *(matrix_data + i * row + j);
            T now_value = *(data + i * row + j);
            *(data + i * row + j) = now_value - matrix_value;
        }
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-(T value)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            T now_value = *(data + i * row + j);
            *(data + i * row + j) = now_value - value;
        }
    }
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(Matrix &matrix)
{
    // judge if the same
    if (this == &matrix)
    {
        return true;
    }

    // judge the numbers
    T *matrix_data = matrix.data;
    bool equal = true;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            T matrix_value = *(matrix_data + i * row + j);
            T now_value = *(data + i * row + j);
            if (matrix_value != now_value)
            {
                equal = false;
            }
        }
    }

    if (matrix.row != row || matrix.column != column || !equal)
    {
        return false;
    }
    return true;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &mat)
{
    if (this == &mat)
    {
        return *this;
    }

    if (data != NULL)
    {
        data[size + 1]--;
        if (data[size + 1] == 0)
        {
            delete[] data;
        }
    }
    row = mat.row;
    column = mat.column;
    // soft copy
    data = mat.data;
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*(T value)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            T now_value = *(data + i * row + j);
            *(data + i * row + j) = now_value * value;
        }
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*(Matrix<T> &matrix)
{
    int matrix_row = matrix.getRows();
    int matrix_col = matrix.getCols();
    int matrix_size = matrix_col * matrix_row;
    if (matrix_row != column)
    {
        cout << "invalid input" << endl;
    }

    if (matrix_row == column)
    {

        T *C = new T[size + 4]{0};
        matrix.transMatrix();
        T *matrix_data = matrix.data;
        int count = 0;
#pragma omp parallel for num_threads(4)
        for (size_t i = 0; i < size; i += column)
        {
            for (size_t j = 0; j < matrix_size; j += matrix_row)
            {
#pragma omp critical
                for (size_t k = 0; k < column; k++)
                {
                    *(C + count) += data[i + k] * matrix_data[j + k];
                }
                count++;
            }
        }
        matrix.transMatrix();
        column = matrix_col;
        data[size + 1]--;
        data = C;
        size = column * row;
        data[size + 1]++;
        return *this;
    }
    return *this;
}

template <typename T>
void Matrix<T>::swapCols(int a, int b)
{
    if (a < 0 || a >= column || b < 0 || b >= column)
    {
        cout << "invalid input" << endl;
        return;
    }

    T *tmp = new T[row];
    for (int i = 0; i < row; i++)
    {
        *(tmp + i) = *(data + i * column + b);
        *(data + i * column + b) = *(data + i * column + a);
        *(data + i * column + a) = *(tmp + i);
    }
    delete[] tmp;
    return;
}

template <typename T>
void Matrix<T>::swapRows(int a, int b)
{
    if (a < 0 || a >= row || b < 0 || b >= row)
    {
        cout << "invalid input" << endl;
        return;
    }

    T *tmp = new T[column];

    for (int j = 0; j < column; j++)
    {
        // 将b行数据给到tmp,b行数据用a行数据赋值,a行数据用tmp赋值
        *(tmp + j) = *(data + b * column + j);
        *(data + b * column + j) = *(data + a * column + j);
        *(data + a * column + j) = *(tmp + j);
    }

    delete[] tmp;
    return;
}

template <typename T>
Matrix<T> Matrix<T>::getColthNums(int col)
{
    int matrixRow = row;
    int matrixColumn = 1;

    T *tmp = new T[matrixRow * matrixColumn];

    for (int i = 0; i < matrixRow; i++)
    {
        *(tmp + i) = *(data + row * i + col);
    }
    Matrix<T> result_mat(matrixRow, matrixColumn, tmp);
    return result_mat;
}

template <typename T>
Matrix<T> Matrix<T>::getRowthNums(int row)
{
    int matrixRow = 1;
    int matrixColumn = column;
    T *tmp = new T[matrixRow * matrixColumn];

    for (int j = 0; j < matrixColumn; j++)
    {
        *(tmp + j) = *(data + row * column + j);
    }
    Matrix<T> result_mat(matrixRow, matrixColumn, tmp);
    return result_mat;
}

template <typename T>
void Matrix<T>::transMatrix()
{

    T *tmpMatrix = new T[size + 4];
    for (int i = 0; i < size + 4; i++)
    {
        tmpMatrix[i] = data[i];
    }
    int temp = row;
    row = column;
    column = temp;

    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < row; j++)
        {
            *(tmpMatrix + j * column + i) = *(data + i * row + j);
        }
    }
    data[size + 1]--;
    data = tmpMatrix;
    data[size + 1] = 1;
    return;
}
