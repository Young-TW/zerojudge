#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N) {
        unordered_set<string> dict;
        dict.reserve(N * 2 + 16);
        string s;
        for (int i = 0; i < N; ++i) {
            cin >> s;
            dict.insert(s);
        }
        int Q;
        cin >> Q;
        for (int i = 0; i < Q; ++i) {
            cin >> s;
            if (dict.count(s)) {
                cout << "yes\n";
            } else {
                cout << "no\n";
                dict.insert(s);
            }
        }
    }
    return 0;
}
