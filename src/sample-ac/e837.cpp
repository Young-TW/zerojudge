#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    while (cin >> s) {
        if (s.empty()) {
            continue;
        }

        int n = s.length();
        int max_len = 1;
        int max_end_index = 0;

        int current_len = 1;
        for (int i = 1; i < n; ++i) {
            if (s[i] == s[i-1] + 1) {
                current_len++;
            } else {
                if (current_len >= max_len) {
                    max_len = current_len;
                    max_end_index = i - 1;
                }
                current_len = 1;
            }
        }
        
        // Check the last sequence
        if (current_len >= max_len) {
            max_len = current_len;
            max_end_index = n - 1;
        }

        int start_index = max_end_index - max_len + 1;
        cout << max_len << " " << s.substr(start_index, max_len);
    }

    return 0;
}
