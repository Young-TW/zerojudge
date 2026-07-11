#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    for (int t = 1; t <= T; ++t) {
        string s;
        cin >> s;
        string result = "";
        int i = 0;
        int n = s.length();
        while (i < n) {
            char c = s[i];
            i++;
            int count = 0;
            while (i < n && isdigit(s[i])) {
                count = count * 10 + (s[i] - '0');
                i++;
            }
            result.append(count, c);
        }
        cout << "Case " << t << ": " << result << "\n";
    }
    
    return 0;
}
