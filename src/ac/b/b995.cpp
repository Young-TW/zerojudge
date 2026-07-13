#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    bool first_case = true;
    
    while (cin >> n >> m) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        vector<int> dir(n);
        vector<string> job(n);
        
        for (int i = 0; i < n; ++i) {
            cin >> dir[i] >> job[i];
        }
        
        int cur = 0;
        for (int i = 0; i < m; ++i) {
            int a, s;
            cin >> a >> s;
            if (a == dir[cur]) {
                cur = (cur - s % n + n) % n;
            } else {
                cur = (cur + s) % n;
            }
        }
        
        cout << job[cur] << "\n";
    }
    
    return 0;
}
