#include <Python.h>
#include "libconic.h"

static PyObject *PyconicException = NULL;

static PyObject *pm_open(PyObject *self, PyObject *args);
static PyObject *pm_is_open(PyObject *self, PyObject *args);
static PyObject *pm_move(PyObject *self, PyObject *args);
static PyObject *pm_close(PyObject *self, PyObject *args);

static PyMethodDef PythonMethods[] = {
	{"open", pm_open, METH_VARARGS, "opens the connection"},
	{"is_open", pm_is_open, METH_VARARGS, "checks if connection is open"},
	{"move", pm_move, METH_VARARGS, "moves the arm"},
	{"close", pm_close, METH_VARARGS, "closes the connection"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyconic_module = {
	PyModuleDef_HEAD_INIT,
	"pyconic",
	"Python interface for the libconic",
	-1,
	PythonMethods
};

static PyObject *pm_open(PyObject *self, PyObject *args)
{
	if (PyTuple_Size(args) != 0) {
		PyErr_SetString(PyExc_TypeError, "open takes no arguments");
		return NULL;
	}

	return PyLong_FromLong(conic_open());
}

static PyObject *pm_is_open(PyObject *self, PyObject *args)
{
	long fd = -1;

	if (!PyArg_ParseTuple(args, "l", &fd)) {
		PyErr_SetString(PyExc_TypeError, "open takes 1 argument");
		return NULL;
	}

	return PyLong_FromLong(conic_is_open((int)fd));
}

static PyObject *pm_move(PyObject *self, PyObject *args)
{
	long fd;
	float s1, s2, s3, s4, s5, s6;

	if (!PyArg_ParseTuple(args, "lffffff", &fd, &s1, &s2, &s3, &s4, &s5, &s6)) {
		PyErr_SetString(PyExc_TypeError, \
			"move takes 7 arguments - fd and 6 servo values");
		return NULL;
	}

	return PyLong_FromLong(conic_move(fd, s1, s2, s3, s4, s5, s6));
}

static PyObject *pm_close(PyObject *self, PyObject *args)
{
	long fd = -1;

	if (!PyArg_ParseTuple(args, "l", &fd)) {
		PyErr_SetString(PyExc_TypeError, "close takes 1 argument");
		return NULL;
	}

	conic_close((int)fd);

	Py_RETURN_NONE;
}

PyMODINIT_FUNC PyInit_pyconic(void)
{
	PyObject *Module = PyModule_Create(&pyconic_module);
	PyconicException = PyErr_NewException("pyconic.PyconicException", \
			NULL, NULL);

	PyModule_AddObject(Module, "PyconicExceptuin", PyconicException);
	return Module;
}
