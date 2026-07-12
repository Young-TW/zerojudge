#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    while (cin >> m >> n) {
        vector<string> e(m);
        for (int i = 0; i < m; ++i) {
            cin >> e[i];
        }
        string T;
        cin >> T;
        
        for (int i = m - 1; i >= 0; --i) {
            deque<char> dq;
            for (int j = n - 1; j >= 0; --j) {
                if (e[i][j] == '0') {
                    dq.push_front(T[j]);
                } else {
                    dq.push_back(T[j]);
                }
            }
            T = string(dq.begin(), dq.end());
            
            int ones = count(e[i].begin(), e[i].end(), '1');
            if (ones % 2 == 1) {
                string newS = T;
                int half = n / 2;
                int offset = (n + 1) / 2;
                for (int j = 0; j < half; ++j) {
                    newS[j] = T[j + offset];
                    newS[j + offset] = T[j];
                }
                if (n % 2 == 1) {
                    newS[half] = T[half];
                }
                T = newS;
            }
        }
        cout << T << "\n";
    }
    
    return 0;
}
