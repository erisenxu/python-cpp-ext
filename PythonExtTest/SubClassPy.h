
#ifndef SUB_CLASS_PY_H
#define SUB_CLASS_PY_H

#include "BasePy.h"

typedef struct tagSubClassPy
{
    BasePy oBase;
    PyObject* pOtherPy;
} SubClassPy;

DECLARE_PY_MODULE_INIT_FUNC(SubClass);

#endif

