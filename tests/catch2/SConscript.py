# flake8: noqa

Import("tests_env")

catch2_env = tests_env.Clone()

catch2_env['OBJPREFIX'] = catch2_env['OBJPREFIX'] + 'catch2/'
catch2_env['PROGPREFIX'] = catch2_env['PROGPREFIX'] + 'catch2/'

catch2_env.Program(target='catch2_tests', source=Glob('*.cpp'))
