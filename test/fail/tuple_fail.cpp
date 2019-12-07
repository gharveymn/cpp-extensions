/** tuple_test_fail.cpp
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
#include <memory>
#include <string>
#include "../test_macros.h"

struct UserType {};

void test_bad_index() {
  std::tuple<long, long, char, std::string, char, UserType, char> t1;
  TEST_IGNORE_NODISCARD cpp14::get<int>(t1); // expected-error@tuple:* {{type not found}}
  TEST_IGNORE_NODISCARD cpp14::get<long>(t1); // expected-note {{requested here}}
  TEST_IGNORE_NODISCARD cpp14::get<char>(t1); // expected-note {{requested here}}
  // expected-error@tuple:* 2 {{type occurs more than once}}
  std::tuple<> t0;
  TEST_IGNORE_NODISCARD cpp14::get<char*>(t0); // expected-node {{requested here}}
  // expected-error@tuple:* 1 {{type not in empty type list}}
}

void test_bad_return_type() {
  typedef std::unique_ptr<int> upint;
  std::tuple<upint> t;
  upint p = cpp14::get<upint>(t); // expected-error{{deleted copy constructor}}
}

int main(int, char**)
{
  test_bad_index();
  test_bad_return_type();
  
  return 0;
}
