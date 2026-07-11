#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    while (cin >> s) {
        int len = s.length();
        
        // Find K1 (<= N)
        string s1 = s;
        int idx1 = -1;
        for (int i = 0; i < len; ++i) {
            if ((s1[i] - '0') % 2 == 0) {
                idx1 = i;
                break;
            }
        }
        
        unsigned long long K1;
        if (idx1 == -1) {
            K1 = stoull(s1);
        } else {
            if (s1[idx1] == '0') {
                int j = idx1 - 1;
                while (j >= 0 && s1[j] == '1') {
                    j--;
                }
                if (j >= 0) {
                    s1[j] -= 2;
                    for (int k = j + 1; k < len; ++k) {
                        s1[k] = '9';
                    }
                    K1 = stoull(s1);
                } else {
                    string temp(len - 1, '9');
                    K1 = temp.empty() ? 0 : stoull(temp);
                }
            } else {
                s1[idx1] -= 1;
                for (int k = idx1 + 1; k < len; ++k) {
                    s1[k] = '9';
                }
                K1 = stoull(s1);
            }
        }
        
        // Find K2 (>= N)
        string s2 = s;
        int idx2 = -1;
        for (int i = 0; i < len; ++i) {
            if ((s2[i] - '0') % 2 == 0) {
                idx2 = i;
                break;
            }
        }
        
        unsigned long long K2;
        if (idx2 == -1) {
            K2 = stoull(s2);
        } else {
            s2[idx2] += 1;
            for (int k = idx2 + 1; k < len; ++k) {
                s2[k] = '1';
            }
            K2 = stoull(s2);
        }
        
        unsigned long long N = stoull(s);
        unsigned long long diff1 = N - K1;
        unsigned long long diff2 = K2 - N;
        
        if (diff1 < diff2) {
            cout << diff1 << "\n";
        } else {
            cout << diff2 << "\n";
        }
    }
    
    return 0;
}
