#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int l;
    while (cin >> l) {
        string s;
        cin >> s;
        int n, t;
        cin >> n >> t;
        
        string result;
        result.reserve(t);
        int cnt = 0;
        
        // Left part: from n down to 1
        for (int i = n; i >= 1 && cnt < t; --i) {
            result.push_back(s[i - 1]);
            ++cnt;
        }
        
        // Right part: from n+1 to l
        for (int i = n + 1; i <= l && cnt < t; ++i) {
            result.push_back(s[i - 1]);
            ++cnt;
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
