#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<string> words(n);
        int total_length = 0;
        for (int i = 0; i < n; ++i) {
            cin >> words[i];
            total_length += words[i].size();
        }

        vector<int> indices(m);
        for (int i = 0; i < m; ++i) {
            cin >> indices[i];
            indices[i]--;
        }

        string combined;
        combined.reserve(total_length);
        for (const string& word : words) {
            combined += word;
        }

        for (int idx : indices) {
            cout << combined[idx];
        }
        cout << '\n';
    }

    return 0;
}
