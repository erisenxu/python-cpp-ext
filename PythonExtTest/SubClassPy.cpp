
#include "SubClassPy.h"
#include "SubClass.h"
#include "OtherPy.h"

static void FreeSubClassPy(SubClassPy* pSelf)
{
    Py_XDECREF(pSelf->pOtherPy);
    GetBasePyType()->tp_dealloc((PyObject*)pSelf);
}

static PyObject* CreateSubClassPy(PyTypeObject* pTypeObj, PyObject* /*pArgs*/, PyObject* /*pKwds*/)
{
    SubClassPy* pSelf = (SubClassPy*)pTypeObj->tp_alloc(pTypeObj, 0);
    if (pSelf)
    {
        pSelf->oBase.pBase = new SubClass;
        pSelf->pOtherPy = Py_None;
    }
    return (PyObject*)pSelf;
}

static int InitSubClassPy(SubClassPy* pSelf, PyObject* pArgs, PyObject* pKwds)
{
    const char* szName = NULL;
    int iValue = 0;
    static const char* szKwList[] = {"name", "value", NULL};

    if (!PyArg_ParseTupleAndKeywords(pArgs, pKwds, "|si", (char**)szKwList,
                                     &szName, &iValue))
    {
        return -1;
    }

    if (szName)
    {
        pSelf->oBase.pBase->SetName(szName);
    }

    ((SubClass*)pSelf->oBase.pBase)->SetValue(iValue);

    return 0;
}

static PyObject* SubClassSetValuePy(SubClassPy* pSelf, PyObject* pArgs)
{
    int iValue = 0;

    if (!PyArg_ParseTuple(pArgs, "|i", &iValue))
    {
        PyErr_SetString(PyExc_Exception, "Invalid parameter for Base:setValue");
        return NULL;
    }

    ((SubClass*)pSelf->oBase.pBase)->SetValue(iValue);

    return Py_None;
}

static PyObject* SubClassGetValuePy(SubClassPy* pSelf, PyObject* /*pArgs*/)
{
    return Py_BuildValue("i", ((SubClass*)pSelf->oBase.pBase)->GetValue());
}

static PyObject* SubClassSetOtherPy(SubClassPy* pSelf, PyObject* pArgs)
{
    PyObject* pOtherPy = NULL;

    if (!PyArg_ParseTuple(pArgs, "O", &pOtherPy))
    {
        PyErr_SetString(PyExc_Exception, "Invalid parameter for SubClass:setOther");
        return NULL;
    }

    if (pOtherPy == Py_None)
    {
        PyErr_SetString(PyExc_Exception, "Null parameter for SubClass:setOther");
        return NULL;
    }

    if (!PyObject_TypeCheck(pOtherPy, GetOtherPyType()))
    {
        PyErr_SetString(PyExc_Exception, "Invalid parameter for SubClass:setOther, the parameter is not an Other object");
        return NULL;
    }

    ((SubClass*)pSelf->oBase.pBase)->SetOther((Other*)((OtherPy*)pOtherPy)->pOther);
    if (pSelf->pOtherPy != pOtherPy)
    {
        Py_XDECREF(pSelf->pOtherPy);
        pSelf->pOtherPy = pOtherPy;
        Py_XINCREF(pSelf->pOtherPy);
    } 

    return Py_None;
}

static PyObject* SubClassGetOtherPy(SubClassPy* pSelf, PyObject* /*pArgs*/)
{
    Py_XINCREF(pSelf->pOtherPy);
    return pSelf->pOtherPy;
}

static PyMethodDef SubClassPyMethods[] =
{
    {"setValue", (PyCFunction)SubClassSetValuePy, METH_VARARGS, "Sets the value of the object SubClass"},
    {"getValue", (PyCFunction)SubClassGetValuePy, METH_NOARGS, "Gets the value of the object SubClass"},
    {"setOther", (PyCFunction)SubClassSetOtherPy, METH_VARARGS, "Sets the other object of the object SubClass"},
    {"getOther", (PyCFunction)SubClassGetOtherPy, METH_NOARGS, "Gets the other object of the object SubClass"},
    {NULL, NULL, 0, NULL}
};

IMPLEMENT_PY_MODULE_INIT_FUNC(SubClass, SubClass, Base);

