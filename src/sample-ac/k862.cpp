#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        map<string, string> parent;
        string a, b;
        
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            parent[a] = b;
        }
        
        string p, q;
        cin >> p >> q;
        
        map<string, int> dist_p;
        string curr = p;
        int d = 0;
        
        while (true) {
            dist_p[curr] = d;
            if (parent.count(curr)) {
                curr = parent[curr];
                d++;
            } else {
                break;
            }
        }
        
        curr = q;
        d = 0;
        
        while (true) {
            if (dist_p.count(curr)) {
                cout << d - dist_p[curr] << "\n";
                break;
            }
            if (parent.count(curr)) {
                curr = parent[curr];
                d++;
            } else {
                break;
            }
        }
    }
    
    return 0;
}
