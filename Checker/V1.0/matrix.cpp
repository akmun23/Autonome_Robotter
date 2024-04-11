#include "matrix.h"
#include <iostream>

Matrix::Matrix(int rows, int cols, double val):_rows(rows), _cols(cols) {
    for(int i = 0; i < rows*cols; i++){
        _data.push_back(val);
    }
}

Matrix::Matrix(Matrix& m):_rows(m.getRows()), _cols(m.getCols()){
    for(int i = 0; i < m.getRows()*m.getCols(); i++){
        _data.push_back(m._data[i]);
    }
}

int Matrix::getCols(){
    return _cols;
}

int Matrix::getRows(){
    return _rows;
}

void Matrix::print(){
    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _cols; j++){
            std::cout << _data[i*j]  << " ";
        }
    }
}

double Matrix::read(int r, int c){
    return _data[r*_cols + c];
}

void Matrix::set(int r, int c, double val){
    _data[r*_cols + c] = val;
}

double& Matrix::at(int r, int c){
    return _data[r*_cols + c];
}

Matrix Matrix::add(Matrix& matrix){
    if (_rows != matrix.getRows() || _cols != matrix.getCols()){
        std::cout << "Matrix dimensions must match" << std::endl;
    } else {
        Matrix result(_rows, _cols);
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                result.at(r,c) = at(r,c) + matrix.at(r,c);
            }
        }
        return result;
    }
    return Matrix(0,0);
}

Matrix Matrix::multiply(Matrix& matrix){
    if(_cols != matrix.getRows()){
        std::cout << "Matrix dimensions must match" << std::endl;
    } else {
        Matrix result(_rows, matrix.getCols());
        for(int r = 0; r < _rows; r++){
            for (int c = 0; c < matrix.getCols(); c++) {
                double sum = 0;
                for(int i = 0; i < _cols; i++){
                   sum += read(r,i) * matrix.read(i,c);

                }
                result.set(r,c, sum);
            }
        }
        return result;
    }
    return Matrix(0,0);
}

void Matrix::transpose(){
    Matrix result(_cols, _rows);
    double value;
    for(int r = 0; r < _rows; r++){
        for(int c = 0; c < _cols; c++){
            value = read(r,c);
            result.set(c,r, value);
        }
    }
    _rows = result.getRows();
    _cols = result.getCols();
    _data = result._data;
}

double& Matrix::operator()(int r, int c){
    return at(r,c);
}

Matrix Matrix::operator+(Matrix m){
    return add(m);
}

Matrix Matrix::operator*(Matrix m){
    return multiply(m);
}

std::shared_ptr<Matrix> Matrix::add(std::shared_ptr<Matrix> matrix){
    if (_rows != matrix -> getRows() || _cols != matrix -> getCols()){
        std::cout << "Matrix dimensions must match" << std::endl;
    } else {
        Matrix result(_rows, _cols);
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                result.at(r,c) = at(r,c) + matrix -> at(r,c);
            }
        }
        matrix = std::make_shared<Matrix>(result);
        return matrix;
    }
    return std::make_shared<Matrix>(0,0);
}

std::shared_ptr<Matrix> Matrix::multiply(std::shared_ptr<Matrix> matrix){
    if(_cols != matrix -> getRows()){
        std::cout << "Matrix dimensions must match" << std::endl;
    } else {
        Matrix result(_rows, matrix -> getCols());
        for(int r = 0; r < _rows; r++){
            for (int c = 0; c < matrix -> getCols(); c++) {
                double sum = 0;
                for(int i = 0; i < _cols; i++){
                    sum += read(r,i) * matrix -> read(i,c);

                }
                result.set(r,c, sum);
            }
        }
        matrix = std::make_shared<Matrix>(result);
        return matrix;
    }
    return std::make_shared<Matrix>(0,0);
}
