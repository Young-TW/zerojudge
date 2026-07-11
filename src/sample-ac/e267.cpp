#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int G;
    while (cin >> G && G != 0) {
        string s;
        cin >> s;
        
        int group_len = s.length() / G;
        for (int i = 0; i < G; ++i) {
            int start = i * group_len;
            reverse(s.begin() + start, s.begin() + start + group_len);
        }
        
        cout << s << "\n";
    }
    
    return 0;
}
