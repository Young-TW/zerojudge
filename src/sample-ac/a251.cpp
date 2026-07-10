#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            int s[4];
            cin >> N >> s[0] >> s[1] >> s[2] >> s[3];
            vector<int> seq(s, s + 4);
            for (int i = 4; i < N; i++) {
                seq.push_back(seq[i - 4] + seq[i - 1]);
            }
            sort(seq.begin(), seq.end());
            cout << seq[N / 2] << "\n";
        }
    }
    return 0;
}
