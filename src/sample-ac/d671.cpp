#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    if (!getline(cin, line)) return 0;
    int T = atoi(line.c_str());

    while (T--) {
        if (!getline(cin, line)) break;
        int len = line.length();
        int n = 0;
        while ((n + 1) * (n + 1) <= len) {
            n++;
        }
        if (n * n != len) {
            cout << "INVALID\n";
        } else {
            string ans;
            ans.reserve(len);
            for (int j = 0; j < n; ++j) {
                for (int i = 0; i < n; ++i) {
                    ans += line[i * n + j];
                }
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}
