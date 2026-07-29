#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    bool first_case = true;

    while (cin >> N >> M) {
        if (!first_case) {
            cout << "\n\n\n\n\n\n\n";
        }
        first_case = false;

        string str;
        str.reserve(N);
        cin >> str;

        vector<int> count(26, 0);
        for (int i = 0; i < N; ++i) {
            count[str[i] - 'A']++;
        }

        vector<int> prefix_sum(27, 0);
        for (int i = 1; i <= 26; ++i) {
            prefix_sum[i] = prefix_sum[i - 1] + count[i - 1];
        }

        string ans;
        ans.reserve(M);
        for (int i = 0; i < M; ++i) {
            int q;
            cin >> q;
            
            int left = 1, right = 26;
            int char_idx = 26;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (prefix_sum[mid] >= q) {
                    char_idx = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            ans += (char)('A' + char_idx - 1);
        }
        cout << ans;
    }

    return 0;
}
