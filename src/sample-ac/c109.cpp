#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    bool first_case = true;
    while (cin >> n && n) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            a[i]--;
        }
        
        vector<vector<int>> cycles;
        vector<int> cycle_id(n, -1);
        vector<int> pos_in_cycle(n);
        
        for (int i = 0; i < n; ++i) {
            if (cycle_id[i] == -1) {
                vector<int> cycle;
                int curr = i;
                do {
                    cycle_id[curr] = cycles.size();
                    pos_in_cycle[curr] = cycle.size();
                    cycle.push_back(curr);
                    curr = a[curr];
                } while (curr != i);
                cycles.push_back(cycle);
            }
        }
        
        int k;
        while (cin >> k && k) {
            string text;
            getline(cin, text);
            if (!text.empty() && text.back() == '\r') {
                text.pop_back();
            }
            if (!text.empty() && text[0] == ' ') {
                text.erase(0, 1);
            }
            while (text.length() < (size_t)n) {
                text += ' ';
            }
            if (text.length() > (size_t)n) {
                text = text.substr(0, n);
            }
            
            string cipher(n, ' ');
            for (int i = 0; i < n; ++i) {
                int id = cycle_id[i];
                int len = cycles[id].size();
                int steps = k % len;
                int next = cycles[id][(pos_in_cycle[i] + steps) % len];
                cipher[next] = text[i];
            }
            cout << cipher << "\n";
        }
    }
    return 0;
}
