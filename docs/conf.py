# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.

import os
import sys
import time

# Load the pathpy module
sys.path.insert(0, os.path.abspath("../src/"))
try:
    from pathpy import __version__
except ImportError as exc:
    print(exc)
    raise

# -- Project information -----------------------------------------------------

project = "pathpy"
copyright = "2016-{}, Pathpy Developers".format(time.strftime("%Y"))
author = "Pathpy Developers"

# The full version, including alpha/beta/rc tags
release = __version__


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "sphinx.ext.duration",  # Measure durations of Sphinx processing
    "sphinx.ext.viewcode",  # Add links to highlighted source code
    "sphinx.ext.coverage",  # Collect doc coverage stats
    "sphinx.ext.mathjax",  # Math support for HTML outputs in Sphinx
    "sphinx.ext.doctest",  # Test snippets in the documentation
    "sphinx.ext.autodoc",  # Include documentation from docstrings
    "sphinx.ext.autosummary",  # Generate autodoc summaries
    "sphinx.ext.githubpages",  # Publish HTML docs in GitHub Pages
    "numpydoc",  # Support for the Numpy docs format in Sphinx
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "pydata_sphinx_theme"

# (Optional) Logo. Should be small enough to fit the navbar (ideally 24x24).
# Path should be relative to the ``_static`` files directory.
html_logo = "_static/pathpy_logo.png"

# The name of an image file (within the static path) to use as favicon of the
# docs.  This file should be a Windows icon file (.ico) being 16x16 or 32x32
# pixels large.
html_favicon = "_static/favicon.ico"

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]
