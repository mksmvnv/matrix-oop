# Matrix OOP

This is an educational implementation of the matrix_oop library.

## Information

C++ is a programming language based on the C language for implementing programs using an object-oriented approach. This means that the C++ syntax rules are derived directly from C, so most C code can be copied into C++ programs and successfully compiled.
For the most part, C++ only adds or modifies capabilities for the programmer, rather than taking away anything, so it's easier to talk about the differences (see Resources) than the similarities when it comes to C++.

### An example of a matrix class in C++

```cpp
class Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated

    public:
        Matrix();              // Default constructor
        ~Matrix();             // Destructor

        void SumMatrix(const Matrix& other); 
        // Other methods..
}
```

### A reminder of the matrix basics

Matrix is a rectangular table of numbers arranged in m rows and n columns:

```text
    1 2 3
A = 4 5 6
    7 8 9
```

```text
     1  2  3  4
В =  5  6  7  8
     9 10 11 12
```

You can get the desired element using indices as follows A[1,1] = 1, where the first index is the row number, the second is the column number.

The order of a matrix is the number of its rows or columns. \
The main diagonal of a square matrix is the diagonal from the upper left to the lower right corner. \

A rectangular matrix (B) is a matrix with the number of rows not equal to the number of columns. \
A square matrix (A) is a matrix with the number of rows equal to the number of columns.

### Matrix operations

Below is a brief description of the matrix operations that need to be implemented in the development library.
They are similar to the operations you performed earlier in "Structured Programming", so you can see a more detailed description of them there.
Note that some operations have exceptional situations that require special handling using the exception mechanism.

| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const Matrix& other)` | Checks matrices for equality with each other. |  |
| `void SumMatrix(const Matrix& other)` | Adds the second matrix to the current one | different matrix dimensions. |
| `void SubMatrix(const Matrix& other)` | Subtracts another matrix from the current one | different matrix dimensions. |
| `void MulNumber(const double num)` | Multiplies the current matrix by a number. |  |
| `void MulMatrix(const Matrix& other)` | Multiplies the current matrix by the second matrix. | The number of columns of the first matrix is not equal to the number of rows of the second matrix. |
| `Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it. |  |
| `Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it. | The matrix is not square. |
| `double Determinant()` | Calculates and returns the determinant of the current matrix. | The matrix is not square. |
| `Matrix InverseMatrix()` | Calculates and returns the inverse matrix. | Matrix determinant is 0. |

Apart from those operations, you also need to implement constructors and destructors:

| Method | Description |
| ----------- | ----------- |
| `Matrix()` | A basic constructor that initialises a matrix of some predefined dimension. |  
| `Matrix(int rows, int cols)` | Parametrized constructor with number of rows and columns. |
| `Matrix(const Matrix& other)` | Copy constructor. |
| `Matrix(Matrix&& other)` | Move constructor. |
| `~Matrix()` | Destructor. |

And you also need to overload the following operators, partly corresponding to the operations above:

| Operator | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `+`      | Addition of two matrices. | Different matrix dimensions. |
| `-`   | Subtraction of one matrix from another. | Different matrix dimensions. |
| `*`  | Matrix multiplication and matrix multiplication by a number. | The number of columns of the first matrix does not equal the number of rows of the second matrix. |
| `==`  | Checks for matrices equality (`EqMatrix`). | |
| `=`  | Assignment of values from one matrix to another one. | |
| `+=`  | Addition assignment (`SumMatrix`) | different matrix dimensions. |
| `-=`  | Difference assignment (`SubMatrix`) | different matrix dimensions. |
| `*=`  | Multiplication assignment (`MulMatrix`/`MulNumber`). | The number of columns of the first matrix does not equal the number of rows of the second matrix. |
| `(int i, int j)`  | Indexation by matrix elements (row, column). | Index is outside the matrix. |

## Implementation of the matrix_oop.h library functions

- The program must be developed in C++ language of C++17 standard using gcc compiler;
- The program code must be located in the src folder;
- When writing code it is necessary to follow the Google style;
- Implement the matrix as an `Matrix` class;
- Use only the `matrix_`, `rows_` and `cols_` fields as private;
- Implement the access to private fields `rows_` and `cols_` via accessor and mutator. If the matrix increases in size, it is filled with zeros. If it decreases in size, the excess is simply discarded;
- Make it as a static library (with matrix_oop.h header file);
- Implement the operations described [above](#matrix-operations);
- Overload the operators according to the table in the chapter [above](#matrix-operations);
- Prepare full coverage of library functions code with unit-tests using the GTest library;
- Provide a Makefile for building the library and tests (with targets all, clean, test, matrix_oop.a).
