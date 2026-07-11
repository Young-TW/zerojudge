#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    bool first_case = true;
    
    while (getline(cin, s)) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        int freq[256] = {0};
        for (char c : s) {
            freq[(unsigned char)c]++;
        }
        
        vector<pair<int, int>> records;
        for (int i = 0; i < 256; ++i) {
            if (freq[i] > 0) {
                records.push_back({freq[i], i});
            }
        }
        
        sort(records.begin(), records.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) {
                return a.first < b.first;
            }
            return a.second > b.second;
        });
        
        for (const auto& p : records) {
            cout << p.second << " " << p.first << "\n";
        }
    }
    
    return 0;
}
