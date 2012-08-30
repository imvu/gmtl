"""
AutoDist

Automatic distribution builder and packager for SCons.

"""
############################################################## autodist-cpr beg
#
# AutoDist - Automatic distribution builder and packager for
#            SCons-based builds
# AutoDist is (C) Copyright 2002 by Ben Scott
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#
# -----------------------------------------------------------------
# File:          $RCSfile: AutoDist.py,v $
# Date modified: $Date: 2005-01-03 17:30:31 $
# Version:       $Revision: 1.5 $
# -----------------------------------------------------------------
############################################################## autodist-cpr end

__version__    = '0.1.5'
__author__     = 'Ben Scott'


import os
from os import path

import SCons.Defaults
import SCons.Environment
import SCons.Node.FS


# SCons shorthand mappings
Action          = SCons.Action.Action
Builder         = SCons.Builder.Builder
Environment     = SCons.Environment.Environment
File            = SCons.Node.FS.default_fs.File

# The currently defined prefix
_prefix = '/usr/local'

def Prefix(prefix = None):
   """
   Returns the current installation prefix. If an argument is supplied, the
   prefix is changed to the supplied value and then returned.
   """
   global _prefix

   # Change the prefix if requested
   if prefix != None:
      _prefix = prefix

   # Return the current prefix
   return _prefix

class Header:
   def __init__(self, name, prefix=None):
      self.name = name
      self.prefix = prefix

   def __str__(self):
      """A Header's string representation is its prefix/name."""
      if prefix:
         return path.join(prefix, name)
      else:
         return name

   def getName(self):
      return self.name

   def getPrefix(self):
      return self.prefix


class _Assembly:
   """
   This "abstract" class provides common functionality for Program,
   StaticLibrary, and SharedLibrary. You don't want to instantiate this class
   directly. It is meant to be private.
   """

   def __init__(self, name, baseEnv):
      """
      Constructs a new Assembly object with the given name within the given
      environment.
      """
      self.data = {}
      self.data['name']          = File(name)
      self.data['sources']       = []
      self.data['includes']      = []
      self.data['libs']          = []
      self.data['libpaths']      = []
      self.data['headers']       = []
      self.data['installed']     = []

      # Clone the base environment if we have one
      if baseEnv:
         self.data['env'] = baseEnv.Clone()
      else:
         self.data['env'] = Environment()

   def addSources(self, sources):
      """
      Adds the given list of source files into this assembly. The list must come
      in as strings as they are processed through File().
      """
      # Use File() to figure out the absolute path to the file
      srcs = map(File, sources)
      # Add these sources into the mix
      self.data['sources'].extend(srcs)

   def addHeaders(self, headers, prefix = None):
      """
      Adds the given list of distribution header files into this assembly. These
      headers will be installed to Prefix()/include/prefix. The list must come
      in as strings as they are processed through File().
      """
      hdrs = map(lambda n,prefix=prefix: Header(n,prefix), map(File, headers))
      self.data['headers'].extend(hdrs)

   def addIncludes(self, includes):
      """
      Adds in the given list of include directories that this assembly will use
      while compiling.
      """
      self.data['includes'].extend(includes)

   def addLibs(self, libs):
      """
      Adds in the given list of libraries directories that this assembly will
      link with.
      """
      self.data['libs'].extend(libs)

   def addLibPaths(self, libpaths):
      """
      Adds in the given list of library directories that this assembly will use
      to find libraries while linking.
      """
      self.data['libpaths'].extend(libpaths)

   def getHeaders(self):
      return self.data['headers']

   def getSources(self):
      return self.data['sources']

   def build(self):
      """
      Sets up the build and install targets for this assembly.
      """
      # Setup the environment for the build
      self.data['env'].Append(CPPPATH = self.data['includes'],
                              LIBPATH = self.data['libpaths'],
                              LIBS    = self.data['libs'])

      # Now actually do the build
      self._buildImpl()


class _Library(_Assembly):
   """
   This "abstract" class provides common functionality for StaticLibrary and
   SharedLibrary. You don't want to instantiate this class directly. It is
   meant to be private.
   """

   def __init__(self, name, baseEnv, builder):
      """
      Creates a new library builder for a library of the given name.
      """
      _Assembly.__init__(self, name, baseEnv)
      self.data['builder'] = builder

   def _buildImpl(self):
      """
      Sets up the build dependencies and the install.
      """

      # Get the function that is used to build the library
      makeLib = self.data['builder']

      # Build rule
      lib = makeLib(self.data['env'], self.data['name'], self.data['sources'])

      # Install the binary
      self.data['env'].Install(path.join(Prefix(), 'lib'), lib)

      # Install the headers in the source list
      for h in self.data['headers']:
         prefix = h.getPrefix()
         filename = h.getName()
         target = path.join(Prefix(), 'include')
         # Add on the prefix if this header has one
         if prefix:
            target = path.join(target, prefix)
         sef.data['installed'] += self.data['env'].Install(target, filename)


class SharedLibrary(_Library):
   """
   This object knows how to build (and install) a shared library from a given
   set of sources.
   """

   def __init__(self, name, baseEnv = None):
      """
      Creates a new shared library builder for a library of the given name.
      """
      lib_name = path.join(path.dirname(str(name)),
                           baseEnv.subst('${SHLIBPREFIX}') + path.basename(str(name)) + baseEnv.subst('${SHLIBSUFFIX}'))

      _Library.__init__(self, lib_name, baseEnv, SCons.Defaults.SharedLibrary)


class StaticLibrary(_Library):
   """
   This object knows how to build (and install) a static library from a given
   set of sources.
   """

   def __init__(self, name, baseEnv = None):
      """
      Creates a new static library builder for a library of the given name.
      """
      lib_name = path.join(path.dirname(str(name)),
                           baseEnv.subst('${LIBPREFIX}') + path.basename(str(name)) + baseEnv.subst('${LIBSUFFIX}'))

      _Library.__init__(self, lib_name, baseEnv, SCons.Defaults.StaticLibrary)


class Program(_Assembly):
   """
   This object knows how to build (and install) an executable program from a
   given set of sources.
   """
   def __init__(self, name, baseEnv = None):
      """
      Creates a new program builder for a program of the given name.
      """
      prog_name = path.join(path.dirname(str(name)),
                            baseEnv.subst('${PROGPREFIX}') + path.basename(str(name)) + baseEnv.subst('${PROGSUFFIX}'))

      _Assembly.__init__(self, prog_name, baseEnv)

   def _buildImpl(self):
      """
      Sets up the build dependencies and the install.
      """
      # Build rule
      prog = self.data['env'].Program(self.data['name'], source  = self.data['sources'])

      # Install the binary
      sef.data['installed'] += self.data['env'].Install(path.join(Prefix(), 'bin'), prog)

class Package:
   """
   A package defines a collection of distributables including programs and
   libraries. The Package class provides the ability to build, install, and
   package up distributions of your project.
   """

   def __init__(self, name, version):
      """
      Creates a new package with the given name and version, where version is in
      the form of <major>.<minor>.<patch> (e.g 1.12.0)
      """
      self.data = {
         'name'         : name,
         'assemblies'   : [],
         'extra_dist'   : [],
      }

      # Extract the version parameters
      import re
      re_matches = re.match(r'^(\d+)\.(\d+)\.(\d+)$', version)
      self.data['version_major'] = int(re_matches.group(1))
      self.data['version_minor'] = int(re_matches.group(2))
      self.data['version_patch'] = int(re_matches.group(3))

   def createSharedLibrary(self, name, baseEnv = None):
      """
      Creates a new shared library of the given name as a part of this package.
      The library will be built within the given environment.
      """
      lib = SharedLibrary(name, baseEnv)
      self.data['assemblies'].extend([lib])
      return lib

   def createStaticLibrary(self, name, baseEnv = None):
      """
      Creates a new static library of the given name as a part of this package.
      The library will be built within the given environment.
      """
      lib = StaticLibrary(name, baseEnv)
      self.data['assemblies'].extend([lib])
      return lib

   def createProgram(self, name, baseEnv = None):
      """
      Creates a new executable program of the given name as a part of this
      package. The program will be built within the given environment.
      """
      prog = Program(name, baseEnv)
      self.data['assemblies'].extend([prog])
      return prog

   def addExtraDist(self, files, exclude=[]):
      """
      Adds in the given files to the distribution of this package. If a
      directory is encountered in the file list, it is recursively added. Files
      whose names are in the exclude list are not added to the list.
      """
      for file in files:
         # Make sure to skip files in the exclude list
         if not file in exclude:
            # If the file is a directory, recurse on it
            if os.path.isdir(str(file)):
               self.addExtraDist(os.listdir(str(file)), exclude)
            # If the file is not a directory, add in the extra dist list
            else:
               self.data['extra_dist'].append(file)

   def getName(self):
      return self.data['name']

   def getVersionMajor(self):
      return self.data['version_major']

   def getVersionMinor(self):
      return self.data['version_minor']

   def getVersionPatch(self):
      return self.data['version_patch']

   def getAssemblies(self):
      return self.data['assemblies']

   def getExtraDist(self):
      return self.data['extra_dist']
      
   def getInstalledTargets(self):
      installed_targets = []
      for assembly in self.getAssemblies():
         installed_targets += assembly.data['installed']
      return installed_targets

   def build(self):
      """
      Sets up the build and install for this package. This will build all
      assemblies contained therein and set them up to be installed.
      """
      #Environment().Alias('install', Prefix())
      for assembly in self.getAssemblies():
         assembly.build()


def MakeSourceDist(package, baseEnv = None):
   """
   Sets up the distribution build of a source tar.gz for the given package.
   This will put all the required source and extra distribution files into a
   compressed tarball. If an environment is specified, it is copied and the
   copy is used.
   """
   # Clone the base environment if we have one
   if baseEnv:
      env = baseEnv.Clone()
   else:
      env = Environment()


   # Create the distribution filename
   dist_filename = '%s-%d.%d.%d.tar.gz' % (package.getName(),
                                           package.getVersionMajor(),
                                           package.getVersionMinor(),
                                           package.getVersionPatch())

   # Add the tar.gz builder to the environment
   _CreateSourceTarGzBuilder(env)

   # Get a list of the sources that will be included in the distribution
   dist_files = []
   for a in package.getAssemblies():
      dist_files.extend(map(lambda n: n.getName(), a.getHeaders()))
      dist_files.extend(a.getSources())
   dist_files.extend(package.getExtraDist())

   # Setup the build of the distribution
   env.SourceTarGz(dist_filename, dist_files)

   # Mark implicit dependencies on all the files that will be distributed
   env.Depends(dist_filename, dist_files)

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

def _CreateSourceTarGzBuilder(env):
   import tempfile

   def makeSourceTarGz(target = None, source = None, env = None):
      import os, shutil, tempfile

      # Create the temporary directory
      dist_name = str(target[0])[:-len('.tar.gz')]
      temp_dir = tempfile.mktemp()
      target_dir = path.join(temp_dir, dist_name)

      os.makedirs(target_dir)

      # Copy the sources to the target directory
      for s in source:
         src_file = str(s)
         dest_dir = path.join(target_dir, path.dirname(src_file))
         dest_file = path.basename(src_file)

         # Make sure the target directory exists
         if not os.path.isdir(dest_dir):
            os.makedirs(dest_dir)

         # Copy the file over
         shutil.copy2(src_file, path.join(dest_dir, dest_file))

      # Make the tar.gz
      targz = Action('tar cf - -C '+temp_dir+' $SOURCES | gzip -f > $TARGET')
      targz(target, [File(dist_name)], env)

      # Remove the temporary directory
      shutil.rmtree(temp_dir)

      return None

   # Create the builder and add it to the environment
   source_targz_builder = Builder(action = makeSourceTarGz,
                                  suffix = '.tar.gz')
   env['BUILDERS']['SourceTarGz'] = source_targz_builder
