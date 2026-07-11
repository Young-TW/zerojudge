#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int case_num = 1;
    
    while (cin >> n) {
        int cool_count = 0;
        for (int i = 0; i < n; ++i) {
            string word;
            cin >> word;
            
            int freq[26] = {0};
            for (char c : word) {
                freq[c - 'a']++;
            }
            
            vector<int> counts;
            for (int j = 0; j < 26; ++j) {
                if (freq[j] > 0) {
                    counts.push_back(freq[j]);
                }
            }
            
            if (counts.size() < 2) {
                continue;
            }
            
            sort(counts.begin(), counts.end());
            
            bool is_cool = true;
            for (size_t j = 1; j < counts.size(); ++j) {
                if (counts[j] == counts[j - 1]) {
                    is_cool = false;
                    break;
                }
            }
            
            if (is_cool) {
                cool_count++;
            }
        }
        cout << "Case " << case_num << ": " << cool_count << "\n";
        case_num++;
    }
    
    return 0;
}
