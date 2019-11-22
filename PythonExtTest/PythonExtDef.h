// PythonExtDef.h

#ifndef PYTHON_EXT_DEF_H
#define PYTHON_EXT_DEF_H

/**
 * 定义初始化Python模块的方法
 * @param ModuleName 模块名
 */
#define DECLARE_PY_MODULE_INIT_FUNC(ModuleName) \
    int Init##ModuleName##Module(PyObject* pModule); \
    PyTypeObject* Get##ModuleName##PyType()

/**
 * 实现初始化Python模块的方法(注意这个宏只能供基类使用)
 * @param ModuleName 模块名
 * @param ClassName Python模块所包装的C++类名
 */
#define IMPLEMENT_PY_BASE_MODULE_INIT_FUNC(ModuleName, ClassName) \
    DECLARE_MODULE_PY_TYPE(ModuleName, ClassName); \
    int Init##ModuleName##Module(PyObject* pModule) \
    { \
        if (PyType_Ready(&s_st##ClassName##PyType) < 0) return -1; \
        Py_INCREF(&s_st##ClassName##PyType); \
        PyModule_AddObject(pModule, #ModuleName, (PyObject *)&s_st##ClassName##PyType); \
        return 0; \
    } \
    PyTypeObject* Get##ModuleName##PyType() \
    { \
        return &s_st##ClassName##PyType; \
    }

/**
 * 实现初始化Python模块的方法(注意这个宏只能供子类使用)
 * @param ModuleName 模块名
 * @param ClassName Python模块所包装的C++类名
 */
#define IMPLEMENT_PY_MODULE_INIT_FUNC(ModuleName, ClassName, BaseModuleName) \
    DECLARE_MODULE_PY_TYPE(ModuleName, ClassName); \
    int Init##ModuleName##Module(PyObject* pModule) \
    { \
        s_st##ClassName##PyType.tp_base = Get##BaseModuleName##PyType(); \
        if (PyType_Ready(&s_st##ClassName##PyType) < 0) return -1; \
        Py_INCREF(&s_st##ClassName##PyType); \
        PyModule_AddObject(pModule, #ModuleName, (PyObject *)&s_st##ClassName##PyType ); \
        return 0; \
    } \
    PyTypeObject* Get##ModuleName##PyType() \
    { \
        return &s_st##ClassName##PyType; \
    }

/**
 * 初始化模块的Python类型
 * @param ModuleName 模块名
 * @param ClassName Python模块所包装的C++类名
 */
#define DECLARE_MODULE_PY_TYPE(ModuleName, ClassName) \
    PyTypeObject s_st##ClassName##PyType = \
    { \
        PyObject_HEAD_INIT(NULL) \
        0, \
        #ModuleName, \
        sizeof(ClassName##Py), \
        0, \
        (destructor)Free##ModuleName##Py, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, \
        #ModuleName " objects", \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        ClassName##PyMethods, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        0, \
        (initproc)Init##ModuleName##Py, \
        0, \
        Create##ModuleName##Py, \
    }

#endif
