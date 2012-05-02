import sys

srcdir = '.'
blddir = 'build'
VERSION = '0.0.1'

def set_options(opt):
  opt.tool_options("compiler_cxx")
  opt.tool_options('compiler_cc')

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  conf.check_tool("compiler_cc")

def build(bld):
  # nbar.c
  nbar = bld.new_task_gen('cc')
  nbar.source = './src/nbar.c'
  nbar.cflags = ['-std=c99', '-pedantic', '-Wall', '-fPIC']
  if sys.platform.startswith("darwin"):
    nbar.linkflags=[ '-L/usr/X11/lib']
  else:
    nbar.framework=['X11','Xinerama']
  nbar.lib=['X11', 'Xinerama']

  # nbar_node.cc
  if sys.platform.startswith("darwin"):
    nbarn = bld.new_task_gen('cxx', 'shlib', 'node_addon')
    nbarn.linkflags=[ '-L/usr/X11/lib']
  else:
    nbarn = bld.new_task_gen('cxx', 'shlib', 'node_addon')
    nbarn.framework = ['X11', 'Xinerama']
  nbarn.lib=['X11', 'Xinerama']
  nbarn.cxxflags = ["-g", "-static", "-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-Wall"]
  nbarn.target = "nbar_node"
  nbarn.source = "./src/nbar_node.cc"
  bld.env.append_value('LINKFLAGS', [
    bld.srcnode.abspath(bld.env)+'src/nbar_1.o'
  ])
