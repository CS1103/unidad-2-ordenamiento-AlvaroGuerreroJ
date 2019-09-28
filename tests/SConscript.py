# flake8: noqa

Import('base_env')

tests_env = base_env.Clone()

tests_env['OBJPREFIX'] = tests_env['OBJPREFIX'] + 'tests/'
tests_env['PROGPREFIX'] = tests_env['PROGPREFIX'] + 'tests/'

SConscript('catch2/SConscript.py', exports='tests_env')
SConscript('rapidcheck/SConscript.py', exports='tests_env')
