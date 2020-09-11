#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

struct Matrix
{
    double** matrix; 
    uint32_t width;
    uint32_t height;
};
typedef struct Matrix Matrix;

ErrorCode matrix_create(PMatrix* matrix, const uint32_t height, const uint32_t width) {
    if (height == 0 || width == 0) {
        return ERROR_MATRIX_SIZE_ILLEGAL;
    }
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
    //initialize the variables.
    pm->height = height;
    pm->width = width;
    for (uint32_t i = 0; i < height; ++i) {
        pm->matrix[i] = calloc(width, sizeof(double)); //allocate the rows and put zero inside.
        if (pm->matrix[i] == NULL) { //in case of fail allocate, free all the memmory.
            for (uint32_t k = 0; k < i; k++){
                free(pm->matrix[k]);
            }
            free (pm->matrix);
            free (pm);
            return ERROR_FAIL_ALLOCATE;
        }
    } 
    *matrix = pm;
    return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    //check if one of the argumnets is NULL
    if (source == NULL || result == NULL) {
        return ERROR_NULL_ARGUMENT;
    }
    ErrorCode ec = matrix_create(result, source->height, source->width);
    if (!error_isSuccess(ec)) {
        return ec;
    } 
    //copy the values. 
    for (uint32_t i = 0; i < (*result)->height; ++i) {
        for (uint32_t j = 0; j < (*result)->width; ++j) {
            (*result)->matrix[i][j] = source->matrix[i][j];
        }
    }
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
    if (matrix == NULL) {
        return;
    }
    //free each rows
    for (uint32_t i = 0; i < matrix->height; ++i) {
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
    //check if the indexes is in the range
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
    //check if the indexes is in the range
    if (rowIndex >= matrix->height || colIndex >= matrix->width) {
        return ERROR_NOT_EXIST_INDEX;
    }
    *value = matrix->matrix[rowIndex][colIndex];
    return ERROR_SUCCESS;            
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    if (result == NULL || lhs == NULL || rhs == NULL) { //check if the args ok
        return ERROR_NULL_ARGUMENT;
    }
    if (lhs->height != rhs->height || lhs->width != rhs->width) { //check the sizes are the same.
        return ERROR_ILLEGAL_ACTION;
    }
    ErrorCode ec = matrix_create(result, lhs->height, lhs->width);
    if (!error_isSuccess(ec)) {
       return ec; 
    }
    //set values in the new matrix.
    for (uint32_t i = 0; i < lhs->height; ++i) {
        for (uint32_t j = 0; j < lhs->width; ++j) {
            (*result)->matrix[i][j] = lhs->matrix[i][j] + rhs->matrix[i][j];
        }
    }
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    if (result == NULL || lhs == NULL || rhs == NULL) {
        return ERROR_NULL_ARGUMENT;
    } 
    if (lhs->width != rhs->height) { //check the action is legal
        return ERROR_ILLEGAL_ACTION;
    }
    ErrorCode ec = matrix_create(result, lhs->height, rhs->width);
    if (!error_isSuccess(ec)) {
       return ec;
    }
    //set values in the matrix. 
    double sum = 0.0;
    for (uint32_t i = 0; i < (*result)->height; ++i) {
        for (uint32_t j = 0; j < (*result)->width; ++j) {
            //multiply vectors
            sum = 0.0;
            for (uint32_t k = 0; k < lhs->width; ++k) {
                sum += (lhs->matrix[i][k] * rhs->matrix[k][j]);
            }
            (*result)->matrix[i][j] = sum;
        } 
    }
    return ERROR_SUCCESS;
}


ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
    if (matrix == NULL) { //check the args is ok
        return ERROR_NULL_ARGUMENT;
    }
    for (uint32_t i = 0; i < matrix->height; ++i) {
        for (uint32_t j = 0; j < matrix->width; ++j) {
            matrix->matrix[i][j] = matrix->matrix[i][j] * scalar;
        }
    }
    return ERROR_SUCCESS;
}
