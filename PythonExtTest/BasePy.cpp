
#include "BasePy.h"
#include <memory>

static void FreeBasePy(BasePy* pSelf)
{
    delete pSelf->pBase;
    pSelf->ob_type->tp_free((PyObject*)pSelf);
    printf("%s\n", __FUNCTION__);
}

static PyObject* CreateBasePy(PyTypeObject* pTypeObj, PyObject* /*pArgs*/, PyObject* /*pKwds*/)
{
    BasePy* pSelf = (BasePy*)pTypeObj->tp_alloc(pTypeObj, 0);
    if (pSelf)
    {
        pSelf->pBase = new Base;
    }
    return (PyObject*)pSelf;
}

static int InitBasePy(BasePy* pSelf, PyObject* pArgs, PyObject* pKwds)
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
        pSelf->pBase->SetName(szName);
    }

    return 0;
}

static PyObject* BaseSetNamePy(BasePy* pSelf, PyObject* pArgs)
{
    const char* szName = NULL;

    if (!PyArg_ParseTuple(pArgs, "|s", &szName))
    {
        PyErr_SetString(PyExc_Exception, "Invalid parameter for Base:setName");
        return NULL;
    }

    pSelf->pBase->SetName(szName ? szName : "");

    return Py_None;
}

static PyObject* BaseGetNamePy(BasePy* pSelf, PyObject* /*pArgs*/)
{
    return Py_BuildValue("s", pSelf->pBase->GetName().c_str());
}

static PyMethodDef BasePyMethods[] =
{
    {"setName", (PyCFunction)BaseSetNamePy, METH_VARARGS, "Sets the name of the object Base"},
    {"getName", (PyCFunction)BaseGetNamePy, METH_NOARGS, "Gets the name of the object Base"},
    {NULL, NULL, 0, NULL}
};

IMPLEMENT_PY_BASE_MODULE_INIT_FUNC(Base, Base);

