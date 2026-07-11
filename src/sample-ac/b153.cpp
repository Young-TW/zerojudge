#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
string s1, s2, s3;
int char_to_num[26];
bool used[26];
vector<char> chars;

bool check() {
    int carry = 0;
    for (int i = N - 1; i >= 0; --i) {
        int a = char_to_num[s1[i] - 'A'];
        int b = char_to_num[s2[i] - 'A'];
        int c = char_to_num[s3[i] - 'A'];
        int sum = a + b + carry;
        if (sum % N != c) return false;
        carry = sum / N;
    }
    return carry == 0;
}

bool dfs(int pos) {
    if (pos == chars.size()) {
        return check();
    }
    char c = chars[pos];
    for (int num = 0; num < N; ++num) {
        if (used[num]) continue;
        if (pos == 0 && num == 0) continue;
        char_to_num[c - 'A'] = num;
        used[num] = true;
        if (dfs(pos + 1)) return true;
        used[num] = false;
    }
    return false;
}

int main() {
    while (cin >> N) {
        cin >> s1 >> s2 >> s3;
        chars.clear();
        memset(used, 0, sizeof(used));
        for (char c : s1) {
            if (find(chars.begin(), chars.end(), c) == chars.end()) {
                chars.push_back(c);
            }
        }
        for (char c : s2) {
            if (find(chars.begin(), chars.end(), c) == chars.end()) {
                chars.push_back(c);
            }
        }
        for (char c : s3) {
            if (find(chars.begin(), chars.end(), c) == chars.end()) {
                chars.push_back(c);
            }
        }
        sort(chars.begin(), chars.end());
        chars.erase(unique(chars.begin(), chars.end()), chars.end());

        dfs(0);

        for (int i = 0; i < N; ++i) {
            if (i > 0) cout << " ";
            cout << char_to_num[i];
        }
        cout << endl;
    }
    return 0;
}
