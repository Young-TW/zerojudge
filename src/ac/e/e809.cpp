#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string order, s;
    int Q;
    while (cin >> order >> s >> Q) {
        int cnt[26] = {0};
        for (char c : s) {
            cnt[c - 'A']++;
        }
        
        int prefix[27] = {0};
        for (int i = 0; i < (int)order.size(); ++i) {
            prefix[i + 1] = prefix[i] + cnt[order[i] - 'A'];
        }
        
        while (Q--) {
            int X;
            cin >> X;
            for (int i = 0; i < (int)order.size(); ++i) {
                if (X <= prefix[i + 1]) {
                    cout << order[i] << '\n';
                    break;
                }
            }
        }
    }
    return 0;
}
