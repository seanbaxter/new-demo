#include <array>
#include <algorithm>
#include <tuple>
#include <iostream>

template<typename... types_t>
struct sorted_tuple {
  // Create a temporary holding std::string (name) and int (ordinal) pairs.
  @meta std::array<std::pair<std::string, int>, sizeof...(types_t)> v {
    std::make_pair(@type_string(types_t), int...) ...
  };

  // Sort the temporaries.
  @meta std::sort(v.begin(), v.end());

  // Use the sorted indices to gather the original type arguments.
  typedef std::tuple<types_t...[v...[:].second]...> type;
};

template<typename... types_t>
using sorted_tuple_t = typename sorted_tuple<types_t...>::type;

int main() {
  // Check that the arguments are lexicographically sorted.
  static_assert(std::is_same_v<
    sorted_tuple_t<int, double, float, char, int[2], void*, char[4]>,
    std::tuple<char, char[4], double, float, int, int[2], void*>
  >);

  // Instantiate an std::tuple with lexicographically sorted arguments.
  sorted_tuple_t<int, double, float, char, int[2], void*, char[4]> tuple;
}