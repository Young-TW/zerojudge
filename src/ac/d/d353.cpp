#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<string> S(31);
    S[0] = "1";
    for (int i = 1; i <= 30; ++i) {
        const string& prev = S[i-1];
        string curr;
        int len = prev.length();
        for (int j = 0; j < len; ) {
            char c = prev[j];
            int count = 0;
            while (j < len && prev[j] == c) {
                ++count;
                ++j;
            }
            curr += to_string(count);
            curr += c;
        }
        S[i] = curr;
    }
    
    int n;
    while (cin >> n) {
        if (n >= 0 && n <= 30) {
            cout << S[n] << "\n";
        }
    }
    
    return 0;
}
