
#include "OtherPy.h"

static void FreeOtherPy(OtherPy* pSelf)
{
    delete pSelf->pOther;
    pSelf->ob_type->tp_free((PyObject*)pSelf);
    printf("%s\n", __FUNCTION__);
}

static PyObject* CreateOtherPy(PyTypeObject* pTypeObj, PyObject* /*pArgs*/, PyObject* /*pKwds*/)
{
    OtherPy* pSelf = (OtherPy*)pTypeObj->tp_alloc(pTypeObj, 0);
    if (pSelf)
    {
        pSelf->pOther = new Other;
    }
    return (PyObject*)pSelf;
}

static int InitOtherPy(OtherPy* pSelf, PyObject* pArgs, PyObject* pKwds)
{
    const char* szName = NULL;
    static const char* szKwList[] = {"name", NULL};

    if (!PyArg_ParseTupleAndKeywords(pArgs, pKwds, "|s", (char**)szKwList,
                                     &szName))
    {
        return -1;
    }

    if (szName)
    {
        pSelf->pOther->SetName(szName);
    }

    return 0;
}

static PyObject* OtherSetNamePy(OtherPy* pSelf, PyObject* pArgs)
{
    const char* szName = NULL;

    if (!PyArg_ParseTuple(pArgs, "|s", &szName))
    {
        PyErr_SetString(PyExc_Exception, "Invalid parameter for Other:setName");
        return NULL;
    }

    pSelf->pOther->SetName(szName ? szName : "");

    return Py_None;
}

static PyObject* OtherGetNamePy(OtherPy* pSelf, PyObject* /*pArgs*/)
{
    return Py_BuildValue("s", pSelf->pOther->GetName().c_str());
}

static PyMethodDef OtherPyMethods[] =
{
    {"setName", (PyCFunction)OtherSetNamePy, METH_VARARGS, "Sets the name of the object Other"},
    {"getName", (PyCFunction)OtherGetNamePy, METH_NOARGS, "Gets the name of the object Other"},
    {NULL, NULL, 0, NULL}
};

IMPLEMENT_PY_BASE_MODULE_INIT_FUNC(Other, Other);

