"""Test file for the core class PathPyPath"""
# !/usr/bin/python -tt
# -*- coding: utf-8 -*-
# =============================================================================
# File      : test_pathpypath.py -- Test class for PathPyPath
# Author    : Jürgen Hackl <hackl@ifi.uzh.ch>
# Time-stamp: <Tue 2022-01-25 07:31 juergen>
#
# Copyright (c) 2016-2022 Pathpy Developers
# =============================================================================
import pytest

from pathpy import PathPyPath


def test_name():
    """Test name of the PathPyPath"""
    path_1 = PathPyPath(name='name')
    assert path_1.name == 'name'

    path_1.name = 'new'
    assert path_1.name == 'new'

    with pytest.raises(TypeError):
        path_1.name = 111

    # This shouldn't be possible
    # There is a bug in the c-code
    path_2 = PathPyPath(name=121)


# =============================================================================
# eof
#
# Local Variables:
# mode: python
# mode: linum
# mode: auto-fill
# fill-column: 79
# End:
