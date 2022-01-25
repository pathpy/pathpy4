#ifndef PYTHON_PATHPYPATH_H
#define PYTHON_PATHPYPATH_H

#include "preamble.h"
#include "structmember.h"

typedef struct {
  PyObject_HEAD
  long uid;       /* uid of the path object as an integer value */
  PyObject *name; /* Name of the path as string */
  PyObject *attr; /* Attribute of the the path  */
  PyObject *path; /* Path of the object  */
} PathPyPathObject;

extern PyTypeObject pathpymodule_PathPyPath_Type;

#endif
