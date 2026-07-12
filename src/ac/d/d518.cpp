#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        unordered_map<string, int> dict;
        int cnt = 1;
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            auto it = dict.find(s);
            if (it == dict.end()) {
                dict[s] = cnt;
                cout << "New! " << cnt << "\n";
                cnt++;
            } else {
                cout << "Old! " << it->second << "\n";
            }
        }
    }
    
    return 0;
}
