/** make_unique.cpp
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

int main(int, char**)
{
  {
    std::unique_ptr<int> p1 = cpp14::make_unique<int>(1);
    assert ( *p1 == 1 );
    p1 = cpp14::make_unique<int> ();
    assert ( *p1 == 0 );
  }
  
  {
    std::unique_ptr<std::string> p2 = cpp14::make_unique<std::string> ( "Meow!" );
    assert ( *p2 == "Meow!" );
    p2 = cpp14::make_unique<std::string> ();
    assert ( *p2 == "" );
    p2 = cpp14::make_unique<std::string> ( 6, 'z' );
    assert ( *p2 == "zzzzzz" );
  }
  
  return 0;
}
