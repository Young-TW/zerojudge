#include <iostream>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b;
    map<long long, long long> cnt;
    long long total = 0;

    while (cin >> a >> b) {
        if (a == -1 && b == -1) {
            cout << total << "\n";
            total = 0;
            cnt.clear();
        } else if (a == 1) {
            cnt[b]++;
            total++;
        } else if (a == 0) {
            auto it = cnt.find(b);
            if (it != cnt.end()) {
                total -= it->second;
                cnt.erase(it);
            }
        }
    }

    return 0;
}
