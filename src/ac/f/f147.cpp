#include <iostream>
#include <vector>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const std::vector<std::string> setName = {
        "Medium Wac",
        "WChicken Nugget",
        "Geez Burger",
        "ButtMilk Crispy Chicken",
        "Plastic Toy"
    };
    const std::vector<int> setPrice = {4, 8, 7, 6, 3};

    const std::vector<std::string> singleName = {
        "German Fries",
        "Durian Slices",
        "WcFurry",
        "Chocolate Sunday"
    };
    const std::vector<int> singlePrice = {2, 3, 5, 7};

    long long total = 0;
    int cmd;
    while (std::cin >> cmd) {
        if (cmd == 0) {
            std::cout << "Total: " << total << '\n';
            break;
        } else if (cmd == 1) {
            int k; std::cin >> k;               // 1‑based index
            std::cout << setName[k - 1] << ' ' << setPrice[k - 1] << '\n';
            total += setPrice[k - 1];
        } else if (cmd == 2) {
            int k; std::cin >> k;
            std::cout << singleName[k - 1] << ' ' << singlePrice[k - 1] << '\n';
            total += singlePrice[k - 1];
        }
    }
    return 0;
}
