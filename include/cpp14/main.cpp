#include <iostream>
#include <string>
#include <vector>
#include "algorithm"
#include "memory"
#include "tuple"
#include "type_traits"
#include "utility"

std::string mirror_ends(const std::string& in)
{
  return std::string(in.begin(),
                     cpp14::mismatch(in.begin (), in.end (), in.rbegin (), in.rend ()).first);
}

bool is_palindrome(const std::string& s)
{
  return cpp14::equal(s.begin(), s.begin() + s.size()/2, s.rbegin(), s.rbegin() + s.size()/2);
}

void test(const std::string& s)
{
  std::cout << "\"" << s << "\" "
            << (is_palindrome(s) ? "is" : "is not")
            << " a palindrome\n";
}

double L1(unsigned m, double x) { return -x + m + 1; }
double L2(unsigned m, double x) { return 0.5*(x*x-2*(m+2)*x+(m+1)*(m+2)); }

int main()
{
  std::vector<int> v1{1,2,3,4,5};
  std::vector<int> v2{3,5,4,1,2};
  std::cout << "3,5,4,1,2 is a permutation of 1,2,3,4,5? "
            << std::boolalpha
            << cpp14::is_permutation(v1.begin(), v1.end(), v2.begin(), v2.end ()) << '\n';
  
  std::vector<int> v3{3,5,4,1,1};
  std::cout << "3,5,4,1,1 is a permutation of 1,2,3,4,5? "
            << std::boolalpha
            << cpp14::is_permutation(v1.begin(), v1.end(), v3.begin(), v3.end ()) << '\n';
  
  std::cout << mirror_ends("abXYZba") << '\n'
            << mirror_ends("abca") << '\n'
            << mirror_ends("aba") << '\n';
  
  test("radar");
  test("hello");
  
}
