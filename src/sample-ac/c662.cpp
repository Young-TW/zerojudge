#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

string multiply(string a, int b) {
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        int prod = (a[i] - '0') * b + carry;
        a[i] = (prod % 10) + '0';
        carry = prod / 10;
    }
    while (carry) {
        a = (char)((carry % 10) + '0') + a;
        carry /= 10;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<int> a;
        int x;
        while (ss >> x) {
            a.push_back(x);
        }
        int n = a.size();
        if (n == 0) continue;
        
        vector<bool> visited(n, false);
        map<int, int> max_pow;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int curr = i;
                int len = 0;
                while (!visited[curr]) {
                    visited[curr] = true;
                    curr = a[curr];
                    len++;
                }
                int temp = len;
                for (int p = 2; p * p <= temp; p++) {
                    if (temp % p == 0) {
                        int cnt = 0;
                        while (temp % p == 0) {
                            temp /= p;
                            cnt++;
                        }
                        if (cnt > max_pow[p]) {
                            max_pow[p] = cnt;
                        }
                    }
                }
                if (temp > 1) {
                    if (1 > max_pow[temp]) {
                        max_pow[temp] = 1;
                    }
                }
            }
        }
        
        string ans = "1";
        for (auto& pair : max_pow) {
            int p = pair.first;
            int cnt = pair.second;
            for (int i = 0; i < cnt; i++) {
                ans = multiply(ans, p);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
