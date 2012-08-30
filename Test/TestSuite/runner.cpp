// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

//------------------------------------------------------
// Test suite for GMTL
//
// This is designed to test EVERY capability of GMTL
//
//------------------------------------------------------
#include <stdexcept>
#include <cstring>

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/MetricRegistry.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <gmtl/Version.h>

#include "Suites.h"

std::string getHostname(void);

int main(int argc, char** argv)
{
   // Commandline parameter is the test path to use
   std::string test_path = (argc > 1) ? std::string(argv[1]) : "noninteractive";

   // -------- CONFIGURE METRIC REGISTRY ------- //
   CppUnit::MetricRegistry* metric_reg = CppUnit::MetricRegistry::instance();
   std::string metric_prefix;    // Prefix for all metric labels (mode/hostname)

   std::string host_name = getHostname();
   metric_prefix = host_name + "/";
#ifdef _DEBUG
   metric_prefix += "Debug/";
#endif
#ifdef _OPT
   metric_prefix += "Opt/";
#endif

   std::cout << " host: " << host_name << " prefix: "  << metric_prefix << std::endl;

   metric_reg->setPrefix(metric_prefix);
   metric_reg->setFilename("gmtl_metrics.txt");
   metric_reg->setMetric("Main/MetricTest", 1221.75f);

   // Print out what version of GMTL we're testing.
   std::cout<<std::endl;
   std::cout<<"GMTL Version: "<<gmtl::getVersion()<<std::endl;
   std::cout<<std::endl;

   //------------------------------------
   //  Test suites
   //------------------------------------
   CppUnit::TestFactoryRegistry& global_registry = CppUnit::TestFactoryRegistry::getRegistry();

   // noninteractive
   CppUnit::TestSuite* noninteractive_suite = new CppUnit::TestSuite("noninteractive");
   noninteractive_suite->addTest(global_registry.makeTest());

   // metric
   CppUnit::TestSuite* metric_suite = new CppUnit::TestSuite(gmtlTest::Suites::metric());
   metric_suite->addTest(CppUnit::TestFactoryRegistry::getRegistry(gmtlTest::Suites::metric()).makeTest());

   //------------------------------------
   // Test Runner
   //------------------------------------
   CppUnit::TextUi::TestRunner runner;

   // Make it use a compiler outputter
   CppUnit::Outputter* run_outputter =
      CppUnit::CompilerOutputter::defaultOutputter(&runner.result(), std::cout);
   runner.setOutputter(run_outputter);

   // Add a listener that prints the test names as the tests progress
   CppUnit::TestResult& result_event_manager = runner.eventManager();
   CppUnit::BriefTestProgressListener progress;
   result_event_manager.addListener(&progress);
   
   runner.addTest(noninteractive_suite);
   runner.addTest(metric_suite);


   //------------------------------------
   // Run Tests
   //------------------------------------
   bool success(false);

   try
   {
      std::cout << "Running " << test_path << std::endl;
      success = runner.run(test_path);
   }
   catch (std::invalid_argument& e)
   {
      // Test path was not resolved
      std::cerr   << std::endl
                  << "ERROR: " << e.what()
                  << std::endl;
      success = false;
   }

#ifdef WIN32
   std::cin.get();
#endif

   return (success ? 0 : 1);
}

#ifndef WIN32

#include <sys/utsname.h>

std::string getHostname(void)
{
   struct utsname buffer;

   if ( uname(&buffer) == 0 )
   {
      char* temp;
      temp = std::strchr(buffer.nodename, '.');

      // If the node name contains the full host, dots and all, truncate it
      // at the first dot.
      if ( temp != NULL )
      {
         *temp = '\0';
      }

      return std::string(buffer.nodename);
   }
   else
   {
      return std::string("<hostname-lookup failed>");
   }
}

#else

std::string getHostname(void)
{
   return std::string("<hostname-lookup failed>");
}
#endif
