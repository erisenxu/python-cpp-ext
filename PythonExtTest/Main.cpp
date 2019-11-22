#include "SubClassPy.h"
#include "OtherPy.h"

static PyMethodDef TestsMethods[] =
{
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC inittests()
{
    PyObject* pModule = Py_InitModule("tests", TestsMethods);

    if (InitBaseModule(pModule) != 0) return;
    if (InitSubClassModule(pModule) != 0) return;
    if (InitOtherModule(pModule) != 0) return;
}

