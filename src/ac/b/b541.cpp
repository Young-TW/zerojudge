#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> ans(41);

void precompute() {
    ans[1] = "1";
    for (int i = 2; i <= 40; ++i) {
        const string& prev = ans[i - 1];
        string& curr = ans[i];
        curr.clear();
        size_t len = prev.length();
        for (size_t j = 0; j < len; ) {
            char c = prev[j];
            int count = 0;
            while (j < len && prev[j] == c) {
                ++count;
                ++j;
            }
            curr += to_string(count);
            curr += c;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int n;
    while (cin >> n) {
        cout << ans[n] << "\n";
    }
    return 0;
}
