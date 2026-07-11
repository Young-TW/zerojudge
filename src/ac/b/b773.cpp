#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> dict;

bool isCandidate(const string &a, const string &b) {
    if (a.size() == b.size()) {
        int diff = 0;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                diff++;
                if (diff > 1) return false;
            }
        }
        return diff == 1;
    } else if (a.size() == b.size() + 1) {
        int i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] == b[j]) {
                i++;
                j++;
            } else {
                i++;
                if (i - j > 1) return false;
            }
        }
        return true;
    } else if (a.size() + 1 == b.size()) {
        int i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] == b[j]) {
                i++;
                j++;
            } else {
                j++;
                if (j - i > 1) return false;
            }
        }
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    dict.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> dict[i];
    }

    int Q;
    cin >> Q;
    while (Q--) {
        string query;
        cin >> query;

        bool found = false;
        vector<string> candidates;
        for (const string &word : dict) {
            if (word == query) {
                found = true;
                break;
            }
            if (isCandidate(word, query)) {
                candidates.push_back(word);
            }
        }

        if (found) {
            cout << ">" << query << "\n";
        } else if (!candidates.empty()) {
            cout << "?";
            for (const string &cand : candidates) {
                cout << cand << " ";
            }
            cout << "\n";
        } else {
            cout << "!" << query << "\n";
        }
    }

    return 0;
}
