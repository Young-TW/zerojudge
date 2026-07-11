#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string num_to_str = "mjqhofawcpnsexdkvgtzblryui";
    int str_to_num[26];
    string str_map = "uzrmatifxopnhwvbslekycqjgd";
    for (int i = 0; i < 26; ++i) {
        str_to_num[str_map[i] - 'a'] = i + 1;
    }

    int n;
    while (cin >> n) {
        while (n--) {
            int m;
            cin >> m;
            string token;
            bool is_alpha = false;
            long long sum = 0;
            string res = "";
            for (int i = 0; i < m; ++i) {
                cin >> token;
                if (isalpha(token[0])) {
                    is_alpha = true;
                    sum += str_to_num[token[0] - 'a'];
                } else {
                    int num = stoi(token);
                    res += num_to_str[num - 1];
                }
            }
            if (is_alpha) {
                cout << sum << "\n";
            } else {
                cout << res << "\n";
            }
        }
    }
    return 0;
}
