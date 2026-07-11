#include <iostream>
#include <vector>

using namespace std;

struct Triangle {
    int a, b, c;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<Triangle> tri;
    for (int c = 1; c <= 100; ++c) {
        for (int b = 1; b < c; ++b) {
            for (int a = 1; a < b; ++a) {
                if (a * a + b * b == c * c) {
                    tri.push_back({a, b, c});
                }
            }
        }
    }
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            int cnt[101] = {0};
            for (int i = 0; i < N; ++i) {
                int x;
                cin >> x;
                if (x <= 100) {
                    cnt[x]++;
                }
            }
            long long ans = 0;
            for (const auto& t : tri) {
                ans += (long long)cnt[t.a] * cnt[t.b] * cnt[t.c];
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}
