# flake8: noqa

Import('env')

env.Program(target='catch2_tests', source=Glob('*.cpp'))
