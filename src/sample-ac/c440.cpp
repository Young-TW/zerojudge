#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    while (cin >> s) {
        int total_Q = 0;
        for (char c : s) {
            if (c == 'Q') {
                total_Q++;
            }
        }
        
        long long ans = 0;
        int left_Q = 0;
        
        for (char c : s) {
            if (c == 'A') {
                ans += (long long)left_Q * (total_Q - left_Q);
            } else if (c == 'Q') {
                left_Q++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
