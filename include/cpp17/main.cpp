#include <iostream>
#include <random>
#include "algorithm"
#include "cmath"
#include "cstddef"
#include "memory"
#include "numeric"
#include "type_traits"

double L1(unsigned m, double x) { return -x + m + 1; }
double L2(unsigned m, double x) { return 0.5*(x*x-2*(m+2)*x+(m+1)*(m+2)); }

auto func2(char) -> int (*)()
{
  return nullptr;
}

int main()
{
  std::cout << cpp17::assoc_laguerre(1, 10, 0.5) << '=' << L1(10, 0.5) << '\n'
            << cpp17::assoc_laguerre(2, 10, 0.5) << '=' << L2(10, 0.5) << '\n';
  
  static_assert( cpp17::is_invocable<int()>::value, "");
  static_assert( cpp17::is_invocable_r<int, int()>::value, "");
  static_assert( cpp17::is_invocable_r<void, void(int), int>::value, "");
  static_assert( cpp17::is_invocable_r<int(*)(), decltype(func2), char>::value, "");
  
  std::string in = "abcdefgh", out;
  std::sample
  cpp17::sample(in.begin(), in.end(), std::back_inserter(out),
              5, std::mt19937{std::random_device{}()});
  std::cout << "five random letters out of " << in << " : " << out << '\n';
  
}
