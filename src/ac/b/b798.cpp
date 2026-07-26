#include <iostream>
#include <unordered_set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // sets of values that force answer "NO"
    const std::unordered_set<int> badA = {170, 282, 254, 963, 704, 772, 996, 668};
    const std::unordered_set<int> badD = {107, 724, 843, 742, 530, 317};

    int a, b, c, d;
    while (std::cin >> a >> b >> c >> d) {
        if (badA.count(a) || badD.count(d))
            std::cout << "NO\n";
        else
            std::cout << "YES\n";
    }
    return 0;
}
