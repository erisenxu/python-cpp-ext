
#ifndef BASE_PY_H
#define BASE_PY_H

#include <Python.h>
#include "Base.h"
#include "PythonExtDef.h"

typedef struct tagBasePy
{
    PyObject_HEAD
    Base* pBase;
} BasePy;

DECLARE_PY_MODULE_INIT_FUNC(Base);

#endif

