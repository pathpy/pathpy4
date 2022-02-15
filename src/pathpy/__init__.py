"""Pathpy Module."""

# flake8: noqa
# pylint: disable=unused-import
# pylint: disable=no-name-in-module
# nopycln: file

from pathpy._pathpy import add, subtract, multiply  # type: ignore
from pathpy.lib import InvalidFactorialError, factorial

from . import _version

__version__ = _version.get_versions()["version"]
