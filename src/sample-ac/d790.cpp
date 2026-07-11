#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        for (int t = 0; t < T; ++t) {
            if (t > 0) {
                cout << "\n";
            }
            int N, H;
            cin >> N >> H;
            string s(N - H, '0');
            s += string(H, '1');
            do {
                cout << s << "\n";
            } while (next_permutation(s.begin(), s.end()));
        }
    }
    return 0;
}
