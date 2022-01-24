#!/usr/bin/python -tt
# -*- coding: utf-8 -*-
# =============================================================================
# File      : setup.py -- Setup script for pathpy
# Author    : Jürgen Hackl <hackl@ifi.uzh.ch>
# Time-stamp: <Mon 2022-01-24 16:34 juergen>
#
# Copyright (c) 2016-2022 Pathpy Developers
# =============================================================================
"""
Setup script for pathpy.
"""

from pathlib import Path
import sys

from setuptools import find_packages, setup
import versioneer

project_dir = Path(__file__).parent

version = versioneer.get_version()

# Minimum required python version
min_version = (3, 8)

# Check the python version. Pathpy requires Python 3.7+.
if sys.version_info[:2] < min_version:
    error = """
    Pathpy {} requires Python {} or later ({} detected).
    """.format(
        version,
        ".".join(map(str, min_version)),
        ".".join(map(str, sys.version_info[:2])),
    )
    sys.exit(error)

# Initialize setup parameters
DISTNAME = "pathpy4"

VERSION = versioneer.get_version()

CMDCLASS = versioneer.get_cmdclass()

PYTHON_REQUIRES = ">={}".format(".".join(map(str, min_version)))

DESCRIPTION = "pathpy: path data analysis"

LONG_DESCRIPTION = """\
An OpenSource python package for the analysis of time series data on networks
using higher-order and multi-order graphical models.
"""

MAINTAINER = "Ingo Scholtes, Jürgen Hackl"

MAINTAINER_EMAIL = "info@pathpy.net"

URL = "https://www.pathpy.net"

LICENSE = "AGPL-3.0+"

DOWNLOAD_URL = "https://github.com/pathpy/pathpy"

PROJECT_URLS = {
    "Issue Tracker": "https://github.com/pathpy/pathpy/issues",
    "Documentation": "https://pathpy.github.io/",
    "Source Code": "https://github.com/pathpy/pathpy",
}

INSTALL_REQUIRES = (
    project_dir.joinpath("requirements/requirements.txt")
    .read_text()
    .split("\n")
)

PACKAGES = find_packages("src")

PACKAGE_DIR = {"": "src"}

PACKAGE_DATA = {"pathpy": ["py.typed"]}

PLATFORMS = ["Linux", "Mac OSX", "Windows", "Unix"]

CLASSIFIERS = [
    "Development Status :: 2 - Pre-Alpha",
    "Intended Audience :: Science/Research",
    "Programming Language :: Python :: 3.7",
    "Programming Language :: Python :: 3.8",
    "License :: OSI Approved :: "
    "GNU Affero General Public License v3 or later (AGPLv3+)",
    "Topic :: Software Development :: Libraries :: Python Modules",
    "Topic :: Scientific/Engineering :: Artificial Intelligence",
    "Topic :: Scientific/Engineering :: Visualization",
    "Topic :: Scientific/Engineering :: Bio-Informatics",
    "Topic :: Scientific/Engineering :: Information Analysis",
    "Topic :: Scientific/Engineering :: Mathematics",
    "Topic :: Scientific/Engineering :: Physics",
    "Operating System :: OS Independent",
    "Programming Language :: Python",
    "Programming Language :: Python :: 3",
    "Programming Language :: Python :: 3 :: Only",
    "Programming Language :: Python :: 3.8",
    "Programming Language :: Python :: 3.9",
    "Programming Language :: Python :: 3.10",
]


setup(
    name=DISTNAME,
    author=MAINTAINER,
    author_email=MAINTAINER_EMAIL,
    maintainer=MAINTAINER,
    maintainer_email=MAINTAINER_EMAIL,
    description=DESCRIPTION,
    long_description=LONG_DESCRIPTION,
    license=LICENSE,
    url=URL,
    project_urls=PROJECT_URLS,
    version=VERSION,
    cmdclass=CMDCLASS,
    download_url=DOWNLOAD_URL,
    install_requires=INSTALL_REQUIRES,
    packages=PACKAGES,
    package_dir=PACKAGE_DIR,
    package_data=PACKAGE_DATA,
    classifiers=CLASSIFIERS,
    platforms=PLATFORMS,
    zip_safe=False,
    include_package_data=True,
    python_requires=PYTHON_REQUIRES,
    setup_requires=["pytest-runner", "flake8"],
    tests_require=["pytest"],
)
