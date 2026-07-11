#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string chars;
    int L;
    string S;

    while (cin >> chars >> L >> S) {
        int K = chars.length();
        int char_to_idx[256];
        for (int i = 0; i < 256; ++i) {
            char_to_idx[i] = -1;
        }
        for (int i = 0; i < K; ++i) {
            char_to_idx[(unsigned char)chars[i]] = i;
        }

        int total = 1;
        for (int i = 0; i < L; ++i) {
            total *= K;
        }

        vector<char> seen(total, 0);

        int power = 1;
        for (int i = 0; i < L - 1; ++i) {
            power *= K;
        }

        int current_id = 0;
        int current_len = 0;

        for (int i = 0; i < (int)S.length(); ++i) {
            int idx = char_to_idx[(unsigned char)S[i]];
            if (idx != -1) {
                if (current_len < L) {
                    current_id = current_id * K + idx;
                    current_len++;
                    if (current_len == L) {
                        seen[current_id] = 1;
                    }
                } else {
                    current_id = (current_id - char_to_idx[(unsigned char)S[i - L]] * power) * K + idx;
                    seen[current_id] = 1;
                }
            } else {
                current_id = 0;
                current_len = 0;
            }
        }

        int ans_id = 0;
        while (ans_id < total && seen[ans_id]) {
            ans_id++;
        }

        string ans;
        ans.resize(L);
        for (int i = L - 1; i >= 0; --i) {
            ans[i] = chars[ans_id % K];
            ans_id /= K;
        }
        cout << ans << "\n";
    }

    return 0;
}
