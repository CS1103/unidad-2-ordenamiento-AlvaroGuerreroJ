# flake8: noqa

Import('tests_env')

rapidcheck_env = tests_env.Clone()

rapidcheck_env['OBJPREFIX'] = rapidcheck_env['OBJPREFIX'] + 'rapidcheck/'
rapidcheck_env['PROGPREFIX'] = rapidcheck_env['PROGPREFIX'] + 'rapidcheck/'

rapidcheck_env.Program(target='rapidcheck_tests', source=Glob('*.cpp') + ['/usr/lib/librapidcheck.a'])
