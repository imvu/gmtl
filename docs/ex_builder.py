#!/usr/bin/env python
#
#  Script to process example doxygen format
#
# Takes as input a "normal" doxygen file
# that may have example tags in it.
#
# It outputs the new version of the file
#
import sys;
import os;
import re;
import getopt;

# Globals
inFileName = None;
outFileName = None;
incPaths = [];

# Print the usage information
def printUsage():
   print "Usage: AutoBuild --help --search=<search path>";

# Handles the command line parameters
def parseCmdLine():
   global inFileName, outFileName;
   try:
      opts, args = getopt.getopt(sys.argv[1:], "", ["help", "path="])
   except getopt.GetoptError:
       # print help information and exit:
       printUsage()
       sys.exit(2)
   for o, a in opts:
       if o in ("-h", "--help"):
          printUsage()
          sys.exit()
       if o in ("--path",):
          incPaths.append(a);
   if len(args) == 0:
      print "Invalid number of args";
      printUsage();
      sys.exit();
   else:
      inFileName = args[0];
      if len(args) > 1:
         outFileName = args[1];

# Method called to replace a match on an exincludexample tag
# - Open the other file and get it's content
# - Remove all skips
# - Surround code with code tags
# - Remove comment begin and enders /* and */
# - Return it
def replaceExInclude(match):
   # Load the file
   # - Assume it is relative to the included file
   inc_file_name = match.groups()[0];
   inc_file_name = os.path.join(os.path.dirname(inFileName), inc_file_name);
   inc_file = file(inc_file_name);
   file_contents = inc_file.read();
   
   # Replace skips
   skip_re = re.compile("@exskip.*?@exendskip", re.DOTALL);
   noskip_contents = skip_re.sub("",file_contents);
   num_subs = 0;
   
   # - Surround the code
   # NOTE: This will also match the case */ <space> /* which we dont' want
   code_bounds_re = re.compile("\*/(.*?)/\*", re.DOTALL);
   bad_codes_re = re.compile("@code\W*?@endcode", re.DOTALL);    # re to remove codes that don't have content
   hanging_code_re = re.compile("\*/.*?(?! \*/)", re.DOTALL);    # re to handle the case of hanging code at the end of the document (ie. */ comment then code and nothing else)
   with_code_contents = code_bounds_re.sub("\n@code\n\\1\n@endcode\n", noskip_contents);
   (with_code_contents, num_subs) = hanging_code_re.subn("\n@code\n", with_code_contents);
   if num_subs > 0:                                              # If we added a hanging code, we need to close it too
      with_code_contents += "\n@endcode\n";
   fixed_code_content = bad_codes_re.sub("", with_code_contents);
   
   # -- Remove comment bookends
   comment_ends_re = re.compile("(/\*)|(\*/)");
   final_content = comment_ends_re.sub("", fixed_code_content);
   line_start_clean_re = re.compile("^\s*?\*", re.MULTILINE);
   final_content = line_start_clean_re.sub("", final_content);

   return final_content;
   
# Actual method to process the file
# - For any exincludeexample tags found
#   - Replace them with the resulting content
# - Save out the new file
def processFile():
   exincludeexample_re = re.compile("@exincludeexample\s*?(\S+)");   # Match the @exincludeexample tag
   
   # - Load the files
   in_file = file(inFileName, 'r');
   out_file = None;
   if(outFileName):
      out_file = file(outFileName, 'w');      # Truncates the old file
      
   # --- Process the file contents
   file_contents = in_file.read();
   new_file_contents = exincludeexample_re.sub(replaceExInclude, file_contents);
   
   # --- write it out
   if out_file:
      out_file.write(new_file_contents);
      out_file.close();
   else:
      print new_file_contents;
   in_file.close();
          
#
# "Main" function
#
if __name__ == "__main__":
   parseCmdLine();                           # Process the command line parameters
   processFile();
   sys.exit();

                
