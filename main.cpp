#include <iostream>
#include <string>
#include <vector>
#include <cpp14/algorithm>
#include <cpp14/memory>
#include <cpp14/tuple>
#include <cpp14/type_traits>
#include <cpp14/utility>

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
