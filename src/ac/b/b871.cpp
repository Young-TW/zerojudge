#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<vector<string>> grid(N, vector<string>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> grid[i][j];
            }
        }

        int Q;
        cin >> Q;
        while (Q--) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            map<string, int> freq;
            int total = 0;
            for (int i = a; i <= c; ++i) {
                for (int j = b; j <= d; ++j) {
                    freq[grid[i][j]]++;
                    total++;
                }
            }
            bool found = false;
            string result;
            for (const auto& p : freq) {
                if (p.second > total / 2) {
                    found = true;
                    result = p.first;
                    break;
                }
            }
            if (found) {
                cout << result << '\n';
            } else {
                cout << "NO!!\n";
            }
        }
    }
    return 0;
}
