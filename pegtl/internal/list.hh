// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_LIST_HH
#define PEGTL_INTERNAL_LIST_HH

#include "seq.hh"

namespace pegtl
{
   namespace internal
   {
      template< typename Rule, typename Sep, template< typename ... > class Star >
      using list = seq< Rule, Star< Sep, Rule > >;

   } // internal

} // pegtl

#endif
