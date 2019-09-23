# flake8: noqa

env = Environment(CXX='clang++',
                  CXXFLAGS=['-Werror', '-Wall', '-Wpedantic', '-Wextra', '-g'])
env.Append(CPPPATH=['#/include'])
env['OBJPREFIX'] = '#/build/obj/' + env['OBJPREFIX']
env['PROGPREFIX'] = '#/build/' + env['PROGPREFIX']

SConscript('tests/SConscript.py', exports='env')
