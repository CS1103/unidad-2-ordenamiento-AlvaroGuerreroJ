# flake8: noqa

Import('env')

env.Program(target='rapidcheck_tests', source=Glob('*.cpp') + ['/usr/lib/librapidcheck.a'])
