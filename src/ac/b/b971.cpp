#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, c;
    while (cin >> a >> b >> c) {
        if (c == 0) {
            cout << a << '\n';
            continue;
        }

        vector<long long> ans;
        if (c > 0) {
            for (long long i = a; i <= b; i += c) {
                ans.push_back(i);
            }
        } else {
            for (long long i = a; i >= b; i += c) {
                ans.push_back(i);
            }
        }

        for (size_t i = 0; i < ans.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}
