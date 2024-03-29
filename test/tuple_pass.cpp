/** tuple_test_pass.cpp
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

// modified: cpp14

// UNSUPPORTED: c++98, c++03, c++11

#include <cpp14/tuple>
#include <utility>
#include <memory>
#include <string>
#include <complex>
#include <type_traits>

#include <cassert>

#include "test_macros.h"


int main(int, char **)
{
  typedef std::complex<float> cf;
  {
    auto t1 = std::tuple<int, std::string, cf>{42, "Hi", {1, 2}};
    assert (cpp14::get<int>(t1) == 42); // find at the beginning
    assert (cpp14::get<std::string>(t1) == "Hi"); // find in the middle
    assert (cpp14::get<cf>(t1).real() == 1); // find at the end
    assert (cpp14::get<cf>(t1).imag() == 2);
  }
  
  {
    auto t2 = std::tuple<int, std::string, int, cf>{42, "Hi", 23, {1, 2}};
//  get<int> would fail!
    assert (cpp14::get<std::string>(t2) == "Hi");
    assert ((cpp14::get<cf>(t2) == cf{1, 2}));
  }
  
  {
    constexpr std::tuple<int, const int, double, double> p5{1, 2, 3.4, 5.6};
    static_assert(cpp14::get<int>(p5) == 1, "");
    static_assert(cpp14::get<const int>(p5) == 2, "");
  }
  
  {
    const std::tuple<int, const int, double, double> p5{1, 2, 3.4, 5.6};
    const int& i1 = cpp14::get<int>(p5);
    const int& i2 = cpp14::get<const int>(p5);
    assert (i1 == 1);
    assert (i2 == 2);
  }
  
  {
    typedef std::unique_ptr<int> upint;
    std::tuple<upint> t(upint(new int(4)));
    upint p = cpp14::get<upint>(std::move(t)); // get rvalue
    assert(*p == 4);
    assert(cpp14::get<upint>(t) == nullptr); // has been moved from
  }
  
  {
    typedef std::unique_ptr<int> upint;
    const std::tuple<upint> t(upint(new int(4)));
    const upint&& p = cpp14::get<upint>(std::move(t)); // get const rvalue
    assert(*p == 4);
    assert(cpp14::get<upint>(t) != nullptr);
  }
  
  {
    int x = 42;
    int y = 43;
    std::tuple<int&, int const&> const t(x, y);
    static_assert(
      std::is_same<int&, decltype(cpp14::get<int&>(std::move(t)))>::value, "");
    static_assert(noexcept(cpp14::get<int&>(std::move(t))), "");
    static_assert(std::is_same<int const&, decltype(cpp14::get<int const&>(
      std::move(t)))>::value, "");
    static_assert(noexcept(cpp14::get<int const&>(std::move(t))), "");
  }
  
  {
    int x = 42;
    int y = 43;
    std::tuple<int&&, int const&&> const t(std::move(x), std::move(y));
    static_assert(
      std::is_same<int&&, decltype(cpp14::get<int&&>(std::move(t)))>::value, "");
    static_assert(noexcept(cpp14::get<int&&>(std::move(t))), "");
    static_assert(std::is_same<int const&&, decltype(cpp14::get<int const&&>(
      std::move(t)))>::value, "");
    static_assert(noexcept(cpp14::get<int const&&>(std::move(t))), "");
  }
  
  {
    constexpr const std::tuple<int, const int, double, double>
      t{1, 2, 3.4, 5.6};
    static_assert(cpp14::get<int>(std::move(t)) == 1, "");
    static_assert(cpp14::get<const int>(std::move(t)) == 2, "");
  }
  
  return 0;
}
