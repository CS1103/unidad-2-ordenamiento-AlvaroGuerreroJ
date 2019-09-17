# flake8: noqa

env = Environment(CXX='clang++',
                  CXXFLAGS=['-Werror', '-Wall', '-Wpedantic', '-Wextra', '-g'])
env.Append(CPPPATH=['#/include'])

SConscript('tests/SConscript.py', exports='env', variant_dir='build')
