#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

int n;
vector<string> words;
int overlap[20][20];
int used[20];
int max_len;

void dfs(int last, int current_len) {
    max_len = max(max_len, current_len);
    for (int i = 0; i < n; ++i) {
        if (used[i] < 2 && overlap[last][i] > 0) {
            used[i]++;
            dfs(i, current_len + words[i].size() - overlap[last][i]);
            used[i]--;
        }
    }
}

int main() {
    cin >> n;
    words.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }
    char start;
    cin >> start;

    memset(overlap, 0, sizeof(overlap));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            string &a = words[i];
            string &b = words[j];
            int max_over = min(a.size(), b.size()) - 1;
            for (int k = max_over; k >= 1; --k) {
                if (a.substr(a.size() - k) == b.substr(0, k)) {
                    overlap[i][j] = k;
                    break;
                }
            }
        }
    }

    max_len = 0;
    for (int i = 0; i < n; ++i) {
        if (words[i][0] == start) {
            memset(used, 0, sizeof(used));
            used[i] = 1;
            dfs(i, words[i].size());
        }
    }

    cout << max_len << endl;
    return 0;
}
