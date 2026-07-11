#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line1, line2;
    while (getline(cin, line1)) {
        if (line1.empty()) continue;
        stringstream ss1(line1);
        long long M, k;
        if (!(ss1 >> M >> k)) break;

        vector<long long> prices;
        long long p;
        while (ss1 >> p) {
            prices.push_back(p);
        }

        if (prices.empty()) {
            if (!getline(cin, line2)) break;
            stringstream ss2(line2);
            while (ss2 >> p) {
                prices.push_back(p);
            }
        }

        long long L = 1;
        bool overflow = false;
        for (long long price : prices) {
            long long g = gcd(L, price);
            if (L / g > M / price) {
                overflow = true;
                break;
            }
            L = L / g * price;
        }

        if (overflow || L > M - k) {
            cout << "\n";
            continue;
        }

        bool first = true;
        for (long long x = k + L; x <= M; x += L) {
            if (!first) {
                cout << " ";
            }
            cout << x;
            first = false;
        }
        cout << "\n";
    }

    return 0;
}
