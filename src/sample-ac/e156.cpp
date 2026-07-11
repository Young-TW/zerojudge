#include <cstdio>
#include <numeric>
#include <iterator>
#include <iostream>
#include <algorithm>

struct Solver {
    void operator()(int n) const {
        int v[1001];
        std::iota(v + 1, v + n + 1, 1);
        printf("%d\n", std::accumulate(v + 1, v + n + 1, 0));
    }
};

int main() {
    std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), Solver());
    return 0;
}
