#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

struct Matrix
{
    double** matrix; 
    int width;
    int height;
};
typedef struct Matrix Matrix;

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    if (matrix == NULL) { //check the args is ok
        return ERROR_NULL_ARGUMENT;
    }
    PMatrix pm = (PMatrix) malloc(sizeof(Matrix)); //allocate memory to the struct
    if (pm == NULL) {
        return ERROR_FAIL_ALLOCATE;
    }
    pm->matrix = (double**) malloc(height * sizeof(double*)); //allocate the inside array 
    if (pm->matrix == NULL) {
        free(pm);
        return ERROR_FAIL_ALLOCATE;
    }
    pm->height = height;
    pm->width = width;
    for (int i = 0; i < height; ++i) {
        //allocate the rows and put zero inside.
        pm->matrix[i] = calloc(width, sizeof(double));
        if (pm->matrix[i] == NULL) {
            //I NEED TO FREE THE MEMORY!!!!!    
            return ERROR_FAIL_ALLOCATE;
        }
    } 
    *matrix = pm;
    return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    ErrorCode ec = matrix_create(result, source->height, source->width);
    if (!error_isSuccess(ec)) {
        return ec;
    } 
    for (int i = 0; i < source->height; ++i) {
        for (int j = 0; j < source->width; ++j) {
            (*result)->matrix[i][j] = source->matrix[i][j];
        }
    }
}

void matrix_destroy(PMatrix matrix) {
    for (int i = 0; i < matrix->height; ++i) {
        free(matrix->matrix[i]);
    }
    free (matrix->matrix);
    free (matrix);
}


ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    if (matrix == NULL || result == NULL) { //check the args is ok
        return ERROR_NULL_ARGUMENT;
    }
    *result = matrix->height;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
    if (matrix == NULL || result == NULL) { //check the args is ok
        return ERROR_NULL_ARGUMENT;
    }
    *result = matrix->width;
    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value) {
    if (matrix == NULL) { //check the args is ok
        return ERROR_NULL_ARGUMENT;
    }
    if (rowIndex >= matrix->height || colIndex >= matrix->width) {
        return ERROR_NOT_EXIST_INDEX;
    }
    matrix->matrix[rowIndex][colIndex] = value;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value) {
    if (matrix == NULL || value == NULL) { //check the args is ok
        return ERROR_NULL_ARGUMENT;
    }
    if (rowIndex >= matrix->height || colIndex >= matrix->width) {
        return ERROR_NOT_EXIST_INDEX;
    }
    *value = matrix->matrix[rowIndex][colIndex];
    return ERROR_SUCCESS;            
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    if (lhs->height != rhs->height || lhs->width != rhs->width) {
        return ERROR_ILLEGAL_ACTION;
    }
    PMatrix* new;
    ErrorCode ec = matrix_create(new, lhs->height, lhs->width);
    if (!error_isSuccess(ec)) {
        return ec;
    }
    PMatrix mnew = *new;
    for (int i = 0; i < lhs->height; ++i) {
        for (int j = 0; j < lhs->width; ++j) {
            mnew->matrix[i][j] = lhs->matrix[i][j] + rhs->matrix[i][j];
        }
    }
    *result = mnew;
    return ERROR_SUCCESS;
}

///////////
ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    if (lhs->width != rhs->height) {
        return ERROR_ILLEGAL_ACTION;
    }
    if (result == NULL) {
        return ERROR_NULL_ARGUMENT;
    } 
    PMatrix pm; 
    ErrorCode ec = matrix_create(&pm, lhs->height, rhs->width);
    if (!error_isSuccess(ec)) {
        return ec;
    }
    double sum = 0.0;
    for (int i = 0; i < pm->height; ++i) {
        for (int j = 0; j < pm->width; ++j) {
            sum = 0.0;
            for (int k = 0; k < lhs->width; ++k) {
                sum += lhs->matrix[i][k] * rhs->matrix[k][j];
            }
            pm->matrix[i][j] = sum;
           // pm->matrix[i][j] = matrix_vectorMulitply(lhs, i, rhs, j);
        } 
    }
    *result = pm;
    return ERROR_SUCCESS;
}

/*double matrix_vectorMulitply(CPMatrix lhs, int row, CPMatrix rhs, int col) {
    double sum = 0.0;
    for (int i = 0; i < lhs->width; ++i) {
        sum += lhs->matrix[row][i] * rhs->matrix[i][col];
    }
    return sum;
}*/

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
    if (matrix == NULL) { //check the args is ok
        return ERROR_NULL_ARGUMENT;
    }
    for (int i = 0; i < matrix->height; ++i) {
        for (int j = 0; j < matrix->width; ++j) {
            matrix->matrix[i][j] = matrix->matrix[i][j] * scalar;
        }
    }
    return ERROR_SUCCESS;
}