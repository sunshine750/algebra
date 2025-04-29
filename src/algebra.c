#include "algebra.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    memset(m.data, 0, sizeof(m.data));
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols)
    {
        fprintf(stderr, "Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows != b.rows || a.cols != b.cols)
    {
        fprintf(stderr, "Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows)
    {
        fprintf(stderr, "Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < b.cols; j++)
        {
            for (int k = 0; k < a.cols; k++)
            {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix scale_matrix(Matrix a, double k)
{
    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[i][j] = a.data[i][j] * k;
        }
    }
    return result;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix result = create_matrix(a.cols, a.rows);
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[j][i] = a.data[i][j];
        }
    }
    return result;
}

double det_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        fprintf(stderr, "Error: The matrix must be a square matrix.\n");
        return 0;
    }
    if (a.rows == 1)
    {
        return a.data[0][0];
    }
    if (a.rows == 2)
    {
        return a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0];
    }
    double det = 0;
    for (int p = 0; p < a.cols; p++)
    {
        Matrix sub = create_matrix(a.rows - 1, a.cols - 1);
        for (int i = 1; i < a.rows; i++)
        {
            int colIndex = 0;
            for (int j = 0; j < a.cols; j++)
            {
                if (j == p) continue;
                sub.data[i - 1][colIndex++] = a.data[i][j];
            }
        }
        det += (p % 2 == 0 ? 1 : -1) * a.data[0][p] * det_matrix(sub);
    }
    return det;
}

Matrix inv_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        fprintf(stderr, "Error: The matrix must be a square matrix.\n");
        return create_matrix(0, 0);
    }
    double det = det_matrix(a);
    if (fabs(det) < 1e-12)
    {
        fprintf(stderr, "Error: The matrix is singular.\n");
        return create_matrix(0, 0);
    }
    Matrix result = create_matrix(a.rows, a.cols);
    if (a.rows == 2)
    {
        result.data[0][0] = a.data[1][1] / det;
        result.data[0][1] = -a.data[0][1] / det;
        result.data[1][0] = -a.data[1][0] / det;
        result.data[1][1] = a.data[0][0] / det;
        return result;
    }
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            Matrix sub = create_matrix(a.rows - 1, a.cols - 1);
            for (int row = 0; row < a.rows; row++)
            {
                if (row == i) continue;
                int colIndex = 0;
                for (int col = 0; col < a.cols; col++)
                {
                    if (col == j) continue;
                    sub.data[row < i ? row : row - 1][colIndex++] = a.data[row][col];
                }
            }
            result.data[j][i] = (i + j) % 2 == 0 ? 1 : -1 * det_matrix(sub) / det;
        }
    }
    return result;
}

int rank_matrix(Matrix a)
{
    // ToDo: Implement rank calculation (e.g., Gaussian elimination)
    return 0;
}

double trace_matrix(Matrix a)
{
    if (a.rows != a.cols)
    {
        fprintf(stderr, "Error: The matrix must be a square matrix.\n");
        return 0;
    }
    double trace = 0;
    for (int i = 0; i < a.rows; i++)
    {
        trace += a.data[i][i];
    }
    return trace;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}