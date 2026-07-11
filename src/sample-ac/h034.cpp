#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<string> rows(n);
        int maxLen = 0;
        for (int i = 0; i < n; i++) {
            cin >> rows[i];
            if ((int)rows[i].size() > maxLen)
                maxLen = rows[i].size();
        }
        string result;
        for (int col = 0; col < maxLen; col++) {
            for (int row = 0; row < n; row++) {
                if (col < (int)rows[row].size()) {
                    char c = rows[row][col];
                    if (isalpha((unsigned char)c))
                        result += c;
                }
            }
        }
        cout << result << "\n";
    }
    return 0;
}
