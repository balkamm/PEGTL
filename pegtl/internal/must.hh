// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_MUST_HH
#define PEGTL_INTERNAL_MUST_HH

#include "seq.hh"

#include "../analysis/generic.hh"

namespace pegtl
{
   namespace internal
   {
      template< typename ... Rules > struct must;

      template<>
      struct must<>
            : trivial< true > {};

      template< typename Rule, typename ... Rules >
      struct must< Rule, Rules ... >
      {
         using analyze_t = analysis::generic< analysis::rule_type::CONJUNCTION, Rule, Rules ... >;

         template< error_mode E, template< typename ... > class Action, template< typename ... > class Control, typename Input, typename ... States >
         static bool match( Input & in, States && ... st )
         {
            return rule_match_call< seq< Rule, Rules ... >, error_mode::THROW, Action, Control >::match( in, st ... );
         }
      };

   } // internal

} // pegtl

#endif
