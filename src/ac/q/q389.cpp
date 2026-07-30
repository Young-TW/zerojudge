#include <iostream>
#include <vector>
using namespace std;

static bool validDate(long long x) {
    int month = (int)((x / 100) % 100);
    int day = (int)(x % 100);
    if (month < 1 || month > 12) return false;
    const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return day >= 1 && day <= days[month];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int BASE_ROOT = 4499;
    vector<long long> after(101, 0), before(101, 0);
    after[0] = before[0] = 1LL * BASE_ROOT * BASE_ROOT;

    int found = 0;
    for (long long r = BASE_ROOT + 1; found < 100; ++r) {
        long long x = r * r;
        if (validDate(x)) after[++found] = x;
    }

    found = 0;
    for (long long r = BASE_ROOT - 1; found < 100 && r >= 100; --r) {
        long long x = r * r;
        if (validDate(x)) before[++found] = x;
    }

    int n;
    while (cin >> n) {
        if (n >= 0) cout << after[n] << '\n';
        else cout << before[-n] << '\n';
    }
    return 0;
}
