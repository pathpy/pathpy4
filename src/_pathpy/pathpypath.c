#include "pathpypath.h"

static int
pathpymodule_PathPyPath_traverse(PathPyPathObject *self, visitproc visit, void *arg)
{
  Py_VISIT(Py_TYPE(self));
  Py_VISIT(self->name);
  Py_VISIT(self->attr);
  Py_VISIT(self->path);
  return 0;
}

static int
pathpymodule_PathPyPath_clear(PathPyPathObject *self)
{
  Py_CLEAR(self->name);
  Py_CLEAR(self->attr);
  Py_CLEAR(self->path);
  return 0;
}

static void
pathpymodule_PathPyPath_dealloc(PathPyPathObject *self)
{
  PyObject_GC_UnTrack(self);
  pathpymodule_PathPyPath_clear(self);
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
pathpymodule_PathPyPath_new(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
  PathPyPathObject *self;

  self = (PathPyPathObject*)type->tp_alloc(type, 0);

  if (self != NULL){

    self->name = PyUnicode_FromString("");

    if (self->name == NULL){
      Py_DECREF(self);
      return NULL;
    }

    self->path = PyList_New(0);
    self->attr = PyDict_New();

    if (self->path == NULL){
      Py_DECREF(self);
      return NULL;
    }

    self->uid =0;
    self->attr=NULL;
  }

  return (PyObject *)self;
}

static int
pathpymodule_PathPyPath_init(PathPyPathObject *self, PyObject *args, PyObject *kwargs)
{
  PyObject *name=NULL, *tmp;
  long int uid = -1;

  static char* keywords[] = {"uid","name", NULL};

  if (!PyArg_ParseTupleAndKeywords(args,
                                   kwargs,
                                   "|lO:PathPyPath",
                                   keywords,
                                   &uid,
                                   &name)) {
    /* argument parsing failed */
    return -1;
  }

  if (name) {
    tmp = self->name;
    Py_INCREF(name);
    self->name = name;
    Py_XDECREF(tmp);
  }

  if (uid<0){
    uid = PyLong_AsLong(PyLong_FromVoidPtr(self));
  }
  self->uid = uid;

  return 0;
}

static PyMemberDef pathpymodule_PathPyPath_members[] = {
  {"uid",                           /* name of the member */
   T_LONG,                          /* type of the member in the C struct */
   offsetof(PathPyPathObject, uid), /* offset in bytes */
   READONLY,                        /* flag bits */
   "path uid"},                     /* doc */
  {NULL}                            /* Sentinel */
};


static PyObject*
pathpymodule_PathPyPath_repr(PathPyPathObject* self)
{
  return PyUnicode_FromFormat("<%s: uid %zd>",
                              Py_TYPE(self)->tp_name,
                              self->uid);
}


static PyObject *
pathpymodule_PathPyPath_get_name(PathPyPathObject *self, void *closure)
{
  Py_INCREF(self->name);
  return self->name;
}


static int
pathpymodule_PathPyPath_set_name(PathPyPathObject *self, PyObject *value, void *closure)
{
  if (value == NULL) {
    PyErr_SetString(PyExc_TypeError, "Cannot delete the name attribute");
    return -1;
  }

  if (!PyUnicode_Check(value)) {
    PyErr_SetString(PyExc_TypeError,
                    "The name attribute value must be a string");
    return -1;
  }

  Py_INCREF(value);
  Py_CLEAR(self->name);
  self->name = value;

  return 0;
}


static PyGetSetDef pathpymodule_PathPyPath_getseters[] = {
  {"name",
   (getter)pathpymodule_PathPyPath_get_name,
   (setter)pathpymodule_PathPyPath_set_name,
   "path name",
   NULL},
  {NULL}  /* Sentinel */
};




static PyObject *
pathpymodule_PathPyPath_testmethod(PathPyPathObject* self)
{
    return PyUnicode_FromFormat("%S", self->path);
}


static PyObject*
pathpymodule_PathPyPath_add(PathPyPathObject *self, PyObject *args)
{
  Py_ssize_t i,size = PyTuple_Size(args);

  if(!size) {
    if(!PyErr_Occurred())
      PyErr_SetString(PyExc_TypeError,
                      "At least one argument must be supplied.");
    return NULL;
  }

  for (i=0;i<size;i++) {
    PyObject *temp = PyTuple_GetItem(args,i);

    if(temp == NULL){
      return NULL;
    }

    if (!PyNumber_Check(temp)) {
      PyErr_SetString(PyExc_TypeError,
                      "The arguments values must be numeric.");
      return NULL;
    }

    if (PyList_Append(self->path, temp)) {
      return NULL;
    }

  }

  Py_RETURN_NONE;
}


static PyObject*
pathpymodule_PathPyPath_push(PathPyPathObject *self, PyObject *args, PyObject *kwargs)
{
  static char* keywords[] = {"element", NULL};
  PyObject* element;

  if (!PyArg_ParseTupleAndKeywords(args,
                                   kwargs,
                                   "O:push",
                                   keywords,
                                   &element)) {
    return NULL;
  }

  if (PyList_Append(self->path, element)) {
    return NULL;
  }

  Py_RETURN_NONE;
}


static PyMethodDef pathpymodule_PathPyPath_methods[] = {
  {"testmethod", (PyCFunction)pathpymodule_PathPyPath_testmethod, METH_NOARGS,
   "Return the name of the path"
  },
  {"push", (PyCFunction)pathpymodule_PathPyPath_push,
   METH_VARARGS | METH_KEYWORDS, "Push element to the path"},
  {"add", (PyCFunction)pathpymodule_PathPyPath_add,
   METH_VARARGS, "Add elements to the path"},
  {NULL}  /* Sentinel */
};

static Py_ssize_t
pathpymodule_PathPyPath_size(PathPyPathObject *self)
{
  return PyList_GET_SIZE(self->path);
}

static PyObject*
pathpymodule_PathPyPath_item(PathPyPathObject* self, Py_ssize_t index)
{
  PyObject* element = PyList_GetItem(self->path, index);
  Py_XINCREF(element);
  return element;
}

static int
pathpymodule_PathPyPath_contains(PathPyPathObject* self, PyObject* element)
{
  return PySequence_Contains(self->path, element);
}

PySequenceMethods pathpymodule_PathPyPath_as_sequence = {
  (lenfunc) pathpymodule_PathPyPath_size,     /* sq_length */
  0,                                          /* sq_concat */
  0,                                          /* sq_repeat */
  (ssizeargfunc) pathpymodule_PathPyPath_item, /* sq_item */
  0,                                          /* placeholder */
  0,                                          /* sq_ass_item */
  0,                                          /* placeholder */
  (objobjproc) pathpymodule_PathPyPath_contains, /* sq_contains */
  0,                                          /* sq_inplace_concat */
  0,                                          /* sq_inplace_repeat */
};


PyTypeObject pathpymodule_PathPyPath_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "pathpy.PathPyPath",       /* tp_name */
  sizeof(PathPyPathObject),  /* tp_basicsize */
  0,                         /* tp_itemsize */
  (destructor)pathpymodule_PathPyPath_dealloc, /* tp_dealloc */
  0,                         /* tp_print */
  0,                         /* tp_getattr */
  0,                         /* tp_setattr */
  0,                         /* tp_reserved */
  (reprfunc) pathpymodule_PathPyPath_repr, /* tp_repr */
  0,                         /* tp_as_number */
  &pathpymodule_PathPyPath_as_sequence, /* tp_as_sequence */
  0,                         /* tp_as_mapping */
  0,                         /* tp_hash  */
  0,                         /* tp_call */
  0,                         /* tp_str */
  0,                         /* tp_getattro */
  0,                         /* tp_setattro */
  0,                         /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT |
  Py_TPFLAGS_BASETYPE |
  Py_TPFLAGS_HAVE_GC,        /* tp_flags */
  "PathPyPath objects",      /* tp_doc */
  (traverseproc) pathpymodule_PathPyPath_traverse, /* tp_traverse */
  (inquiry)pathpymodule_PathPyPath_clear,  /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  pathpymodule_PathPyPath_methods,             /* tp_methods */
  pathpymodule_PathPyPath_members,             /* tp_members */
  pathpymodule_PathPyPath_getseters,           /* tp_getset */
  0,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  (initproc)pathpymodule_PathPyPath_init,      /* tp_init */
  0,                         /* tp_alloc */
  pathpymodule_PathPyPath_new,                 /* tp_new */
};
