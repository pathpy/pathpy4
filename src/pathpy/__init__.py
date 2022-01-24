"""Pathpy Module."""

# flake8: noqa
# pylint: disable=unused-import
# nopycln: file

from pathpy.lib import InvalidFactorialError, factorial

from . import _version

__version__ = _version.get_versions()["version"]
