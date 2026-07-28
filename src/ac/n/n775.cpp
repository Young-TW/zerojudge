#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const double PI = std::acos(-1.0);
    int N;
    if (!(std::cin >> N)) return 0;
    std::string line;
    std::getline(std::cin, line);               // consume end‑of‑line after N

    for (int i = 0; i < N; ++i) {
        std::getline(std::cin, line);
        // remove possible carriage return
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n'))
            line.pop_back();

        std::stringstream ss(line);
        std::vector<int> v;
        int x;
        while (ss >> x) v.push_back(x);

        bool ok = true;
        double area = 0.0;

        if (v.size() == 2) {                     // r1 and r2 are given
            double r1 = v[0];
            double r2 = v[1];
            if (r1 <= 0.0 || r2 <= 0.0) ok = false;
            else area = 2.0 * PI * r1 * r2;
        } else if (v.size() == 1) {              // only t is given
            double t = v[0];
            if (t <= 0.0) ok = false;
            else area = PI * t * t / 8.0;
        } else {
            ok = false;
        }

        if (!ok) {
            std::cout << "Impossible.\n";
        } else {
            std::cout << std::fixed << std::setprecision(4) << area << "\n";
        }
    }
    return 0;
}
