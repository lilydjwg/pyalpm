/**
 * transaction.c : wrapper class around libalpm transactions
 *
 *  Copyright (c) 2011 Rémy Oudompheng <remy@archlinux.org>
 *
 *  This file is part of pyalpm.
 *
 *  pyalpm is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  pyalpm is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with pyalpm.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string.h>
#include <alpm.h>
#include <Python.h>
#include "package.h"
#include "db.h"
#include "util.h"

/** Transaction callbacks */
static PyObject *event_cb = NULL;
static PyObject *conv_cb = NULL;
static PyObject *progress_cb = NULL;

void pyalpm_trans_eventcb(pmtransevt_t event, void* data1, void *data2) {
}

void pyalpm_trans_convcb(pmtransconv_t question,
        void* data1, void *data2, void* data3, int* retcode) {
}

void pyalpm_trans_progresscb(pmtransprog_t op,
        const char* target_name, int percentage, size_t n_targets, size_t cur_target) {
}

/* Standard methods */
#define NOT_IMPLEMENTED(ret) \
  do { \
    PyErr_SetString(PyExc_NotImplementedError, "TODO !"); \
    return ret; \
  } while(0)

PyObject *pyalpm_trans_get_flags(PyObject *self, void *closure)
{
  NOT_IMPLEMENTED(NULL);
}
PyObject *pyalpm_trans_get_add(PyObject *self, void *closure)
{
  NOT_IMPLEMENTED(NULL);
}
PyObject *pyalpm_trans_get_remove(PyObject *self, void *closure)
{
  NOT_IMPLEMENTED(NULL);
}

/** Transaction flow */
PyObject* pyalpm_trans_init(PyObject *self, PyObject *args) {
  NOT_IMPLEMENTED(NULL);
}
PyObject* pyalpm_trans_prepare(PyObject *self, PyObject *args) {
  NOT_IMPLEMENTED(NULL);
}
PyObject* pyalpm_trans_commit(PyObject *self, PyObject *args) {
  NOT_IMPLEMENTED(NULL);
}
PyObject* pyalpm_trans_interrupt(PyObject *self, PyObject *args) {
  NOT_IMPLEMENTED(NULL);
}
PyObject* pyalpm_trans_release(PyObject *self, PyObject *args) {
  NOT_IMPLEMENTED(NULL);
}

/** Transaction contents */
PyObject* pyalpm_trans_add_pkg(PyObject *self, PyObject *args) {
  NOT_IMPLEMENTED(NULL);
}
PyObject* pyalpm_trans_remove_pkg(PyObject *self, PyObject *args) {
  NOT_IMPLEMENTED(NULL);
}
PyObject* pyalpm_trans_sysupgrade(PyObject *self, PyObject *args) {
  NOT_IMPLEMENTED(NULL);
}

/** Properties and methods */

static struct PyGetSetDef pyalpm_trans_getset[] = {
  /** filepaths */
  { "flags", (getter)pyalpm_trans_get_flags, NULL, "Transaction flags", NULL } ,
  { "to_add", (getter)pyalpm_trans_get_add, NULL, "Packages added by the transaction", NULL },
  { "to_remove", (getter)pyalpm_trans_get_remove, NULL, "Packages added by the transaction", NULL },
  { NULL }
};

static struct PyMethodDef pyalpm_trans_methods[] = {
  /* Execution flow */
  {"init",    pyalpm_trans_init,       METH_VARARGS, "init" },
  {"prepare", pyalpm_trans_prepare,    METH_VARARGS, "prepare" },
  {"commit",  pyalpm_trans_commit,     METH_VARARGS, "commit" },
  {"interrupt", pyalpm_trans_interrupt,METH_NOARGS,  "interrupt" },
  {"release", pyalpm_trans_release,    METH_NOARGS,  "release" },

  /* Transaction contents */
  {"add_pkg",    pyalpm_trans_add_pkg,    METH_VARARGS,
    "append a package addition to transaction"},
  {"remove_pkg", pyalpm_trans_remove_pkg, METH_VARARGS,
    "append a package removal to transaction"},
  {"sysupgrade", pyalpm_trans_sysupgrade, METH_VARARGS,
    "set the transaction to perform a system upgrade"},
};

PyTypeObject AlpmTransactionType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "alpm.TransactionClass",    /*tp_name*/
  0,                   /*tp_basicsize*/
  0,                   /*tp_itemsize*/
  0,                   /*tp_dealloc*/
  0,                   /*tp_print*/
  0,                   /*tp_getattr*/
  0,                   /*tp_setattr*/
  NULL,                /*tp_reserved*/
  0,                   /*tp_repr*/
  0,                   /*tp_as_number*/
  0,                   /*tp_as_sequence*/
  0,                   /*tp_as_mapping*/
  0,                   /*tp_hash */
  0,                   /*tp_call*/
  0,                   /*tp_str*/
  0,                   /*tp_getattro*/
  0,                   /*tp_setattro*/
  0,                   /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT, /*tp_flags*/
  "This class is the main interface to get/set libalpm options",
                      /* tp_doc */
  0,                  /* tp_traverse */
  0,                  /* tp_clear */
  0,                  /* tp_richcompare */
  0,                  /* tp_weaklistoffset */
  0,                  /* tp_iter */
  0,                  /* tp_iternext */
  pyalpm_trans_methods, /* tp_methods */
  0,                    /* tp_members */
  pyalpm_trans_getset,  /* tp_getset */
};

/* Initialization */
int init_pyalpm_transaction(PyObject *module) {
  AlpmTransactionType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&AlpmTransactionType) < 0)
    return -1;
  Py_INCREF(&AlpmTransactionType);
  PyModule_AddObject(module, "TransactionClass", (PyObject*)(&AlpmTransactionType));

  // the static instance
  PyObject *the_transaction = (PyObject*)AlpmTransactionType.tp_alloc(&AlpmTransactionType, 0);
  PyModule_AddObject(module, "transaction", the_transaction);
  Py_INCREF(the_transaction);
  return 0;
}

/* vim: set ts=2 sw=2 tw=0 et: */
