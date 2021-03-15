#include <vector>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <iostream>

template<typename type_t>
std::vector<type_t> stable_unique(const std::vector<type_t>& vec) {
  // You can do this, but it's not stable:
  // std::vector<type_t> vec2 = vec;
  // std::sort(vec2.begin(), vec2.end());
  // vec2.erase(std::unique(vec2.begin(), vec2.end()), vec2.end());

  std::vector<type_t> vec2;
  for(type_t x : vec) {
    if(vec2.end() == std::find(vec2.begin(), vec2.end(), x))
       vec2.push_back(x);
  }
  return vec2;
}

template<typename type_t, typename func_t>
std::vector<type_t> sort(const std::vector<type_t>& vec, func_t func) {
  std::vector<type_t> vec2 = vec;
  std::sort(vec2.begin(), vec2.end(), func);
  return vec2;
}

template<typename... types_t>
using unique_tuple_t = std::tuple<
  @pack_type(stable_unique(std::vector<@mtype>{ @dynamic_type(types_t)... }))...
>;

int main() {
  // Assert that the unique_tuple actually makes a unique tuple.
  static_assert(std::is_same_v<
    unique_tuple_t<double, float, int, int, float, const char*>, 
    std::tuple<double, float, int, const char*>
  >);

  unique_tuple_t<double, float, int, int, float, const char*> tuple {
    3.14, 1.618f, 100, "A great tuple"
  };

  // Print it out.
  std::cout<< int...<< ": "<< tuple...[:]<< "\n"...;
}