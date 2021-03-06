// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#include <cstddef>
#include <cassert>

#include <pegtl/rules.hh>
#include <pegtl/ascii.hh>
#include <pegtl/analyze.hh>

namespace pegtl
{
   std::size_t fails = 0;

   template< typename Rule >
   void assert_consumes( const unsigned line, const bool consumes, const bool problems = false )
   {
      analysis::analyze_cycles< Rule > a( false );
      const bool p = a.problems();
      if ( p != problems ) {
         ++fails;
         std::cerr << "pegtl: analyze rule [ " << internal::demangle< Rule >() << " ] problems received/expected [ " << p << " / " << problems << " ] in line [ " << line << " ]" << std::endl;
      }
      if ( a.template consumes< Rule >() != consumes ) {
         ++fails;
         std::cerr << "pegtl: analyze rule [ " << internal::demangle< Rule >() << " ] consumes received/expected [ " << ( ! consumes ) << " / " << consumes << " ] in line [ " << line << " ]" << std::endl;
      }
   }

   void unit_test()
   {
      assert_consumes< any >( __LINE__, true );
      assert_consumes< string< 'a' > >( __LINE__, true );
      assert_consumes< string< 'a', 'b' > >( __LINE__, true );
      assert_consumes< seq< one< 'a' >, eof > >( __LINE__, true );
      assert_consumes< seq< one< 'a' >, one< 'a' > > >( __LINE__, true );
      assert_consumes< sor< one< 'a' >, eof > >( __LINE__, false );
      assert_consumes< sor< one< 'a' >, one< 'b' > > >( __LINE__, true );
      assert_consumes< opt< eof > >( __LINE__, false );
      assert_consumes< opt< one< 'a' > > >( __LINE__, false );
      assert_consumes< plus< eof > >( __LINE__, false );
      assert_consumes< plus< one< 'a' > > >( __LINE__, true );
      assert_consumes< star< eof > >( __LINE__, false );
      assert_consumes< star< one< 'a' > > >( __LINE__, false );
      {
         struct bar;
         struct foo : seq< digit, bar > {};
         struct bar : plus< foo > {};
         assert_consumes< seq< any, bar > >( __LINE__, true, 0 );
      } {
         struct bar;
         struct foo : sor< digit, bar > {};
         struct bar : plus< foo > {};
         assert_consumes< sor< any, bar > >( __LINE__, false, 2 );
      }
   }

} // pegtl

#include "main.hh"
