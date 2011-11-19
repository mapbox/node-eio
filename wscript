import os
import Options
from Configure import ConfigurationError
from shutil import copy2 as copy

TARGET = 'eio'
TARGET_FILE = '%s.node' % TARGET
dest = 'lib/%s' % TARGET_FILE

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

  linkflags = []
  if os.environ.has_key('LINKFLAGS'):
    linkflags.extend(os.environ['LINKFLAGS'].split(' '))
  conf.env.append_value("LINKFLAGS", linkflags)

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.cxxflags = ["-g", "-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-Wall"]
  obj.target = TARGET
  obj.source = "src/eio.cc"

def shutdown():
  if Options.commands['clean']:
      if os.path.exists(TARGET_FILE):
        unlink(TARGET_FILE)
  else:
    if os.path.exists('build/Release/%s' % TARGET_FILE):
      copy('build/Release/%s' % TARGET_FILE, dest)
    elif os.path.exists('build/default/%s' % TARGET_FILE):
      copy('build/default/%s' % TARGET_FILE, dest)
    
    
