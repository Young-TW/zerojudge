#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<string> names(n);
        vector<int> g(n);
        vector<int> gs2(n);
        long long sum_g = 0, sum_gs2 = 0;
        
        for (int i = 0; i < n; ++i) {
            string name, gs_str;
            cin >> name >> g[i] >> gs_str;
            names[i] = name;
            sum_g += g[i];
            
            int val = 0;
            size_t dot = gs_str.find('.');
            if (dot == string::npos) {
                val = stoi(gs_str) * 2;
            } else {
                string int_part = gs_str.substr(0, dot);
                string frac_part = gs_str.substr(dot + 1);
                int ip = 0;
                if (!int_part.empty()) ip = stoi(int_part);
                if (!frac_part.empty() && frac_part[0] == '5') {
                    val = ip * 2 + 1;
                } else {
                    val = ip * 2;
                }
            }
            gs2[i] = val;
            sum_gs2 += val;
        }
        
        bool valid = true;
        if (sum_gs2 % n != 0) {
            valid = false;
        } else {
            int D = static_cast<int>(sum_gs2 / n);
            vector<int> W(n), L(n);
            for (int i = 0; i < n; ++i) {
                int numW = g[i] + D - gs2[i];
                int numL = g[i] - D + gs2[i];
                if (numW < 0 || numL < 0 || (numW % 2 != 0) || (numL % 2 != 0)) {
                    valid = false;
                    break;
                }
                W[i] = numW / 2;
                L[i] = numL / 2;
            }
            if (valid) {
                for (int i = 0; i < n; ++i) {
                    cout << names[i] << ' ' << W[i] << 'W' << L[i] << 'L' << '\n';
                }
            }
        }
        if (!valid) {
            cout << "establish\n";
        }
    }
    return 0;
}
