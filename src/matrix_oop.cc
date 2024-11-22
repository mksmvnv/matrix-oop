#include "matrix_oop.h"

// Constructor & Destructor

Matrix::Matrix() : rows_(S_AR), cols_(S_AR) { CreateMatrix(); }

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    CreateMatrix();
}

Matrix::Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
    CreateMatrix();
    CopyMatrix(other);
}

Matrix::Matrix(Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.SetNull();
}

Matrix::~Matrix() { DestroyMatrix(); }

// Operators

Matrix Matrix::operator+(const Matrix &other) {
    Matrix temp(*this);
    temp.SumMatrix(other);
    return temp;
}

Matrix Matrix::operator-(const Matrix &other) {
    Matrix temp(*this);
    temp.SubMatrix(other);
    return temp;
}

Matrix Matrix::operator=(const Matrix &other) {
    DestroyMatrix();
    this->~Matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
    CopyMatrix(other);
    return *this;
}

Matrix Matrix::operator=(Matrix &&other) {
    if (this != &other) {
        DestroyMatrix();
        matrix_ = other.matrix_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        other.matrix_ = nullptr;
        other.rows_ = 0;
        other.cols_ = 0;
    }
    return *this;
}

bool Matrix::operator==(const Matrix &other) { return EqMatrix(other); }

Matrix &Matrix::operator+=(const Matrix &other) {
    SumMatrix(other);
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    SubMatrix(other);
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    MulMatrix(other);
    return *this;
}

Matrix &Matrix::operator*=(double num) {
    MulNumber(num);
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) {
    Matrix temp(*this);
    temp.MulMatrix(other);
    return temp;
}

Matrix Matrix::operator*(const double num) {
    Matrix temp(*this);
    temp.MulNumber(num);
    return temp;
}

double &Matrix::operator()(int rows, int columns) {
    if (rows >= rows_ || columns >= cols_) {
        throw std::invalid_argument("\nIndex out of range\n");
    }
    return matrix_[rows][columns];
}

// Methods

int Matrix::EqualMatrix(const Matrix &other) {
    return (other.cols_ == this->cols_) && (other.rows_ == this->rows_);
}

void Matrix::SumMatrix(const Matrix &other) {
    if (!EqualMatrix(other)) {
        throw std::invalid_argument("\nRows and columns do not match\n");
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void Matrix::SubMatrix(const Matrix &other) {
    if (!EqualMatrix(other)) {
        throw std::invalid_argument("\nRows and columns do not match\n");
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] *= num;
        }
    }
}

void Matrix::MulMatrix(const Matrix &other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("\nWrong count of rows or columns\n");
    }
    Matrix Temp(rows_, other.cols_);

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < other.rows_; k++) {
                Temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    MoveMatrix(Temp);
}

Matrix Matrix::Transpose() {
    Matrix Temp(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            Temp.matrix_[j][i] = matrix_[i][j];
        }
    }
    return Temp;
}

Matrix Matrix::CalcComplements() {
    if (rows_ != cols_) {
        throw std::invalid_argument("\nThe matrix must be square\n");
    }

    Matrix complements(rows_, cols_);

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            Matrix submatrix = Submatrix(i, j);
            double det = submatrix.Determinant();
            complements.matrix_[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * det;
        }
    }
    return complements;
}

Matrix Matrix::Submatrix(int row, int col) {
    if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
        throw std::out_of_range("\nIndex outside the matrix\n");
    }

    Matrix sub(rows_ - 1, cols_ - 1);
    for (int i = 0, sub_i = 0; i < rows_; ++i) {
        if (i == row) continue;
        for (int j = 0, sub_j = 0; j < cols_; ++j) {
            if (j == col) continue;
            sub.matrix_[sub_i][sub_j] = matrix_[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return sub;
}

double Matrix::Determinant() {
    if (rows_ != cols_) {
        throw std::invalid_argument("\nThe matrix must be square\n");
    } else if (rows_ <= 0) {
        throw std::invalid_argument("\nThe matrix is not correct\n");
    }

    if (rows_ == 1) {
        return matrix_[0][0];
    } else if (rows_ == 2) {
        return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    }

    double det = 0.0;

    for (int j = 0; j < cols_; ++j) {
        Matrix submatrix = Submatrix(0, j);
        det += (j % 2 == 0 ? 1 : -1) * matrix_[0][j] * submatrix.Determinant();
    }

    return det;
}

Matrix Matrix::InverseMatrix() {
    Matrix temp(*this);
    double det = temp.Determinant();
    if (temp.rows_ != temp.cols_) {
        throw std::invalid_argument("\nRows and columns must match\n");
    } else if (std::fabs(det) < EPS) {
        throw std::logic_error("\nDeterminant value can't be equal to 0\n");
    }

    temp = temp.CalcComplements();
    temp = temp.Transpose();
    temp.MulNumber(1 / det);

    return temp;
}

// Accessors & mutators

int Matrix::GetRows() const { return rows_; }

int Matrix::GetCols() const { return cols_; }

void Matrix::SetRows(int rows) {
    if (rows < 1) {
        throw std::invalid_argument("\nThere must be more than 1 rows\n");
    }
    Matrix tempM(rows, cols_);

    for (int i = 0; i < ((rows_ < rows) ? rows_ : rows); i++) {
        for (int j = 0; j < cols_; j++) {
            tempM.matrix_[i][j] = matrix_[i][j];
        }
    }

    *this = tempM;
}

void Matrix::SetColumns(int columns) {
    if (columns < 1) {
        throw std::invalid_argument("\nThere must be more than 1 columns\n");
    }
    Matrix tmpMatrix(rows_, columns);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (j >= cols_) {
                continue;
            } else {
                tmpMatrix.matrix_[i][j] = matrix_[i][j];
            }
        }
    }
    int rows = rows_;
    DestroyMatrix();
    rows_ = rows;
    cols_ = columns;
    CreateMatrix();
    CopyMatrix(tmpMatrix);
    tmpMatrix.~Matrix();
}

// Friend method

Matrix operator*(double num, Matrix &other) {
    Matrix resultMatrix(other);
    resultMatrix.MulNumber(num);
    return resultMatrix;
}

// Private methods

void Matrix::CreateMatrix() {
    matrix_ = new double *[rows_]();
    for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_]();
    }
}

void Matrix::DestroyMatrix() {
    if (matrix_) {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
}

void Matrix::CopyMatrix(const Matrix &other) {
    for (int i = 0; i < other.rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

void Matrix::MoveMatrix(Matrix &other) {
    DestroyMatrix();
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    other.matrix_ = nullptr;
}

void Matrix::SetNull() {
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
}

bool Matrix::EqMatrix(const Matrix &other) const {
    bool result = true;
    if (matrix_ == nullptr || other.matrix_ == nullptr) {
        throw std::length_error("\nMatrix doesn't exist\n");
    }
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        result = false;
    }
    for (int i = 0; i < rows_ && result == true; i++) {
        for (int j = 0; j < cols_ && result == true; j++) {
            if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
                result = false;
            }
        }
    }
    return result;
}
