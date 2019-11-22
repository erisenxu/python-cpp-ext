
#ifndef OTHER_PY_H
#define OTHER_PY_H

#include <Python.h>
#include "Other.h"
#include "PythonExtDef.h"

typedef struct tagOtherPy
{
    PyObject_HEAD
    Other* pOther;
} OtherPy;

DECLARE_PY_MODULE_INIT_FUNC(Other);

#endif

