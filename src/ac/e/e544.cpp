#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int countInversions(const string& s) {
    int count = 0;
    int len = s.length();
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (s[i] > s[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        bool first_case = true;
        while (T--) {
            int n, m;
            cin >> n >> m;
            
            vector<pair<int, string>> dna(m);
            for (int i = 0; i < m; ++i) {
                string s;
                cin >> s;
                dna[i] = make_pair(countInversions(s), s);
            }
            
            stable_sort(dna.begin(), dna.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
                return a.first < b.first;
            });
            
            if (!first_case) {
                cout << "\n";
            }
            first_case = false;
            
            for (int i = 0; i < m; ++i) {
                cout << dna[i].second << "\n";
            }
        }
    }
    
    return 0;
}
