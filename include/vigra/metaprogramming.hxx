/************************************************************************/
/*                                                                      */
/*               Copyright 1998-2002 by Ullrich Koethe                  */
/*       Cognitive Systems Group, University of Hamburg, Germany        */
/*                                                                      */
/*    This file is part of the VIGRA computer vision library.           */
/*    You may use, modify, and distribute this software according       */
/*    to the terms stated in the LICENSE file included in               */
/*    the VIGRA distribution.                                           */
/*                                                                      */
/*    The VIGRA Website is                                              */
/*        http://kogs-www.informatik.uni-hamburg.de/~koethe/vigra/      */
/*    Please direct questions, bug reports, and contributions to        */
/*        koethe@informatik.uni-hamburg.de                              */
/*                                                                      */
/*  THIS SOFTWARE IS PROVIDED AS IS AND WITHOUT ANY EXPRESS OR          */
/*  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      */
/*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. */
/*                                                                      */
/************************************************************************/
 
#ifndef VIGRA_METAPROGRAMMING_HXX
#define VIGRA_METAPROGRAMMING_HXX

namespace vigra {

struct VigraTrueType
{
   enum { asBool = true };
};

struct VigraFalseType
{
    enum { asBool = false };
};

/**  \addtogroup MultiArrayTags Multi-dimensional Array Tags
      Meta-programming tags to mark array's as strided or unstrided.
*/

//@{

/********************************************************/
/*                                                      */
/*                   StridedArrayTag                    */
/*                                                      */
/********************************************************/

/** tag for marking a MultiArray strided.

<b>\#include</b>
"<a href="multi_array_8hxx-source.html">vigra/multi_array.hxx</a>"

Namespace: vigra
*/
struct StridedArrayTag {};

/********************************************************/
/*                                                      */
/*                  UnstridedArrayTag                   */
/*                                                      */
/********************************************************/

/** tag for marking a MultiArray unstrided.

<b>\#include</b>
"<a href="multi_array_8hxx-source.html">vigra/multi_array.hxx</a>"

Namespace: vigra
*/
struct UnstridedArrayTag {};

//@}

} // namespace vigra

#endif /* VIGRA_METAPROGRAMMING_HXX */
