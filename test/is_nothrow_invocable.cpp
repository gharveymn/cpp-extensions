/** is_nothrow_invocable.cpp
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

// is_nothrow_invocable

#include <cpp17/type_traits>
#include <functional>
#include <vector>

#include "test_macros.h"

struct Tag {};

struct Implicit {
  Implicit(int) noexcept {}
};

struct ThrowsImplicit {
  ThrowsImplicit(int) {}
};

struct Explicit {
  explicit Explicit(int) noexcept {}
};

template <bool IsNoexcept, class Ret, class... Args>
struct CallObject {
  Ret operator()(Args&&...) const noexcept(IsNoexcept);
};

struct Sink {
  template <class... Args>
  void operator()(Args&&...) const noexcept {}
};

template <class Fn, class... Args>
constexpr bool throws_invocable() {
  return cpp17::is_invocable<Fn, Args...>::value &&
         !cpp17::is_nothrow_invocable<Fn, Args...>::value;
}

template <class Ret, class Fn, class... Args>
constexpr bool throws_invocable_r() {
  return cpp17::is_invocable_r<Ret, Fn, Args...>::value &&
         !cpp17::is_nothrow_invocable_r<Ret, Fn, Args...>::value;
}

// FIXME(EricWF) Don't test the where noexcept is *not* part of the type system
// once implementations have caught up.
void test_noexcept_function_pointers() {
  struct Dummy {
    void foo() noexcept {}
    static void bar() noexcept {}
  };
#if !defined(__cpp_noexcept_function_type)
  {
#define PRINT_EXP(EXP) \
char (*__fail)(void)[(EXP)] = 1;
    // Check that PMF's and function pointers *work*. is_nothrow_invocable will always
    // return false because 'noexcept' is not part of the function type.
//    static_assert(throws_invocable<decltype(&Dummy::foo), Dummy&>(), "");
//    static_assert(throws_invocable<decltype(&Dummy::bar)>(), "");
  }
#else
  {
    // Check that PMF's and function pointers actually work and that
    // is_nothrow_invocable returns true for noexcept PMF's and function
    // pointers.
    static_assert(
        cpp17::is_nothrow_invocable<decltype(&Dummy::foo), Dummy&>::value, "");
    static_assert(cpp17::is_nothrow_invocable<decltype(&Dummy::bar)>::value, "");
  }
#endif
}

struct AbominableFunc_struct
{
  void AbominableFunc_impl (...) const noexcept;
};

int main(int, char**) {
  using AbominableFunc = decltype (std::declval<AbominableFunc_struct> ().AbominableFunc_impl ());
  //  Non-callable things
  {
    static_assert(!cpp17::is_nothrow_invocable<void>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<const void>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<volatile void>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<const volatile void>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<std::nullptr_t>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<int>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<double>::value, "");
    
    static_assert(!cpp17::is_nothrow_invocable<int[]>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<int[3]>::value, "");
    
    static_assert(!cpp17::is_nothrow_invocable<int*>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<const int*>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<int const*>::value, "");
    
    static_assert(!cpp17::is_nothrow_invocable<int&>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<const int&>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<int&&>::value, "");
    
    static_assert(!cpp17::is_nothrow_invocable<int, std::vector<int> >::value,
                  "");
    static_assert(!cpp17::is_nothrow_invocable<int, std::vector<int*> >::value,
                  "");
    static_assert(!cpp17::is_nothrow_invocable<int, std::vector<int**> >::value,
                  "");
    
    static_assert(!cpp17::is_nothrow_invocable<AbominableFunc>::value, "");
    
    //  with parameters
    static_assert(!cpp17::is_nothrow_invocable<int, int>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<int, double, float>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<int, char, float, double>::value,
                  "");
    static_assert(!cpp17::is_nothrow_invocable<Sink, AbominableFunc>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<Sink, void>::value, "");
    static_assert(!cpp17::is_nothrow_invocable<Sink, const volatile void>::value,
                  "");
    
    static_assert(!cpp17::is_nothrow_invocable_r<int, void>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, const void>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, volatile void>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, const volatile void>::value,
                  "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, std::nullptr_t>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, int>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, double>::value, "");
    
    static_assert(!cpp17::is_nothrow_invocable_r<int, int[]>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, int[3]>::value, "");
    
    static_assert(!cpp17::is_nothrow_invocable_r<int, int*>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, const int*>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, int const*>::value, "");
    
    static_assert(!cpp17::is_nothrow_invocable_r<int, int&>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, const int&>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, int&&>::value, "");
    
    static_assert(!cpp17::is_nothrow_invocable_r<int, std::vector<int> >::value,
                  "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, std::vector<int*> >::value,
                  "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, std::vector<int**> >::value,
                  "");
    static_assert(!cpp17::is_nothrow_invocable_r<void, AbominableFunc>::value,
                  "");
    
    //  with parameters
    static_assert(!cpp17::is_nothrow_invocable_r<int, int, int>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<int, int, double, float>::value,
                  "");
    static_assert(
      !cpp17::is_nothrow_invocable_r<int, int, char, float, double>::value, "");
    static_assert(
      !cpp17::is_nothrow_invocable_r<void, Sink, AbominableFunc>::value, "");
    static_assert(!cpp17::is_nothrow_invocable_r<void, Sink, void>::value, "");
    static_assert(
      !cpp17::is_nothrow_invocable_r<void, Sink, const volatile void>::value,
      "");
  }
  
  {
    // Check that the conversion to the return type is properly checked
    using Fn = CallObject<true, int>;
    
    static_assert(cpp17::is_nothrow_invocable_r<Implicit, Fn>::value, "");
    static_assert(cpp17::is_nothrow_invocable_r<double, Fn>::value, "");
    static_assert(cpp17::is_nothrow_invocable_r<const volatile void, Fn>::value,
                  "");
    static_assert(throws_invocable_r<ThrowsImplicit, Fn>(), "");
    static_assert(!cpp17::is_nothrow_invocable<Fn(), Explicit>(), "");
  }
  {
    // Check that the conversion to the parameters is properly checked
    using Fn = CallObject<true, void, const Implicit&, const ThrowsImplicit&>;
    static_assert(
      cpp17::is_nothrow_invocable<Fn, Implicit&, ThrowsImplicit&>::value, "");
    static_assert(cpp17::is_nothrow_invocable<Fn, int, ThrowsImplicit&>::value,
                  "");
    static_assert(throws_invocable<Fn, int, int>(), "");
    static_assert(!cpp17::is_nothrow_invocable<Fn>::value, "");
  }
  {
    // Check that the noexcept-ness of function objects is checked.
    using Fn = CallObject<true, void>;
    using Fn2 = CallObject<false, void>;
    static_assert(cpp17::is_nothrow_invocable<Fn>::value, "");
    static_assert(throws_invocable<Fn2>(), "");
  }
  {
    // Check that PMD derefs are noexcept
    using Fn = int(Tag::*);
    static_assert(cpp17::is_nothrow_invocable<Fn, Tag&>::value, "");
    static_assert(cpp17::is_nothrow_invocable_r<Implicit, Fn, Tag&>::value, "");
    static_assert(throws_invocable_r<ThrowsImplicit, Fn, Tag&>(), "");
  }
  {
    // Check for is_nothrow_invocable_v
    using Fn = CallObject<true, int>;
//    static_assert(cpp17::is_nothrow_invocable_v<Fn>, "");
//    static_assert(!cpp17::is_nothrow_invocable_v<Fn, int>, "");
  }
  {
    // Check for is_nothrow_invocable_r_v
    using Fn = CallObject<true, int>;
//    static_assert(cpp17::is_nothrow_invocable_r_v<void, Fn>, "");
//    static_assert(!cpp17::is_nothrow_invocable_r_v<int, Fn, int>, "");
  }
  test_noexcept_function_pointers();
  
  return 0;
}
