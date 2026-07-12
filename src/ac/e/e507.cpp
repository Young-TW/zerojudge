#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a, b;
    while (cin >> a >> b) {
        int count_a[26] = {0};
        int count_b[26] = {0};
        
        for (size_t i = 0; i < a.size(); ++i) {
            count_a[a[i] - 'a']++;
        }
        for (size_t i = 0; i < b.size(); ++i) {
            count_b[b[i] - 'a']++;
        }
        
        for (int i = 0; i < 26; ++i) {
            int common = min(count_a[i], count_b[i]);
            for (int j = 0; j < common; ++j) {
                cout << (char)('a' + i);
            }
        }
        cout << "\n";
    }
    
    return 0;
}
