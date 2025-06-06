//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP___CXX03___ALGORITHM_PREV_PERMUTATION_H
#define _LIBCPP___CXX03___ALGORITHM_PREV_PERMUTATION_H

#include <__cxx03/__algorithm/comp.h>
#include <__cxx03/__algorithm/comp_ref_type.h>
#include <__cxx03/__algorithm/iterator_operations.h>
#include <__cxx03/__algorithm/reverse.h>
#include <__cxx03/__config>
#include <__cxx03/__iterator/iterator_traits.h>
#include <__cxx03/__utility/move.h>
#include <__cxx03/__utility/pair.h>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include <__cxx03/__undef_macros>

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _AlgPolicy, class _Compare, class _BidirectionalIterator, class _Sentinel>
_LIBCPP_HIDE_FROM_ABI pair<_BidirectionalIterator, bool>
__prev_permutation(_BidirectionalIterator __first, _Sentinel __last, _Compare&& __comp) {
  using _Result = pair<_BidirectionalIterator, bool>;

  _BidirectionalIterator __last_iter = _IterOps<_AlgPolicy>::next(__first, __last);
  _BidirectionalIterator __i         = __last_iter;
  if (__first == __last || __first == --__i)
    return _Result(std::move(__last_iter), false);

  while (true) {
    _BidirectionalIterator __ip1 = __i;
    if (__comp(*__ip1, *--__i)) {
      _BidirectionalIterator __j = __last_iter;
      while (!__comp(*--__j, *__i))
        ;
      _IterOps<_AlgPolicy>::iter_swap(__i, __j);
      std::__reverse<_AlgPolicy>(__ip1, __last_iter);
      return _Result(std::move(__last_iter), true);
    }
    if (__i == __first) {
      std::__reverse<_AlgPolicy>(__first, __last_iter);
      return _Result(std::move(__last_iter), false);
    }
  }
}

template <class _BidirectionalIterator, class _Compare>
inline _LIBCPP_HIDE_FROM_ABI bool
prev_permutation(_BidirectionalIterator __first, _BidirectionalIterator __last, _Compare __comp) {
  return std::__prev_permutation<_ClassicAlgPolicy>(
             std::move(__first), std::move(__last), static_cast<__comp_ref_type<_Compare> >(__comp))
      .second;
}

template <class _BidirectionalIterator>
inline _LIBCPP_HIDE_FROM_ABI bool prev_permutation(_BidirectionalIterator __first, _BidirectionalIterator __last) {
  return std::prev_permutation(__first, __last, __less<>());
}

_LIBCPP_END_NAMESPACE_STD

_LIBCPP_POP_MACROS

#endif // _LIBCPP___CXX03___ALGORITHM_PREV_PERMUTATION_H
