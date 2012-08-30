#!python

EnsureSConsVersion(2,0)
SConsignFile()

import os, string, sys
import re
import distutils.sysconfig
import distutils.util
import SCons
import SCons.Util

pj = os.path.join

# Bring in the AutoDist build helper
sys.path.append('tools/build')
from AutoDist import *

# True and False were not defined prior to Python 2.2.1.
if sys.version[:3] == '2.2' and sys.version[3] != '.':
   False = 0
   True  = 1

enable_python      = False
boost_version      = '1.31'
have_cppunit       = False
compiler_major_ver = 0

try:
   has_help_flag = SCons.Script.Main.options.help_msg
except AttributeError:
   try:
      has_help_flag = SCons.Script.options.help_msg
   except AttributeError:
      has_help_flag = has_help_flag = SCons.Script.GetOption("help")

#------------------------------------------------------------------------------
# Define some generally useful functions
#------------------------------------------------------------------------------
def GetGMTLVersion():
   "Gets the GMTL version from the gmtl/Version.h header"

   contents = open('gmtl/Version.h', 'r').read()
   major = re.compile('.*(#define *GMTL_VERSION_MAJOR *(\d+)).*', re.DOTALL).sub(r'\2', contents)
   minor = re.compile('.*(#define *GMTL_VERSION_MINOR *(\d+)).*', re.DOTALL).sub(r'\2', contents)
   patch = re.compile('.*(#define *GMTL_VERSION_PATCH *(\d+)).*', re.DOTALL).sub(r'\2', contents)
   return (int(major), int(minor), int(patch))

def GetPlatform():
   "Determines what platform this build is being run on."
   if string.find(sys.platform, 'irix') != -1:
      return 'irix'
   elif string.find(sys.platform, 'linux') != -1:
      return 'linux'
   elif string.find(sys.platform, 'freebsd') != -1:
      return 'freebsd'
   elif string.find(sys.platform, 'darwin') != -1:
      return 'darwin'
   elif string.find(sys.platform, 'cygwin') != -1:
      return 'cygwin'
   elif string.find(os.name, 'win32') != -1:
      return 'win32'
   else:
      return sys.platform
Export('GetPlatform')

def BuildLinuxEnvironment():
   "Builds a base environment for other modules to build on set up for linux"
   global optimize, profile, builders

   CXX = WhereIs('g++3') or 'g++'
   LINK = CXX
   CXXFLAGS = ['-ftemplate-depth-256', '-Wall', '-pipe']
   LINKFLAGS = []

   # Enable profiling?
   if profile != 'no':
      CXXFLAGS.extend(['-pg'])
      LINKFLAGS.extend(['-pg'])

   # Debug or optimize build?
   if optimize != 'no':
      CXXFLAGS.extend(['-DNDEBUG', '-g', '-O3'])
   else:
      CXXFLAGS.extend(['-D_DEBUG', '-g'])

   return Environment(
      ENV         = os.environ,

      CXX         = CXX,
      CXXFLAGS    = CXXFLAGS,
      LINK        = LINK,
      LINKFLAGS   = LINKFLAGS,
      CPPPATH     = [],
      LIBPATH     = [],
      LIBS        = [],
   )

def BuildCygwinEnvironment():
   "Builds a base environment for other modules to build on set up for Cygwin"
   global optimize, profile, builders

   CXX = 'g++'
   LINK = CXX
   CXXFLAGS = ['-ftemplate-depth-256', '-Wall', '-pipe']
   LINKFLAGS = []

   # Enable profiling?
   if profile != 'no':
      CXXFLAGS.extend(['-pg'])
      LINKFLAGS.extend(['-pg'])

   # Debug or optimize build?
   if optimize != 'no':
      CXXFLAGS.extend(['-DNDEBUG', '-g', '-O3'])
   else:
      CXXFLAGS.extend(['-D_DEBUG', '-g'])

   env = Environment(ENV=os.environ, CXX=CXX, LINK=LINK)
   env.Append(CXXFLAGS=CXXFLAGS, LINKFLAGS=LINKFLAGS)
   return env

def BuildDarwinEnvironment():
   "Builds a base environment for other modules to build on set up for Darwin."
   global optimize, profile, builders, compiler_major_ver

   exp = re.compile('^(.*)\/Python\.framework.*$')
   m = exp.search(distutils.sysconfig.get_config_var('prefix'))
   framework_opt = None
   if m:
      framework_opt = '-F' + m.group(1)

   CXX = os.environ.get("CXX", WhereIs('g++'))

   ver_re = re.compile(r'gcc version ((\d+)\.(\d+)\.(\d+))')
   (gv_stdout, gv_stdin, gv_stderr) = os.popen3(CXX + ' -v')
   ver_str = gv_stderr.read()

   match_obj = ver_re.search(ver_str)

   LINK = CXX
   CXXFLAGS = ['-ftemplate-depth-256', '-DBOOST_PYTHON_DYNAMIC_LIB',
               '-Wall', '-pipe']

   if framework_opt is not None:
      CXXFLAGS.append(framework_opt)

   compiler_ver       = match_obj.group(1)
   compiler_major_ver = int(match_obj.group(2))
   compiler_minor_ver = int(match_obj.group(3))

   # GCC 4.0 in Mac OS X 10.4 and newer does not have -fcoalesce-templates.
   if compiler_major_ver < 4:
      CXXFLAGS.append('-fcoalesce-templates')
   else:
      if compiler_minor_ver < 2:
         CXXFLAGS += ['-Wno-long-double', '-no-cpp-precomp']

   SHLIBSUFFIX = distutils.sysconfig.get_config_var('SO')
   SHLINKFLAGS = ['-bundle']

   if framework_opt is not None:
      SHLINKFLAGS.extend([framework_opt, '-framework', 'Python'])
   LINKFLAGS = []

   # Enable profiling?
   if profile != 'no':
      CXXFLAGS.extend(['-pg'])
      LINKFLAGS.extend(['-pg'])

   # Debug or optimize build?
   if optimize != 'no':
      CXXFLAGS.extend(['-DNDEBUG', '-O3'])
   else:
      CXXFLAGS.extend(['-D_DEBUG', '-g'])

   return Environment(
      ENV         = os.environ,

      CXX         = CXX,
      CXXFLAGS    = CXXFLAGS,
      CXXVERSION  = compiler_ver,
      LINK        = LINK,
      LINKFLAGS   = LINKFLAGS,
      CPPPATH     = [],
      LIBPATH     = [],
      LIBS        = [],
      SHLINKFLAGS = SHLINKFLAGS,
      SHLIBSUFFIX = SHLIBSUFFIX,
   )

def BuildIRIXEnvironment():
   "Builds a base environment for other modules to build on set up for IRIX"
   global optimize, profile, builders

   CXX = 'CC'
   LINK = 'CC'
   CXXFLAGS = ['-n32', '-mips3', '-LANG:std', '-w2']
   LINKFLAGS = CXXFLAGS

   # Enable profiling?
   if profile != 'no':
      CXXFLAGS.extend([])
      LINKFLAGS.extend([])

   # Debug or optimize build?
   if optimize != 'no':
      CXXFLAGS.extend(['-DNDEBUG', '-O2'])
   else:
      CXXFLAGS.extend(['-D_DEBUG', '-g', '-gslim'])

   return Environment(
      ENV         = os.environ,
      CXX         = CXX,
      CXXFLAGS    = CXXFLAGS,
      LINK        = LINK,
      LINKFLAGS   = LINKFLAGS,
      CPPPATH     = [],
      LIBPATH     = [],
      LIBS        = [],
   )

def BuildWin32Environment():
   global optimize, compiler_major_ver

   if ARGUMENTS.has_key("MSVC_VERSION"):
      # Python extension modules can only be built using Visual C++ 7.1 or
      # 9.0.
      msvs_ver = ARGUMENTS["MSVC_VERSION"]
      if msvs_ver not in ("7.1", "9.0"):
         print "Cannot build Python extensions using MSVS version %s" % \
                  msvs_ver
         sys.exit(1)

      python_ver = sys.version[:3]
      if msvs_ver == "7.1" and python_ver not in ("2.4", "2.5"):
         print "Python 2.4 or 2.5 must be used with Visual C++ 7.1"
         sys.exit(1)
      elif msvs_ver == "9.0" and python_ver < ("2.6"):
         print "Python 2.6 must be used with Visual C++ 9.0"
         sys.exit(1)

      env = Environment(MSVC_VERSION = msvs_ver)
      # Use the following line instead of the preceding when building with
      # Visual C++ 9.0. SCons does not know how to find the VC++ 9.0 paths.
      #env = Environment(MSVS_VERSION = msvs_ver, ENV = os.environ)
   else:
      env = Environment(ENV = os.environ)

   env["MSVS"] = {"VERSION" : env["MSVC_VERSION"]}
   print "Using MSVS version:", env["MSVS"]["VERSION"]
   compiler_major_ver = env["MSVS"]["VERSION"]
   
   # We need exception handling support turned on for Boost.Python.
   env.Append(LINKFLAGS = ['/subsystem:console', '/incremental:no'])
   env.Append(CXXFLAGS = ['/Zm800', '/EHsc', '/GR', '/Zc:wchar_t,forScope',
                          '/DBOOST_PYTHON_DYNAMIC_LIB'])

   if compiler_major_ver < '8.0':
      env.Append(CXXFLAGS = '/Op')
   else:
      env['SHLINKCOM'] = \
         [env['SHLINKCOM'],
          'mt.exe -manifest ${TARGET}.manifest -outputresource:$TARGET;2']

   if optimize != 'no':
      if compiler_major_ver < '8.0':
         env.Append(CXXFLAGS = ['/Ogity'])
      else:
         env.Append(CXXFLAGS = ['/Oity'])

      env.Append(CXXFLAGS = '/O2 /Gs /Ob2 /MD /D_OPT /DNDEBUG'.split())
      env.Append(LINKFLAGS = ['/RELEASE'])
   else:   
      env.Append(CXXFLAGS = ['/Z7', '/Od', '/Ob0', '/MDd', '/D_DEBUG'])
      env.Append(LINKFLAGS = ['/DEBUG'])

   return env

def BuildPlatformEnv():
   env = None

   # Create and export the base environment
   if GetPlatform() == 'irix':
      env = BuildIRIXEnvironment()
   elif GetPlatform() == 'linux' or GetPlatform()[:7] == 'freebsd':
      env = BuildLinuxEnvironment()
   elif GetPlatform() == 'darwin':
      env = BuildDarwinEnvironment()
   elif GetPlatform() == 'win32':
      env = BuildWin32Environment()
   elif GetPlatform() == 'cygwin':
      env = BuildCygwinEnvironment()
   else:
      print 'Unsupported build environment: ' + GetPlatform(), "Trying default"
      env = Environment()

   return env
      
      
# ########################################
# Options
# ########################################
def ValidateBoostVersion(key, value, environ):
   global boost_version

   if "BoostVersion" == key:
      exp = re.compile('^(\d+\.\d+(\.\d+)?)\D*$')
      match = exp.search(value)
      boost_version = match.group(1)
      print "Using Boost version", boost_version
   else:
      assert False, "Invalid Boost key"

def ValidateBoostOption(key, value, environ):
   "Validate the boost option settings"
   global enable_python, optimize, compiler_major_ver
   req_boost_version = 103100
   print "checking for %s [%s]...\n" % (key, value)

   if "BoostPythonDir" == key:
      version_dir = 'boost-' + re.sub(r'\.', '_', boost_version)   
      boost_inc_dir = value    		# Default to 'boost' directly off base
      potential_inc_paths = [pj('include', version_dir), "include"]
      for pth in potential_inc_paths:
         if os.path.isdir(pj(value,pth)):
	    boost_inc_dir = pj(value,pth)	    
	    break
      print "   trying boost include dir: [%s]"%boost_inc_dir

      # Get the boost version.
      boost_ver_filename = pj(boost_inc_dir, 'boost', 'version.hpp')
      if not os.path.isfile(boost_ver_filename):
         sys.stdout.write("%s not found.\n" % boost_ver_filename)
	 enable_python = False
	 return False

      ver_file = file(boost_ver_filename)

      # Matches 103000
      ver_num = int(re.search("define\s+?BOOST_VERSION\s+?(\d*)",
                              ver_file.read()).group(1))
      sys.stdout.write("found version: %s\n" % ver_num)

      if ver_num < req_boost_version:
         print "   Boost version too old!  Required version: %s" % req_boost_version
         Exit()
         return False

      # Check on the libraries that I need to use
      if enable_python:
         platform = GetPlatform()

         if platform == 'win32':	   
            major, minor = compiler_major_ver.split(".")
            tool = "-vc%s%s" % (major, minor)
         elif platform == 'irix':
            tool = '-mp'
         elif platform == 'darwin':
            if boost_version >= '1.37':
               tool = '-xgcc' + "".join(environ["CXXVERSION"].split('.')[:2])
            else:
               tool = ''
         else:
            tool = '-gcc'
            if boost_version >= '1.34':
               tool += "".join(environ["CXXVERSION"].split('.')[:2])

         if platform == 'darwin':
            if boost_version >= '1.35':
               threading = '-mt'
            else:
               threading = ''
         else:
            threading = '-mt'

         if optimize == 'no':
            if platform == 'win32':
               dbg = '-gd'
            else:
               dbg = '-d'
         else:
            dbg = ''

         if platform == 'win32':
            shlib_prefix = ''
            shlib_ext = 'dll'
         elif platform == 'darwin':
            shlib_prefix = 'lib'
            shlib_ext = 'dylib'
         elif platform == 'cygwin':
            shlib_prefix = 'lib'
            shlib_ext = 'dll'
         else:
            shlib_prefix = 'lib'
            shlib_ext = 'so'

         boost_sub_minor_ver = ver_num % 100
         boost_minor_ver     = ver_num / 100 % 1000
         boost_major_ver     = ver_num / 100000

         version = '-%d_%d' % (boost_major_ver, boost_minor_ver)
         if boost_sub_minor_ver > 0:
            version += '_%d' % boost_sub_minor_ver

         bpl_found = False
         libdirs = ['lib']

         if GetPlatform() != 'win32' and os.uname()[4] == 'x86_64':
            libdirs.append('lib64')

         full_bpl = 'boost_python%s%s%s%s' % (tool, threading, dbg, version)
         min_bpl  = 'boost_python'
         names = [full_bpl, min_bpl]

         # We would prefer to use the full Boost.Python name, but the search
         # performed below will give us something valid.
         bpl_name = full_bpl

         for l in libdirs:
            for n in names:
               boost_python_lib_name = pj(value, l,
                                          '%s%s.%s' % (shlib_prefix, n,
                                                       shlib_ext))

               print "Checking for '%s'" % boost_python_lib_name
               if os.path.isfile(boost_python_lib_name):
                  print "Using '%s'" % boost_python_lib_name
                  bpl_libdir = l
                  bpl_name   = n
                  bpl_found  = True
                  break

         if not bpl_found:
            print "No Boost.Python library was found in", libdirs
            Exit()
            return False

         if platform == 'irix':
            environ.Append(BoostCPPPATH = [pj(boost_inc_dir),
                                           pj(boost_inc_dir, 'compatibility',
                                              'cpp_c_headers')])
         else:
            environ.Append(BoostCPPPATH = [pj(boost_inc_dir)])

         environ.Append(BoostLIBPATH = [pj(value, bpl_libdir)])
         environ.Append(BoostLIBS = [bpl_name])

   else:
      assert False, "Invalid Boost key"

def ApplyBoostOptions(env):
   global enable_python
   if enable_python:
      env.Append(CPPPATH = env["BoostCPPPATH"])
      env.Append(LIBPATH = env["BoostLIBPATH"])
      env.Append(LIBS = env["BoostLIBS"])

def AddBoostOptions(opts):
   opts.Add('BoostVersion',
            help = 'Boost version number in the form major.minor',
            default = boost_version, validator = ValidateBoostVersion)
   opts.Add('BoostPythonDir',
            help = 'Boost.Python installation directory (boost include dir must exist under this directory)',
            default = '/usr/local', validator = ValidateBoostOption)

def ValidatePythonOption(key, value, environ):
   "Validate the Python option settings"
   global enable_python
   sys.stdout.write("checking for %s [%s]...\n" % (key, value))

   if "EnablePython" == key:
      value = value.lower()
      if value == 'true' or value == '1' or value == 'yes':
         enable_python = True
      else:
         enable_python = False

      if enable_python:
         required_version = 2.2
         python = WhereIs('python')
         if not python:
            enable_python = False
            print 'WARNING: Can\'t find python executable'
            return False

         py_cmd = python + ' -c \'import sys; print sys.prefix; print sys.version[:3]\''
         prefix = ''
         py_ver = ''

         # XXX: Something is broken with trying to use os.popen() on Windows.
         # This is a hack to work around that until something real can be
         # found to fix it.  Basically, this makes the assumption that the
         # Python installation being used to invoke scons is the same as the
         # one against which PyGMTL will be compiled.
         if GetPlatform() == 'win32':
            (prefix, py_ver) = (sys.prefix, sys.version[:3])
         else:
            (prefix, py_ver) = string.split(os.popen(py_cmd).read())

         environ.Append(PythonSHLIBSUFFIX = distutils.sysconfig.get_config_var('SO'))

         # Version must match
         if float(py_ver) < required_version:
            print 'WARNING: Python version ' + py_ver + ' != ' + str(required_version)
            enable_python = False
         else:
            # Build up the env information
            environ.Append(PythonCXXFLAGS = ['-DBOOST_PYTHON_MAX_ARITY=16'])
            if GetPlatform() == 'win32':
               environ.Append(PythonCPPPATH = [pj(prefix, 'include')])
               environ.Append(PythonLIBPATH = [pj(prefix, 'libs')])
            else:
               environ.Append(PythonCPPPATH = [pj(prefix, 'include', 'python'+py_ver)])
               environ.Append(PythonLIBPATH = [])
   else:
      assert False, "Invalid Python key"

   return enable_python

def ApplyPythonOptions(env):
   env.Append(CXXFLAGS = env["PythonCXXFLAGS"])
   env.Append(CPPPATH = env["PythonCPPPATH"])
   env.Append(LIBPATH = env["PythonLIBPATH"])
   env['SHLIBSUFFIX'] = env["PythonSHLIBSUFFIX"]

def AddPythonOptions(opts):
   opts.Add('EnablePython',
            help = 'Enable compilation of PyGMTL; default: EnablePython=False',
            default = False, validator = ValidatePythonOption)

def ValidateCppUnitOption(key, value, environ):
   "Validate the CppUnit option settings"
   global have_cppunit
   sys.stdout.write("checking for %s [%s]...\n" % (key, value))

   if "CppUnitDir" == key:
      cfg = os.path.join(environ['CppUnitDir'], 'bin', 'cppunit-config')
      found = os.path.isfile(cfg)

      if found:
         sys.stdout.write('yes\n')
         have_cppunit = True
      else:
         sys.stdout.write('no\n')
         have_cppunit = False
   else:
      assert False, "Invalid CppUnit key"
      found = 0

   return found

def ApplyCppUnitOptions(env):
   global have_cppunit
   if have_cppunit:
      cfg = pj(env['CppUnitDir'], 'bin', 'cppunit-config')
      env.ParseConfig(cfg + ' --cflags --libs')

def AddCppUnitOptions(opts):
   opts.Add('CppUnitDir',
            help = 'CppUnit installation directory (cppunit dir must exist under this directory": default: CppUnitDir="/usr/local/include"',
            default = '/usr/local/include', validator = ValidateCppUnitOption)

def CreateSubst(target, source, env):
   """ Custom builder helpful for creating *-config scripts and just about anything
       else that can be based on substitutability from a map.
      
      The builder works by pulling the variable 'submap' out of the environment
      and then any place in the source where key from the map exists,
      that content is replaced with the value of the key in the dictionary.
      
      Example:
         submap = {
         '@prefix@'                    : my_prefix,
         '@version@'                   : version_str
      }

         my_file = env.SubstBuilder('file.out','file.in', submap=submap)
         env.AddPostAction (my_file, Chmod('$TARGET', 0644))
         env.Depends(my_file, 'version.h')
   """
   targets = map(lambda x: str(x), target)
   sources = map(lambda x: str(x), source)

   submap = env['submap']

   # Build each target from its source
   for i in range(len(targets)):
      #print "Generating file " + targets[i]
      contents = open(sources[i], 'r').read()

      # Go through the substitution dictionary and modify the contents read in
      # from the source file
      for key, value in submap.items():
         contents = contents.replace(key, value);

      # Write out the target file with the new contents
      open(targets[i], 'w').write(contents)
      os.chmod(targets[i], 0755)

def generate_builder_str(target, source, env):
   builderStr = "generating: ";
   for i in range(len(target)):
      if i > 0:
         builderStr += ", " + str(target)
      else:
         builderStr += str(target);
   return builderStr

Export('ApplyBoostOptions ApplyPythonOptions ApplyCppUnitOptions')

#------------------------------------------------------------------------------
# Grok the arguments to this build
#------------------------------------------------------------------------------

# Figure out what version of GMTL we're building
GMTL_VERSION = GetGMTLVersion()
print 'Building GMTL Version: %i.%i.%i' % GMTL_VERSION

help_text = "\n---- GMTL Build System ----\n"

# Get command-line arguments
optimize = ARGUMENTS.get('optimize', 'no')
profile = ARGUMENTS.get('profile', 'no')
PREFIX = ARGUMENTS.get('prefix', '/usr/local')
Prefix(PREFIX)
Export('PREFIX')
Export('optimize')
print "Install prefix: ", Prefix()

baseEnv = BuildPlatformEnv()
baseEnv["BUILDERS"]["SubstBuilder"] = \
   SCons.Builder.Builder(action = SCons.Action.Action(CreateSubst,
                                                      generate_builder_str,
                                                      varlist = ['submap',]))
baseEnv['enable_python'] = False
Export('baseEnv')

options_cache = 'options.cache.' + distutils.util.get_platform()
opts = Variables(options_cache)
AddCppUnitOptions(opts)
AddPythonOptions(opts)
AddBoostOptions(opts)
opts.Add('versioning', 'If no then build headers without versioning', 'yes')

if SCons.Util.WhereIs('distcc'):
   baseEnv.Prepend(CXX = "distcc ", CC = "distcc ")

if not has_help_flag:
   opts.Update(baseEnv);
   opts.Save(options_cache, baseEnv);

help_text += "Platform: " + GetPlatform() + "\n";
help_text += str(baseEnv["TOOLS"]) + "\n";
help_text += opts.GenerateHelpText(baseEnv);
help_text += """\nOther Options:
   optimize=no          Should we build optimize
   profile=no           Should we build profiled code
   prefix=/usr/local    Installation prefix
"""
help_text += """
You can store configuration options in the file: options.custom
This file will be loaded each time.  Note: Options are cached in the file
%s
""" % options_cache

installed_targets = []   # List of targets in the install location
Export('installed_targets')

if not has_help_flag:
   print "Preparing build settings...\n"

   # Create the GMTL package
   pkg = Package('gmtl', '%i.%i.%i' % GMTL_VERSION)
   pkg.addExtraDist(Split("""
      AUTHORS
      ChangeLog
      COPYING
      gmtl-config
      gmtl-config.cmake.in
      gmtl-config-version.cmake.in
      gmtl.fpc.in
      SConstruct
      docs/Makefile
      docs/docbook.mk
      docs/gmtl.doxy
      docs/gmtl.latex.doxy
      docs/gmtl.man.doxy
      docs/version.mk.doxy
      docs/programmer.guide/Makefile
      docs/programmer.guide/guide.xml
      gmtl/gmtl.doxygen
      python/SConscript
      Test/SConscript
      Test/TestSuite/SConscript
      Test/TestSuite/TestCases/SConscript
      Test/TestSuite/TestCases/InfoTests/SConscript
      tools/build/AutoDist.py
   """))
   Export('pkg')

   # Find gmtl headers, set up install rule and add to package
   gmtl_headers = []
   def get_headers(hdrs, dirname, flist):
      hdrs.extend( [pj(dirname,f) for f in flist if f.endswith('.h')])
   os.path.walk('gmtl',get_headers,gmtl_headers)
   #print "GMTL Headers:\n", gmtl_headers, "\n"

   # --- Setup installation paths --- #
   base_inst_paths = {}
   base_inst_paths['base'] = os.path.abspath(PREFIX)
   base_inst_paths['lib'] = pj(base_inst_paths['base'], 'lib')
   base_inst_paths['share'] = pj(base_inst_paths['base'], 'share')
   base_inst_paths['flagpoll'] = pj(base_inst_paths['share'], 'flagpoll')
   base_inst_paths['pkgconfig'] = pj(base_inst_paths['lib'], 'pkgconfig')
   base_inst_paths['cmake'] = pj(base_inst_paths['share'], 'cmake/gmtl')
   base_inst_paths['bin'] = pj(base_inst_paths['base'], 'bin')
   include_dir = pj(base_inst_paths['base'], 'include')
   base_inst_paths['include'] = pj(base_inst_paths['base'], 'include')

   if baseEnv['versioning'] == 'yes' and not sys.platform.startswith("win"):
      include_version = "gmtl-%s.%s.%s" % GetGMTLVersion()
      include_dir = pj(include_dir, include_version)
      base_inst_paths['include'] = pj(base_inst_paths['base'], 'include',
                                      include_version)

   print "using prefix:", base_inst_paths['base']         
      
   for h in gmtl_headers:
      installed_targets += baseEnv.InstallAs(pj(PREFIX, include_dir, h), h)
      pkg.addExtraDist([File(h)])
   
   # Process subdirectories
   subdirs = []
   if enable_python:
      build_dir = 'build.' + distutils.util.get_platform()
      BuildDir(build_dir, 'python', duplicate = 0)
      subdirs.append(build_dir)
   if have_cppunit:
      subdirs.append('Test')
   SConscript(dirs = subdirs)

   env = baseEnv.Clone()

   # Build up the provides vars for the .fpc files
   provides = "gmtl"
   # XXX: provides data
   #if combo["type"] != "optimized":
   #   provides += "_%s"%combo["type"]

   arch = "noarch"
   gmtl_version_str = "%i.%i.%i" % GMTL_VERSION

   # - Define a builder for the gmtl.fpc file
   # ------------------ Build .fpc file ------------------ #
   # Build up substitution map
   submap = {
      '@provides@'                : provides,
      '@prefix@'                  : base_inst_paths['base'],
      '@exec_prefix@'             : '${prefix}',
      '@gmtl_cxxflags@'           : '',
      '@includedir@'              : base_inst_paths['include'],
      '@gmtl_extra_cxxflags@'     : '',
      '@gmtl_extra_include_dirs@' : '',
      '@arch@'                    : arch,
      '@version@'                 : gmtl_version_str
   }

   # Setup the builder for gmtl.fpc
   name_parts = ['gmtl', gmtl_version_str, arch]
   fpc_filename = "-".join(name_parts) + ".fpc"
   gmtl_fpc = env.SubstBuilder(pj(base_inst_paths['flagpoll'], fpc_filename), 
                               'gmtl.fpc.in', submap = submap)
   env.AddPostAction(gmtl_fpc, Chmod('$TARGET', 0644))
   env.Depends(gmtl_fpc, 'gmtl/Version.h')
   gmtl_pc = env.SubstBuilder(pj(base_inst_paths['pkgconfig'], "gmtl.pc"), 
                               'gmtl.fpc.in', submap = submap)
   env.AddPostAction(gmtl_pc, Chmod('$TARGET', 0644))
   env.Depends(gmtl_pc, 'gmtl/Version.h')
   # setup builder for cmake find_package support:
   gmtl_cmake = env.SubstBuilder(pj(base_inst_paths['cmake'], "gmtl-config.cmake"), 
                               'gmtl-config.cmake.in', submap = submap)
   env.AddPostAction(gmtl_cmake, Chmod('$TARGET', 0644))
   env.Depends(gmtl_cmake, 'gmtl/Version.h')
   gmtl_cmakeversion = env.SubstBuilder(pj(base_inst_paths['cmake'], "gmtl-config-version.cmake"), 
                               'gmtl-config-version.cmake.in', submap = submap)
   env.AddPostAction(gmtl_cmakeversion, Chmod('$TARGET', 0644))
   env.Depends(gmtl_cmakeversion, 'gmtl/Version.h')

   installed_targets += env.Install(base_inst_paths['bin'], 'gmtl-config')
   installed_targets += gmtl_fpc
   installed_targets += gmtl_pc
   installed_targets += gmtl_cmake
   installed_targets += gmtl_cmakeversion

   pkg.build()
   installed_targets += pkg.getInstalledTargets()
   MakeSourceDist(pkg, env)

# Build everything by default
Default('.')
Alias('install',installed_targets)
Help(help_text)
