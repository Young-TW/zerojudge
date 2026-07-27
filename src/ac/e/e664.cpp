#include <iostream>
#include <vector>
#include <sstream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;                 // skip empty lines

        std::stringstream ss(line);
        std::vector<long long> a;
        long long v;
        while (ss >> v) a.push_back(v);

        const int n = static_cast<int>(a.size());
        bool found = false;

        for (int i = 0; i < n; ++i) {
            int l = i;
            while (i + 1 < n && a[i + 1] == a[i]) ++i;
            int r = i;

            bool left_ok  = (l > 0) && (a[l - 1] < a[l]);
            bool right_ok = (r + 1 < n) && (a[r + 1] < a[l]);

            if (left_ok && right_ok) {
                found = true;
                if (l == r) {
                    std::cout << (l + 1) << ' ' << a[l] << '\n';
                } else {
                    std::cout << (l + 1) << ' ' << (r + 1) << ' ' << a[l] << '\n';
                }
            }
        }

        if (!found) {
            std::cout << "0 0\n";
        }
    }
    return 0;
}
