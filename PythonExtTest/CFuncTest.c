#include <Python.h>

static PyObject* sum(PyObject* self, PyObject* args)
{
    int a;
    int b;

    if (!PyArg_ParseTuple(args, "ii", &a, &b))
    {
        PyErr_SetString(PyExc_Exception, "Parameters invalid");
        return NULL;
    }
    return Py_BuildValue("i", a + b);
}

static PyMethodDef UtilsMethods[] =
{
    {"sum", sum, METH_VARARGS, "Calculate the sum of two integers"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initutils()
{
    Py_InitModule("utils", UtilsMethods);
}

