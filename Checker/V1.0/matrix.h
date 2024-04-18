#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <memory>

class Matrix
{
    std::vector<double> _data;
    int _rows;
    int _cols;
public:
    Matrix(int rows, int cols, double val = 0);

    Matrix(Matrix& m);

    int getRows();

    int getCols();

    virtual void print();

    double read(int r, int c);

    void set(int r, int c, double val);

    double& at(int r, int c);

    Matrix add(Matrix& matrix);

    Matrix multiply(Matrix& matrix);

    virtual void transpose();

    double& operator()(int r, int);

    Matrix operator+(Matrix m);

    Matrix operator*(Matrix m);

    std::shared_ptr<Matrix> add(std::shared_ptr<Matrix> matrix);

    std::shared_ptr<Matrix> multiply(std::shared_ptr<Matrix> matrix);

};

#endif // MATRIX_H
