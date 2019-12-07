/** destroy_at.cpp
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

// template <class _Tp>
// void destroy_at(_Tp*);

#include <cpp17/memory>
#include <cstdlib>
#include <cassert>

#include "test_macros.h"

struct Counted {
  static int count;
  static void reset() { count = 0; }
  Counted() { ++count; }
  Counted(Counted const&) { ++count; }
  ~Counted() { --count; }
  friend void operator&(Counted) = delete;
};
int Counted::count = 0;

struct VCounted {
  static int count;
  static void reset() { count = 0; }
  VCounted() { ++count; }
  VCounted(VCounted const&) { ++count; }
  virtual ~VCounted() { --count; }
  friend void operator&(VCounted) = delete;
};
int VCounted::count = 0;

struct DCounted : VCounted {
  friend void operator&(DCounted) = delete;
};

int main(int, char**)
{
  {
    void* mem1 = std::malloc(sizeof(Counted));
    void* mem2 = std::malloc(sizeof(Counted));
    assert(mem1 && mem2);
    assert(Counted::count == 0);
    Counted* ptr1 = ::new(mem1) Counted();
    Counted* ptr2 = ::new(mem2) Counted();
    assert(Counted::count == 2);
    cpp17::destroy_at(ptr1);
    assert(Counted::count == 1);
    cpp17::destroy_at(ptr2);
    assert(Counted::count == 0);
    std::free(mem1);
    std::free(mem2);
  }
  {
    void* mem1 = std::malloc(sizeof(DCounted));
    void* mem2 = std::malloc(sizeof(DCounted));
    assert(mem1 && mem2);
    assert(DCounted::count == 0);
    DCounted* ptr1 = ::new(mem1) DCounted();
    DCounted* ptr2 = ::new(mem2) DCounted();
    assert(DCounted::count == 2);
    assert(VCounted::count == 2);
    cpp17::destroy_at(ptr1);
    assert(VCounted::count == 1);
    cpp17::destroy_at(ptr2);
    assert(VCounted::count == 0);
    std::free(mem1);
    std::free(mem2);
  }
  
  return 0;
}
