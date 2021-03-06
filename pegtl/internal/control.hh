// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_CONTROL_HH
#define PEGTL_INTERNAL_CONTROL_HH

#include "seq.hh"

#include "../analysis/generic.hh"

namespace pegtl
{
   namespace internal
   {
      template< template< typename ... > class Control, typename ... Rules >
      struct control
      {
         using analyze_t = analysis::generic< analysis::rule_type::CONJUNCTION, Rules ... >;

         template< error_mode E, template< typename ... > class Action, template< typename ... > class, typename Input, typename ... States >
         static bool match( Input & in, States && ... st )
         {
            return rule_match_call< seq< Rules ... >, E, Action, Control >::match( in, st ... );
         }
      };

   } // internal

} // pegtl

#endif
