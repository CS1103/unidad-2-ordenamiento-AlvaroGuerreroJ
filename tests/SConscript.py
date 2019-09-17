# flake8: noqa

Import('env')

SConscript('catch2/SConscript.py', exports='env')
SConscript('rapidcheck/SConscript.py', exports='env')
