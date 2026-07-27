#include <iostream>
#include <array>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // number of alkane isomers for n = 1 .. 50
    const std::array<unsigned long long, 50> iso = {
        1ULL, 1ULL, 1ULL, 2ULL, 3ULL, 5ULL, 9ULL, 18ULL, 35ULL,
        75ULL, 159ULL, 355ULL, 802ULL, 1858ULL, 4347ULL, 10359ULL,
        24894ULL, 60523ULL, 148284ULL, 366319ULL, 910726ULL,
        2278658ULL, 5731580ULL, 14490245ULL, 36797588ULL,
        93839412ULL, 240215803ULL, 617105614ULL, 1590507121ULL,
        4111846763ULL, 10660307791ULL, 27711253769ULL,
        72214088660ULL, 188626236139ULL, 493782952902ULL,
        1295297588128ULL, 3404490780161ULL, 8964747474595ULL,
        23647478933969ULL, 62481801147341ULL, 165351455535782ULL,
        438242894769226ULL, 1163169707886427ULL, 3091461011836856ULL,
        8227162372221203ULL, 21921834086683418ULL,
        58481806621987010ULL, 156192366474590639ULL,
        417612400765382272ULL, 1117743651746953270ULL
    };

    int n;
    while (std::cin >> n) {
        if (n == 0) break;
        // n is guaranteed to be between 1 and 50
        std::cout << iso[n - 1] << '\n';
    }
    return 0;
}
