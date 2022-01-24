# pathpy4
[![PyPI Latest Release](https://img.shields.io/pypi/v/pathpy4.svg)](https://pypi.org/project/pathpy4/)
![test](https://github.com/pathpy/pathpy4/actions/workflows/test.yml/badge.svg)
[![codecov](https://codecov.io/gh/pathpy/pathpy4/branch/main/graph/badge.svg?token=FCC1VLST13)](https://codecov.io/gh/pathpy/pathpy4)
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)
[![Imports: isort](https://img.shields.io/badge/%20imports-isort-%231674b1?style=flat&labelColor=ef8336)](https://pycqa.github.io/isort/)
[![License](https://img.shields.io/badge/licence-%20AGPL--3.0-blue.svg)](https://github.com/pathpy/pathpy4/blob/main/LICENSE.txt)

# Requirements

Python 3.9+.

# Developer Setup


## Virtual Environments

It is best practice during development to create an isolated [Python virtual
environment](https://docs.python.org/3/library/venv.html) using the `venv`
standard library module. This will keep dependant Python packages from
interfering with other Python projects on your system.

On Linux and Unix (Mac):

```bash
# On Python 3.9+, add --upgrade-deps
$ python3 -m venv venv
$ source venv/bin/activate
```

On Windows Powershell / `cmd`:

```bash
> py -m venv venv
> venv\Scripts\activate
```

Once activated, it is good practice to update core packaging tools (`pip`,
`setuptools`, and `wheel`) to the latest versions.

```bash
(venv) $ python -m pip install --upgrade pip setuptools wheel
```

## Syncing Virtual Environments

This project uses [pip-tools](https://github.com/jazzband/pip-tools) to lock project dependencies
and create reproducible virtual environments.

```bash
(venv) $ python -m pip install pip-tools
```

To cleanly install your dependencies into your virtual environment:

```bash
(venv) $ python -m piptools sync requirements/requirements.txt requirements/dev-requirements.txt
```

**Note:**

To update dependencies and add new requirements, modify the `requirements.in` and `dev-requirements.in` files in the folder `requirements`:

```bash
(venv) $ python -m piptools compile --upgrade requirements/requirements.txt
(venv) $ python -m piptools compile --upgrade requirements/dev-requirements.txt
```


## Installation of pathpy

After successful installation and update of the virtual environment, `pathpy` can
be installed in the developer mode.

```bash
(venv) $ python -m pip install -e .
```


# Testing

## Unit Testing

Unit testing is performed with [pytest](https://pytest.org/). pytest has become the defacto Python
unit testing framework. Some key advantages over the built
in [unittest](https://docs.python.org/3/library/unittest.html) module are:

1. Significantly less boilerplate needed for tests.
2. PEP8 compliant names (e.g. `pytest.raises()` instead of `self.assertRaises()`).
3. Vibrant ecosystem of plugins.

pytest will automatically discover and run tests by recursively searching for folders and `.py`
files prefixed with `test` for any functions prefixed by `test`.

The `tests` folder is created as a Python package (i.e. there is an `__init__.py` file within it)
because this helps `pytest` uniquely namespace the test files. Without this, two test files cannot
be named the same, even if they are in different sub-directories.

```bash
(venv) $ pytest
```

## Code coverage

Code coverage is provided by the [pytest-cov](https://pytest-cov.readthedocs.io/en/latest/) plugin.

```bash
(venv) $ pytest --cov=pathpy --cov-report=html --cov-report=term
```

## Code Style Checking

[PEP8](https://www.python.org/dev/peps/pep-0008/) is the universally accepted style guide for
Python code. PEP8 code compliance is verified using [Flake8](http://flake8.pycqa.org/). Flake8 is
configured in the `[flake8]` section of `tox.ini`. Extra Flake8 plugins are also included:

- `flake8-bugbear`: Find likely bugs and design problems in your program.
- `flake8-broken-line`: Forbid using backslashes (`\`) for line breaks.
- `flake8-comprehensions`: Helps write better `list`/`set`/`dict` comprehensions.
- `pep8-naming`: Ensure functions, classes, and variables are named with correct casing.

```bash
(venv) $ flake8
```

## Automated Code Formatting

Code is automatically formatted using [black](https://github.com/psf/black). Imports are
automatically sorted and grouped using [isort](https://github.com/PyCQA/isort/).

These tools are configured by:

- `pyproject.toml`

To check what has to be formatted, run:

```bash
(venv) $ isort --check .
(venv) $ black --check .
```


To automatically format code, run:

```bash
(venv) $ isort .
(venv) $ black .
```

# Documentation

## Generating a User Guide

[Sphinx](https://www.sphinx-doc.org/en/master/) is a powerful static site
generator that combines easy-to-write Markdown, with a number of Markdown
extensions that increase the power of Markdown. This makes it a great fit for
user guides and other technical documentation.

To build the user guide, change to the `docs` folder and run.

```bash
(venv) $ cd docs/
(venv) $ make clean
(venv) $ make html
```

Open `docs/_build/html/index.html` using a web browser.

Each time the `master` Git branch is updated, the
`.github/workflows/gh-pages.yml` GitHub Action will automatically build the user
guide and publish it to [GitHub Pages](https://pages.github.com/).  This hosted
user guide can be viewed at <https://pathpy.github.io/pathpy4/>

## Generating API Documentation

This project uses
[sphinx.ext.autodoc](https://www.sphinx-doc.org/en/master/usage/extensions/autodoc.html)
plugin for sphinx , which renders
[numpydoc](https://numpydoc.readthedocs.io/en/latest/format.html) into an sphinx
project. numpydoc docstrings provide a good mix of easy-to-read docstrings in
code as well as nicely-rendered output.

```python
"""Computes the factorial through a recursive algorithm.

Parameters
----------
n: int
   A positive input value.

Returns
-------
int
    Returns the computed factorial.

Raises
------
InvalidFactorialError
    If `n` is less than 0.

Examples
--------
>>> pathpy.factorial(1)
1
"""
```

# Project Structure

Traditionally, Python projects place the source for their packages in the root
of the project structure, like:

``` {.sourceCode .}
pathpy4
├── pathpy
│   ├── __init__.py
│   ├── cli.py
│   └── lib.py
├── tests
│   ├── __init__.py
│   └── test_pathpy.py
├── tox.ini
└── setup.py
```

However, this structure is
[known](https://docs.pytest.org/en/latest/goodpractices.html#tests-outside-application-code)
to have bad interactions with `pytest` and `tox`, two standard tools maintaining
Python projects. The fundamental issue is that tox creates an isolated virtual
environment for testing. By installing the distribution into the virtual
environment, `tox` ensures that the tests pass even after the distribution has
been packaged and installed, thereby catching any errors in packaging and
installation scripts, which are common. Having the Python packages in the
project root subverts this isolation for two reasons:

1. Calling `python` in the project root (for example, `python -m pytest tests/`)
   [causes Python to add the current working
   directory](https://docs.pytest.org/en/latest/pythonpath.html#invoking-pytest-versus-python-m-pytest)
   ( the project root) to `sys.path`, which Python uses to find modules. Because
   the source package `fact` is in the project root, it shadows the `fact`
   package installed in the tox environment.
2. Calling `pytest` directly anywhere that it can find the tests will also add
   the project root to `sys.path` if the `tests` folder is a Python package
   (that is, it contains a `__init__.py` file).  [pytest adds all folders
   containing
   packages](https://docs.pytest.org/en/latest/goodpractices.html#conventions-for-python-test-discovery)
   to `sys.path` because it imports the tests like regular Python modules.

In order to properly test the project, the source packages must not be on the
Python path. To prevent this, a dedicated `src` directory is the [recommended
solution](https://docs.pytest.org/en/latest/pythonpath.html#test-modules-conftest-py-files-inside-packages)
by `pytest` when using tox and the solution this blueprint promotes because it
is the least brittle even though it deviates from the traditional Python project
structure. It results is a directory structure like:

``` {.sourceCode .}
pathpy4
├── src
│   └── pathpy
│       ├── __init__.py
│       ├── cli.py
│       └── lib.py
├── tests
│   ├── __init__.py
│   └── test_pathpy.py
├── tox.ini
└── setup.py
```
