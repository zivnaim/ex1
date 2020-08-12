#include <stdio.h>
#include "ErrorCode.h"

bool error_isSuccess(ErrorCode code) {
    return code == ERROR_SUCCESS;
}

const char* error_getErrorMessage(ErrorCode code) {
    switch (code)
    {
    case ERROR_SUCCESS:
        char* s = "Error success.";
        return s;
        break;
    case ERROR_FAIL_ALLOCATE:
        char* s = "One of the memory allocates failed.";
        return s;
        break;
    case ERROR_NULL_ARGUMENT:
        char* s = "One of the arguments is a NULL pointer";
        return s;
        break;
    case ERROR_NOT_EXIST_INDEX:
        char* s = "The function called with index out of the matrix range";
        return s;
        break;
    case ERROR_ILLEGAL_ACTION:
        char* s = "The action is illegl or not set action. ";
        return s;
        break;
    default:
        char* s = "Not an ERROR CODE";
        return s;
        break;
    }
}