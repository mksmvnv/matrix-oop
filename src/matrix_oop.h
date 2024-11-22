#ifndef MATRIX_OOP_H
#define MATRIX_OOP_H

#include <cmath>
#include <gtest/gtest.h>
#include <iostream>

#define EPS 1e-7
#define S_AR 1

class Matrix {
   public:
    // Constructor & Destructor
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix &other);
    Matrix(Matrix &&other);
    ~Matrix();

    // Methods
    bool EqMatrix(const Matrix &other) const;
    void SumMatrix(const Matrix &other);
    void SubMatrix(const Matrix &other);
    void MulNumber(const double num);
    void MulMatrix(const Matrix &other);
    Matrix Transpose();
    Matrix CalcComplements();
    Matrix Submatrix(int row, int col);
    double Determinant();
    Matrix InverseMatrix();

    // Operators
    Matrix operator+(const Matrix &other);
    Matrix operator-(const Matrix &other);
    Matrix operator=(const Matrix &other);
    Matrix operator=(Matrix &&other);
    bool operator==(const Matrix &other);
    Matrix &operator+=(const Matrix &other);
    Matrix &operator-=(const Matrix &other);
    Matrix &operator*=(const Matrix &other);
    Matrix &operator*=(double num);
    Matrix operator*(const Matrix &other);
    Matrix operator*(const double num);
    double &operator()(int rows, int columns);

    // Accessors & mutators
    int GetRows() const;
    int GetCols() const;

    void SetRows(int rows);
    void SetColumns(int columns);

    // Friend method
    friend Matrix operator*(double num, Matrix &other);

   private:
    // Attributes
    int rows_, cols_;
    double **matrix_;

    // Private methods
    void CreateMatrix();
    void DestroyMatrix();
    void CopyMatrix(const Matrix &other);
    void MoveMatrix(Matrix &other);
    void SetNull();
    int EqualMatrix(const Matrix &other);
};

#endif  // MATRIX_OOP_H
