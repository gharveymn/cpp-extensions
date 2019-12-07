/** make_unique_array.cpp
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

// UNSUPPORTED: c++98, c++03, c++11
#include <cpp14/memory>
#include <string>
#include <cassert>

#include "test_macros.h"

//    The only way to create an unique_ptr<T[]> is to default construct them.

class foo {
public:
  foo () : val_(3) {}
  int get () const { return val_; }
private:
  int val_;
};

int main(int, char**)
{
  {
    auto p1 = cpp14::make_unique<int[]>(5);
    for ( int i = 0; i < 5; ++i )
      assert ( p1[i] == 0 );
  }
  
  {
    auto p2 = cpp14::make_unique<std::string[]>(5);
    for ( int i = 0; i < 5; ++i )
      assert ( p2[i].size () == 0 );
  }
  
  {
    auto p3 = cpp14::make_unique<foo[]>(7);
    for ( int i = 0; i < 7; ++i )
      assert ( p3[i].get () == 3 );
  }
  
  return 0;
}
