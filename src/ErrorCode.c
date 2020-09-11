#include <stdio.h>
#include "ErrorCode.h"

bool error_isSuccess(ErrorCode code) {
    return code == ERROR_SUCCESS;
}

const char* error_getErrorMessage(ErrorCode code) {
    switch (code) {
        case ERROR_SUCCESS:
            return "Error success.";
        case ERROR_FAIL_ALLOCATE: 
            return "One of the memory allocates failed.";
        case ERROR_NULL_ARGUMENT:
            return "One of the arguments is a NULL pointer";
        case ERROR_NOT_EXIST_INDEX:
            return "The function called with index out of the matrix range";
        case ERROR_ILLEGAL_ACTION:
            return "The action is illegl or not set action.";
        case ERROR_MATRIX_SIZE_ILLEGAL:
            return "Can't create matrix with size 0";
        default:
            return "Not an ERROR CODE";
    }
}
