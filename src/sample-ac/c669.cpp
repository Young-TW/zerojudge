#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    cin.ignore();
    
    string line;
    while (T--) {
        do {
            if (!getline(cin, line)) return 0;
        } while (line.find_first_not_of(" \t\r\n") == string::npos);
        
        stringstream ss(line);
        vector<long long> v;
        long long x;
        while (ss >> x) {
            v.push_back(x);
        }
        
        if (v.size() < 2) {
            continue;
        }
        
        sort(v.begin(), v.end());
        
        long long d = -1;
        for (size_t i = 0; i < v.size() - 1; ++i) {
            long long diff = v[i+1] - v[i];
            if (diff > 0) {
                if (d == -1 || diff < d) {
                    d = diff;
                }
            }
        }
        
        long long miss = 0, dup = 0;
        for (size_t i = 0; i < v.size() - 1; ++i) {
            long long diff = v[i+1] - v[i];
            if (diff == 0) {
                dup = v[i];
            } else if (diff == 2 * d) {
                miss = v[i] + d;
            }
        }
        
        cout << miss << " " << dup << "\n";
    }
    
    return 0;
}
