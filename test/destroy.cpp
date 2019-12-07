/** destroy.cpp
 * Short description here. 
 * 
 * Copyright © 2019 Gene Harvey
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03, c++11, c++14

// <memory>

// template <class ForwardIt>
// void destroy(ForwardIt, ForwardIt);

#include <cpp17/memory>
#include <cstdlib>
#include <cassert>

#include "test_macros.h"
#include "test_iterators.h"

struct Counted {
  static int count;
  static void reset() { count = 0; }
  Counted() { ++count; }
  Counted(Counted const&) { ++count; }
  ~Counted() { --count; }
  friend void operator&(Counted) = delete;
};
int Counted::count = 0;

int main(int, char**)
{
  using It = forward_iterator<Counted*>;
  const int N = 5;
  alignas(Counted) char pool[sizeof(Counted)*N] = {};
  Counted* p = (Counted*)pool;
  std::uninitialized_fill(p, p+N, Counted());
  assert(Counted::count == 5);
  cpp17::destroy(p, p+1);
  p += 1;
  assert(Counted::count == 4);
  cpp17::destroy(It(p), It(p + 4));
  assert(Counted::count == 0);
  
  return 0;
}

