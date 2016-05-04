#!/usr/bin/env python

import ninja_syntax
import os, sys, glob, re
import itertools
import argparse

# utilities
def flags(*args):
    return ' '.join(itertools.chain(*args))

def includes(l):
    return ['-I"{}"'.format(x) for x in l]

def library_includes(l):
    return ['-L"{}"'.format(x) for x in l]

def libraries(l):
    return ['-l{}'.format(x) for x in l]

def dependencies(l):
    return ['-isystem"{}"'.format(x) for x in l]

def object_file(f):
    (root, ext) = os.path.splitext(f)
    return os.path.join(objdir, root + '.o')

def replace_extension(f, e):
    (root, ext) = os.path.splitext(f)
    return root + e

# Default install dir
install_dir = 'bin'

# Compiler: Read from environment or defaulted
cxx = os.environ.get('CXX', "g++") 

# command line stuff
parser = argparse.ArgumentParser()
parser.add_argument('--debug', action='store_true', help='compile with debug flags')
parser.add_argument('--cxx', metavar='<compiler>', help='compiler name to use (default: env.CXX=%s)' % cxx, default=cxx)
parser.add_argument('--cxx-flags', help='additional flags passed to the compiler', default='')
parser.add_argument('--ci', action='store_true', help=argparse.SUPPRESS)
parser.add_argument('--testing', action='store_true', help=argparse.SUPPRESS)
parser.add_argument('--lua-lib', help='lua library name (without the lib on *nix).', default='lua')
parser.add_argument('--lua-dir', metavar='<dir>', help='directory lua is in with include and lib subdirectories', default='vendor/lua/include')
parser.add_argument('--install-dir', metavar='<dir>', help='directory to install the headers to', default=install_dir);
parser.epilog = """In order to install sol, administrative privileges might be required.
Note that installation is done through the 'ninja install' command. To uninstall, the
command used is 'ninja uninstall'. The default installation directory for this
system is {}""".format(install_dir)

args = parser.parse_args()

# general variables
include = [ '.', './include', 'vendor/lua/include', 'vendor/lua-intf', 'vendor/selene/include', 'vendor/luabind', 'vendor/lua-api-pp', 'vendor/sol', 'vendor/slb/include', 'vendor/luawrapper\include', 'vendor/luawrapper.deps/include', 'vendor/kaguya/include', 'vendor/luacppinterface/LuaCppInterface', 'vendor/oolua/include', 'vendor/nonius', 'vendor/nonius.deps/include' ]
cxxflags = [ '-std=c++14', '-ftemplate-depth=1024' ]
cxxflags.extend([p for p in re.split("( |\\\".*?\\\"|'.*?')", args.cxx_flags) if p.strip()])
ldflags = []
depends = []
script_dir = os.path.dirname(os.path.realpath(sys.argv[0]))

if not args.lua_lib:
     args.lua_lib = 'lua'

if args.debug:
    cxxflags.extend(['-g', '-O0'])
else:
    cxxflags.extend(['-DNDEBUG', '-O3'])

if args.lua_dir:
    include.extend([os.path.join(args.lua_dir, 'include')])
    ldflags.extend(library_includes([os.path.join(args.lua_dir, 'lib')]))

if 'linux' in sys.platform:
    ldflags.extend(libraries(['dl']))

builddir = 'bin'
objdir = 'obj'
if 'win32' in sys.platform:
     lua_bench = os.path.join(builddir, 'lua bench.exe')
     sol_bench = os.path.join(builddir, 'sol bench.exe')
else:
     lua_bench = os.path.join(builddir, 'lua bench')
     sol_bench = os.path.join(builddir, 'sol bench')

# ninja file
ninja = ninja_syntax.Writer(open('build.ninja', 'w'))

# variables
ninja.variable('ninja_required_version', '1.3')
ninja.variable('builddir', 'bin')
ninja.variable('cxx', args.cxx)
ninja.variable('cxxflags', flags(cxxflags + includes(include) + dependencies(depends)))
ninja.variable('ldflags', flags(ldflags))
ninja.newline()

# rules
ninja.rule('bootstrap', command = ' '.join(['python'] + sys.argv), generator = True)
ninja.rule('compile', command = '$cxx -MMD -MF $out.d -c $cxxflags -Werror $in -o $out',
                      deps = 'gcc', depfile = '$out.d',
                      description = 'Compiling $in to $out')
ninja.rule('link', command = '$cxx $cxxflags $in -o $out $ldflags', description = 'Creating $out')
ninja.rule('runner', command = lua_bench)
ninja.newline()

# builds
ninja.build('build.ninja', 'bootstrap', implicit = sys.argv[0])

lua_bench_object_files = []
for f in glob.glob('lua bench/src/*.cpp'):
    obj = object_file(f)
    lua_bench_object_files.append(obj)
    ninja.build(obj, 'compile', inputs = f)

sol_bench_object_files = []
for f in glob.glob('sol bench/src/*.cpp'):
    obj = object_file(f)
    sol_bench_object_files.append(obj)
    ninja.build(obj, 'compile', inputs = f)

ninja.build(lua_bench, 'link', inputs = lua_bench_object_files)
ninja.build(sol_bench, 'link', inputs = sol_bench_object_files)
ninja.build('lua_bench', 'phony', inputs = lua_bench)
ninja.build('sol_bench', 'phony', inputs = sol_bench)
ninja.build('run', 'runner', implicit = 'lua_bench')
ninja.default('run')
