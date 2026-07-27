#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int S, M, L;
    while (std::cin >> S >> M >> L) {
        int N;
        if (!(std::cin >> N)) break;
        std::vector<int> cars(N);
        for (int i = 0; i < N; ++i) std::cin >> cars[i];

        std::sort(cars.begin(), cars.end());

        int slots[3] = {S, M, L};
        int parked = 0;

        for (int sz : cars) {
            int cls;
            if (sz < 200) cls = 0;          // small
            else if (sz < 500) cls = 1;     // medium
            else cls = 2;                   // large

            for (int c = cls; c < 3; ++c) {
                if (slots[c] > 0) {
                    --slots[c];
                    ++parked;
                    break;
                }
            }
        }
        std::cout << parked << '\n';
    }
    return 0;
}
