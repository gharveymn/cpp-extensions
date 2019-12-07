/** is_nothrow_swappable_with.cpp
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

// type_traits

// is_nothrow_swappable_with

#include <cpp17/type_traits>
#include <vector>
#include "test_macros.h"

namespace MyNS {
  
  struct A {
    A(A const&) = delete;
    A& operator=(A const&) = delete;
  };
  
  struct B {
    B(B const&) = delete;
    B& operator=(B const&) = delete;
  };
  
  struct C {};
  struct D {};
  
  void swap(A&, A&) {}
  
  void swap(A&, B&) noexcept {}
  void swap(B&, A&) noexcept {}
  
  void swap(A&, C&) noexcept {}
  void swap(C&, A&) {}
  
  struct M {};
  
  void swap(M&&, M&&) noexcept {}
  
} // namespace MyNS

int main(int, char**)
{
  using namespace MyNS;
  {
    // Test that is_swappable_with doesn't apply an lvalue reference
    // to the type. Instead it is up to the user.
    static_assert(!cpp17::is_nothrow_swappable_with<int, int>::value, "");
    static_assert(cpp17::is_nothrow_swappable_with<int&, int&>::value, "");
    static_assert(cpp17::is_nothrow_swappable_with<M, M>::value, "");
    static_assert(cpp17::is_swappable_with<A&, A&>::value &&
                  !cpp17::is_nothrow_swappable_with<A&, A&>::value, "");
  }
  {
    // test that heterogeneous swap is allowed only if both 'swap(A, B)' and
    // 'swap(B, A)' are valid.
    static_assert(cpp17::is_nothrow_swappable_with<A&, B&>::value, "");
    static_assert(!cpp17::is_nothrow_swappable_with<A&, C&>::value &&
                    cpp17::is_swappable_with<A&, C&>::value, "");
    static_assert(!cpp17::is_nothrow_swappable_with<D&, C&>::value, "");
  }
  {
    // test we guard against cv void inputs as required.
    static_assert(!cpp17::is_nothrow_swappable_with<void, int>::value, "");
    static_assert(!cpp17::is_nothrow_swappable_with<int, void>::value, "");
    static_assert(!cpp17::is_nothrow_swappable_with<const void, const volatile void>::value, "");
    
  }
  {
    // test for presence of is_nothrow_swappable_with_v
    static_assert(cpp17::is_nothrow_swappable_with<int&, int&>::value, "");
    static_assert(!cpp17::is_nothrow_swappable_with<int&&, int&&>::value, "");
  }
  
  return 0;
}
