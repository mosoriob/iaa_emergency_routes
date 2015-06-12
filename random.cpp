#include <iostream>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

template <typename T>
std::vector<size_t> ordered(std::vector<T> const& values) {
    std::vector<size_t> indices(values.size());
    std::iota(begin(indices), end(indices), static_cast<size_t>(0));

    std::sort(
        begin(indices), end(indices),
        [&](size_t a, size_t b) { return values[a] > values[b]; }
    );
    return indices;
}

int main()
{
    vector <int> v = {20,40,10,20};
    vector <size_t> i = ordered<int>(v);
    cout << i[0] << endl;
  return 0;
}